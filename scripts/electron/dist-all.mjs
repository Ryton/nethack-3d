import { spawnSync } from "node:child_process";
import concurrently from "concurrently";
import fs from "node:fs";
import path from "node:path";
import process from "node:process";

const args = new Set(process.argv.slice(2));
const isParallel = args.has("--parallel");
const isDryRun = args.has("--dry-run");
const parallelOutputRoot = "release/.parallel";
const windowsParallelOutputDir = `${parallelOutputRoot}/win`;
const linuxParallelOutputDir = `${parallelOutputRoot}/linux`;
const npmExecPath = process.env.npm_execpath;
const npmRunner = npmExecPath
  ? {
    command: process.execPath,
    baseArgs: [npmExecPath],
  }
  : {
    command: process.platform === "win32" ? "npm.cmd" : "npm",
    baseArgs: [],
  };

function runOrExit(command, commandArgs, extraEnv = {}) {
  const printable = `${command} ${commandArgs.join(" ")}`;
  if (isDryRun) {
    console.log(`[dry-run] ${printable}`);
    return;
  }

  const result = spawnSync(command, commandArgs, {
    stdio: "inherit",
    shell: false,
    env: {
      ...process.env,
      ...extraEnv,
    },
  });

  if (result.error) {
    const message = result.error.code === "ENOENT"
      ? `Required command not found: ${command}`
      : result.error.message;
    console.error(message);
    process.exit(1);
  }

  if (typeof result.status === "number" && result.status !== 0) {
    process.exit(result.status);
  }
}

function runNpmOrExit(npmArgs, extraEnv = {}) {
  runOrExit(
    npmRunner.command,
    [...npmRunner.baseArgs, ...npmArgs],
    extraEnv,
  );
}

