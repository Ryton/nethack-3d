import fs from "node:fs";
import path from "node:path";
import vm from "node:vm";
import { createRequire } from "node:module";
import { fileURLToPath } from "node:url";
import ts from "typescript";

const require = createRequire(import.meta.url);
const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);
const repoRoot = path.resolve(__dirname, "..", "..");
const showAll = process.argv.includes("--verbose");
const maxItemsPerCategory = showAll ? Number.POSITIVE_INFINITY : 80;

const localeChecks = [
  {
    locale: "de",
    file: path.join(repoRoot, "src", "i18n", "locales", "de.ts"),
    exportName: "de",
  },
  {
    locale: "es",
    file: path.join(repoRoot, "src", "i18n", "locales", "es.ts"),
    exportName: "esOverrides",
  },
  {
    locale: "fi",
    file: path.join(repoRoot, "src", "i18n", "locales", "fi.ts"),
    exportName: "fi",
  },
  {
    locale: "ja",
    file: path.join(repoRoot, "src", "i18n", "locales", "ja.ts"),
    exportName: "ja",
  },
  {
    locale: "pt-br",
    file: path.join(repoRoot, "src", "i18n", "locales", "pt-br.ts"),
    exportName: "ptBrOverrides",
  },
  {
    locale: "zh-cn",
    file: path.join(repoRoot, "src", "i18n", "locales", "zh-cn.ts"),
    exportName: "zhCnOverrides",
  },
];

const moduleCache = new Map();

function resolveModulePath(request, fromDirectory) {
  const basePath = path.resolve(fromDirectory, request);
  const candidates = [
    basePath,
    `${basePath}.ts`,
    `${basePath}.tsx`,
    `${basePath}.js`,
    `${basePath}.mjs`,
    `${basePath}.cjs`,
    path.join(basePath, "index.ts"),
    path.join(basePath, "index.tsx"),
    path.join(basePath, "index.js"),
    path.join(basePath, "index.mjs"),
    path.join(basePath, "index.cjs"),
  ];

  for (const candidate of candidates) {
    if (fs.existsSync(candidate) && fs.statSync(candidate).isFile()) {
      return candidate;
    }
  }

  throw new Error(
    `Unable to resolve module '${request}' from '${fromDirectory}'.`,
  );
}

function loadTsModule(modulePath) {
  const resolvedPath = path.resolve(modulePath);
  if (moduleCache.has(resolvedPath)) {
    return moduleCache.get(resolvedPath).exports;
  }

  const source = fs.readFileSync(resolvedPath, "utf8");
  const transpiled = ts.transpileModule(source, {
    compilerOptions: {
      module: ts.ModuleKind.CommonJS,
      target: ts.ScriptTarget.ES2020,
      jsx: ts.JsxEmit.ReactJSX,
      esModuleInterop: true,
    },
    fileName: resolvedPath,
  });

  const module = { exports: {} };
  moduleCache.set(resolvedPath, module);

  const localRequire = (request) => {
    if (request.startsWith(".") || request.startsWith("/")) {
      const dependencyPath = resolveModulePath(
        request,
        path.dirname(resolvedPath),
      );
      return loadTsModule(dependencyPath);
    }
    return require(request);
  };

  const context = vm.createContext({
    module,
    exports: module.exports,
    require: localRequire,
    __dirname: path.dirname(resolvedPath),
    __filename: resolvedPath,
    console,
    process,
    Buffer,
    setTimeout,
    clearTimeout,
    setInterval,
    clearInterval,
  });

  const script = new vm.Script(transpiled.outputText, {
    filename: resolvedPath,
  });
  script.runInContext(context);
  return module.exports;
}

function isPlainObject(value) {
  return typeof value === "object" && value !== null && !Array.isArray(value);
}

function describeValueKind(value) {
  if (Array.isArray(value)) {
    return "array";
  }
  return typeof value;
}

function collectLeafPaths(value, prefix) {
  if (isPlainObject(value)) {
    return Object.entries(value).flatMap(([key, child]) =>
      collectLeafPaths(child, [...prefix, key]),
    );
  }
  return [prefix.join(".")];
}

