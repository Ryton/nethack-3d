import { copyFileSync, existsSync, mkdirSync } from "node:fs";
import { dirname, resolve } from "node:path";
import { fileURLToPath } from "node:url";

const __dirname = dirname(fileURLToPath(import.meta.url));
const PROJECT_ROOT = resolve(__dirname, "../..");

const targets = [
  {
    id: "wasm-367",
    label: "NetHack 3.6.7",
    sourceBuildDir:
      "\\\\wsl.localhost\\Ubuntu\\home\\james\\Repos\\forked\\neth4ck-monorepo\\packages\\wasm-367\\build",
    sourceJsFileName: "nethack.js",
    sourceWasmFileName: "nethack.wasm",
    publicJsDest: resolve(PROJECT_ROOT, "public/nethack-367.js"),
    publicWasmDest: resolve(PROJECT_ROOT, "public/nethack-367.wasm"),
  },
  {
    id: "wasm-37",
    label: "NetHack 3.7",
    sourceBuildDir:
      "\\\\wsl.localhost\\Ubuntu\\home\\james\\Repos\\forked\\neth4ck-monorepo\\packages\\wasm-37\\build",
    sourceJsFileName: "nethack.js",
    sourceWasmFileName: "nethack.wasm",
    publicJsDest: resolve(PROJECT_ROOT, "public/nethack-37.js"),
    publicWasmDest: resolve(PROJECT_ROOT, "public/nethack-37.wasm"),
  },
  {
    id: "slashem",
    label: "Slash'EM",
    sourceBuildDir:
      "\\\\wsl.localhost\\Ubuntu\\home\\james\\Repos\\slashem-wasm\\build",
    sourceJsFileName: "slashem.js",
    sourceWasmFileName: "slashem.wasm",
    publicJsDest: resolve(PROJECT_ROOT, "public/slashem.js"),
    publicWasmDest: resolve(PROJECT_ROOT, "public/slashem.wasm"),
  },
];

function ensureFileExists(filePath, message) {
  if (!existsSync(filePath)) {
    throw new Error(message);
  }
}

export function copyWasm() {
  mkdirSync(resolve(PROJECT_ROOT, "public"), { recursive: true });

  for (const target of targets) {
    const sourceBuildDir = resolve(target.sourceBuildDir);
    const sourceJsPath = resolve(sourceBuildDir, target.sourceJsFileName);
    const sourceWasmPath = resolve(sourceBuildDir, target.sourceWasmFileName);

    ensureFileExists(
      sourceJsPath,
      `${target.label} JS build not found at ${sourceJsPath}`,
    );
    ensureFileExists(
      sourceWasmPath,
      `${target.label} wasm build not found at ${sourceWasmPath}`,
    );

    copyFileSync(sourceJsPath, target.publicJsDest);
    copyFileSync(sourceWasmPath, target.publicWasmDest);
  }
}

if (process.argv[1] && resolve(process.argv[1]) === fileURLToPath(import.meta.url)) {
  copyWasm();
}