function quoteShellArg(value) {
  if (/^[A-Za-z0-9_./:=+\\-]+$/.test(value)) {
    return value;
  }

  if (process.platform === "win32") {
    return `"${value.replace(/"/g, '""')}"`;
  }

  return `'${value.replace(/'/g, `'\\''`)}'`;
}

function formatCommandForShell(command, args = []) {
  return [command, ...args].map(quoteShellArg).join(" ");
}

function runParallelJobsOrExit(jobs) {
  if (isDryRun) {
    for (const job of jobs) {
      const cmd = formatCommandForShell(job.command, job.args);
      console.log(`[dry-run] [${job.label}] ${cmd}`);
    }
    return Promise.resolve();
  }

  const { result } = concurrently(
    jobs.map((job) => ({
      command: formatCommandForShell(job.command, job.args),
      name: job.label,
      prefixColor: job.prefixColor,
      cwd: process.cwd(),
      env: job.env ?? {},
    })),
    {
      prefix: "name",
      padPrefix: true,
      prefixColors: jobs.map((job) => job.prefixColor ?? "auto"),
      killOthersOn: ["failure"],
      successCondition: "all",
    },
  );

  return result.catch((events) => {
    const failedEvent = events.find((event) => !event.killed && event.exitCode !== 0);
    if (failedEvent) {
      throw new Error(`${failedEvent.command.name} job failed with exit code ${failedEvent.exitCode}`);
    }

    const killedEvent = events.find((event) => event.killed);
    if (killedEvent) {
      throw new Error(`${killedEvent.command.name} job was terminated.`);
    }

    throw new Error("Parallel packaging failed.");
  });
}

function ensureCleanParallelOutputRoot() {
  const absoluteParallelOutputRoot = path.resolve(process.cwd(), parallelOutputRoot);
  fs.rmSync(absoluteParallelOutputRoot, { recursive: true, force: true });
  fs.mkdirSync(absoluteParallelOutputRoot, { recursive: true });
}

function sleep(milliseconds) {
  Atomics.wait(new Int32Array(new SharedArrayBuffer(4)), 0, 0, milliseconds);
}

function isRetryableFilesystemError(error) {
  return error && ["EBUSY", "ENOTEMPTY", "EPERM"].includes(error.code);
}

function replacePathWithRetries(sourcePath, destinationPath) {
  const maxAttempts = 20;

  for (let attempt = 1; attempt <= maxAttempts; attempt += 1) {
    try {
      fs.rmSync(destinationPath, { recursive: true, force: true });
      fs.renameSync(sourcePath, destinationPath);
      return;
    } catch (error) {
      if (!isRetryableFilesystemError(error) || attempt === maxAttempts) {
        throw error;
      }

      sleep(500);
    }
  }
}

function renameParallelMetadataFile(fileName, label) {
  if (fileName === "builder-debug.yml") {
    return `builder-debug.${label}.yml`;
  }

  if (fileName === "builder-effective-config.yaml") {
    return `builder-effective-config.${label}.yaml`;
  }

  return fileName;
}

function moveParallelOutputIntoRelease(sourceRelativeDir, label) {
  const sourceDir = path.resolve(process.cwd(), sourceRelativeDir);
  if (!fs.existsSync(sourceDir)) {
    throw new Error(`Expected ${label} output directory at ${sourceRelativeDir}, but it was not created.`);
  }

  const releaseDir = path.resolve(process.cwd(), "release");
  fs.mkdirSync(releaseDir, { recursive: true });

  for (const entry of fs.readdirSync(sourceDir, { withFileTypes: true })) {
    const sourcePath = path.join(sourceDir, entry.name);
    const destinationPath = path.join(releaseDir, renameParallelMetadataFile(entry.name, label));
    replacePathWithRetries(sourcePath, destinationPath);
  }
}

function finalizeParallelOutputsOrExit() {
  if (isDryRun) {
    console.log(`[dry-run] merge ${windowsParallelOutputDir} + ${linuxParallelOutputDir} into release/`);
    return;
  }

  moveParallelOutputIntoRelease(windowsParallelOutputDir, "win");
  moveParallelOutputIntoRelease(linuxParallelOutputDir, "linux");
  fs.rmSync(path.resolve(process.cwd(), parallelOutputRoot), { recursive: true, force: true });
}

async function main() {
  console.log("Building Electron web assets once...");
  runNpmOrExit(["run", "build:electron"]);

  const windowsElectronBuilderNpmArgs = [
    ...npmRunner.baseArgs,
    "exec",
    "--",
    "electron-builder",
    "--win",
    "nsis",
    "portable",
    "--x64",
  ];
  const linuxAllTargetsArgs = ["scripts/electron/dist-linux-appimage.mjs"];

  if (isParallel) {
    windowsElectronBuilderNpmArgs.push(`-c.directories.output=${windowsParallelOutputDir}`);

    console.log("Preparing Linux packaging prerequisites before parallel packaging...");
    if (!isDryRun) {
      ensureCleanParallelOutputRoot();
    }
    runOrExit("node", linuxAllTargetsArgs, {
      NH3D_SKIP_ELECTRON_BUILD: "1",
      NH3D_APPIMAGE_PREPARE_ONLY: "1",
      NH3D_ELECTRON_OUTPUT_DIR: linuxParallelOutputDir,
    });

    console.log("Packaging Windows and Linux targets in parallel...");
    await runParallelJobsOrExit([
      {
        label: "windows",
        command: npmRunner.command,
        args: windowsElectronBuilderNpmArgs,
        prefixColor: "blue",
      },
      {
        label: "linux",
        command: process.execPath,
        args: linuxAllTargetsArgs,
        env: {
          NH3D_SKIP_ELECTRON_BUILD: "1",
          NH3D_APPIMAGE_SKIP_PREPARE: "1",
          NH3D_ELECTRON_OUTPUT_DIR: linuxParallelOutputDir,
        },
        prefixColor: "magenta",
      },
    ]);
    finalizeParallelOutputsOrExit();
  } else {
    console.log("Packaging Windows setup + portable...");
    runOrExit(npmRunner.command, windowsElectronBuilderNpmArgs);
    console.log("Packaging Linux AppImage...");
    runOrExit("node", linuxAllTargetsArgs, { NH3D_SKIP_ELECTRON_BUILD: "1" });
  }

  console.log("Done. Artifacts are in release/.");
}

main().catch((error) => {
  console.error(error.message);
  process.exit(1);
});