function collectIdenticalStringPaths(baseValue, localeValue, prefix, result) {
  if (localeValue === undefined) {
    return;
  }

  if (isPlainObject(baseValue)) {
    if (!isPlainObject(localeValue)) {
      return;
    }

    for (const [key, childBaseValue] of Object.entries(baseValue)) {
      collectIdenticalStringPaths(
        childBaseValue,
        localeValue[key],
        [...prefix, key],
        result,
      );
    }
    return;
  }

  if (
    typeof baseValue === "string" &&
    typeof localeValue === "string" &&
    prefix.join(".") !== "meta.locale" &&
    baseValue === localeValue
  ) {
    result.push(prefix.join("."));
  }
}

function compareTrees(baseValue, localeValue, prefix, result) {
  const baseKind = describeValueKind(baseValue);
  const localeKind = describeValueKind(localeValue);
  const keyPath = prefix.join(".");

  if (localeValue === undefined) {
    result.missing.push(...collectLeafPaths(baseValue, prefix));
    return;
  }

  if (isPlainObject(baseValue)) {
    if (!isPlainObject(localeValue)) {
      result.mismatchedTypes.push({
        path: keyPath,
        expected: baseKind,
        actual: localeKind,
      });
      return;
    }

    for (const [key, childBaseValue] of Object.entries(baseValue)) {
      compareTrees(childBaseValue, localeValue[key], [...prefix, key], result);
    }

    for (const key of Object.keys(localeValue)) {
      if (!(key in baseValue)) {
        result.extra.push([...prefix, key].join("."));
      }
    }
    return;
  }

  if (baseKind !== localeKind) {
    result.mismatchedTypes.push({
      path: keyPath,
      expected: baseKind,
      actual: localeKind,
    });
    return;
  }

  if (
    typeof baseValue === "function" &&
    typeof localeValue === "function" &&
    baseValue.length !== localeValue.length
  ) {
    result.mismatchedArity.push({
      path: keyPath,
      expected: baseValue.length,
      actual: localeValue.length,
    });
  }
}

function printCategory(title, items, formatter = (item) => item, log = "error") {
  if (items.length === 0) {
    return;
  }

  console[log](`  ${title}: ${items.length}`);
  const visibleItems = items.slice(0, maxItemsPerCategory);
  for (const item of visibleItems) {
    console[log](`    - ${formatter(item)}`);
  }
  if (visibleItems.length < items.length) {
    console[log](`    ... ${items.length - visibleItems.length} more`);
  }
}

const { en } = loadTsModule(
  path.join(repoRoot, "src", "i18n", "locales", "en.ts"),
);
let hasFailures = false;

for (const localeCheck of localeChecks) {
  const localeModule = loadTsModule(localeCheck.file);
  const localeValue = localeModule[localeCheck.exportName];

  if (!localeValue) {
    console.error(
      `Translation check failed: export '${localeCheck.exportName}' was not found in ${localeCheck.file}.`,
    );
    process.exitCode = 1;
    hasFailures = true;
    continue;
  }

  const result = {
    missing: [],
    extra: [],
    mismatchedTypes: [],
    mismatchedArity: [],
    identicalStrings: [],
  };

  compareTrees(en, localeValue, [], result);
  collectIdenticalStringPaths(en, localeValue, [], result.identicalStrings);

  const issueCount =
    result.missing.length +
    result.extra.length +
    result.mismatchedTypes.length +
    result.mismatchedArity.length;

  if (issueCount === 0) {
    if (result.identicalStrings.length === 0) {
      console.log(`Locale '${localeCheck.locale}' is complete.`);
    } else {
      console.warn(
        `Locale '${localeCheck.locale}' is complete with ${result.identicalStrings.length} identical-string warning${result.identicalStrings.length === 1 ? "" : "s"}.`,
      );
      printCategory(
        "Identical to English",
        result.identicalStrings,
        (item) => item,
        "warn",
      );
    }
    continue;
  }

  hasFailures = true;
  console.error(`Locale '${localeCheck.locale}' has translation issues.`);
  printCategory("Missing keys", result.missing);
  printCategory("Extra keys", result.extra);
  printCategory(
    "Type mismatches",
    result.mismatchedTypes,
    (item) => `${item.path} (expected ${item.expected}, got ${item.actual})`,
  );
  printCategory(
    "Function arity mismatches",
    result.mismatchedArity,
    (item) => `${item.path} (expected ${item.expected}, got ${item.actual})`,
  );
  printCategory("Identical to English", result.identicalStrings);
}

if (hasFailures) {
  if (!showAll) {
    console.error("Re-run with --verbose to print every issue.");
  }
  process.exitCode = 1;
} else {
  console.log("All locale overrides are complete.");
}
