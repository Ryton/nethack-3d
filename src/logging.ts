type NH3DGlobalScope = typeof globalThis & {
  __NH3D_LOGGING_ENABLED__?: boolean;
  __NH3D_ORIGINAL_CONSOLE_LOG__?: typeof console.log;
  __NH3D_ORIGINAL_CONSOLE_INFO__?: typeof console.info;
  __NH3D_ORIGINAL_CONSOLE_WARN__?: typeof console.warn;
  __NH3D_ORIGINAL_CONSOLE_ERROR__?: typeof console.error;
  __NH3D_ORIGINAL_CONSOLE_DEBUG__?: typeof console.debug;
  __NH3D_ORIGINAL_CONSOLE_TRACE__?: typeof console.trace;
  __NH3D_ORIGINAL_CONSOLE_ASSERT__?: typeof console.assert;
  __NH3D_DEBUG_SESSION_LOG_HOOK__?: (
    level:
      | "log"
      | "info"
      | "warn"
      | "error"
      | "debug"
      | "trace"
      | "assert"
      | "event",
    args: unknown[],
    source?: string,
  ) => void;
};

const globalScope = globalThis as NH3DGlobalScope;

const noopLog: typeof console.log = (..._args: unknown[]): void => {};

if (!globalScope.__NH3D_ORIGINAL_CONSOLE_LOG__) {
  globalScope.__NH3D_ORIGINAL_CONSOLE_LOG__ = console.log.bind(console);
}
if (!globalScope.__NH3D_ORIGINAL_CONSOLE_INFO__) {
  globalScope.__NH3D_ORIGINAL_CONSOLE_INFO__ = console.info.bind(console);
}
if (!globalScope.__NH3D_ORIGINAL_CONSOLE_WARN__) {
  globalScope.__NH3D_ORIGINAL_CONSOLE_WARN__ = console.warn.bind(console);
}
if (!globalScope.__NH3D_ORIGINAL_CONSOLE_ERROR__) {
  globalScope.__NH3D_ORIGINAL_CONSOLE_ERROR__ = console.error.bind(console);
}
if (!globalScope.__NH3D_ORIGINAL_CONSOLE_DEBUG__) {
  globalScope.__NH3D_ORIGINAL_CONSOLE_DEBUG__ = console.debug.bind(console);
}
if (!globalScope.__NH3D_ORIGINAL_CONSOLE_TRACE__) {
  globalScope.__NH3D_ORIGINAL_CONSOLE_TRACE__ = console.trace.bind(console);
}
if (!globalScope.__NH3D_ORIGINAL_CONSOLE_ASSERT__) {
  globalScope.__NH3D_ORIGINAL_CONSOLE_ASSERT__ = console.assert.bind(console);
}

if (typeof globalScope.__NH3D_LOGGING_ENABLED__ !== "boolean") {
  // import.meta.env.DEV is a Vite feature that is true when running in development mode
  // (i.e. on localhost) and false when built for production.
  globalScope.__NH3D_LOGGING_ENABLED__ = import.meta.env.DEV;
}

function applyConsoleLogState(): void {
  const originalLog =
    globalScope.__NH3D_ORIGINAL_CONSOLE_LOG__ || console.log.bind(console);
  const originalInfo =
    globalScope.__NH3D_ORIGINAL_CONSOLE_INFO__ || console.info.bind(console);
  const originalDebug =
    globalScope.__NH3D_ORIGINAL_CONSOLE_DEBUG__ || console.debug.bind(console);
  const originalTrace =
    globalScope.__NH3D_ORIGINAL_CONSOLE_TRACE__ || console.trace.bind(console);
  const originalAssert =
    globalScope.__NH3D_ORIGINAL_CONSOLE_ASSERT__ || console.assert.bind(console);
  console.log = globalScope.__NH3D_LOGGING_ENABLED__ ? originalLog : noopLog;
  console.info = globalScope.__NH3D_LOGGING_ENABLED__ ? originalInfo : noopLog;
  console.debug = globalScope.__NH3D_LOGGING_ENABLED__ ? originalDebug : noopLog;
  console.trace = globalScope.__NH3D_LOGGING_ENABLED__ ? originalTrace : noopLog;
  console.assert = globalScope.__NH3D_LOGGING_ENABLED__
    ? originalAssert
    : ((condition?: boolean, ..._args: unknown[]) => {
        if (condition) {
          return;
        }
      });
}

export function isLoggingEnabled(): boolean {
  return Boolean(globalScope.__NH3D_LOGGING_ENABLED__);
}

export function setLoggingEnabled(enabled: boolean): boolean {
  globalScope.__NH3D_LOGGING_ENABLED__ = Boolean(enabled);
  applyConsoleLogState();
  return isLoggingEnabled();
}

export function toggleLoggingEnabled(): boolean {
  return setLoggingEnabled(!isLoggingEnabled());
}

export function logWithOriginal(...args: unknown[]): void {
  globalScope.__NH3D_DEBUG_SESSION_LOG_HOOK__?.(
    "log",
    args,
    "logWithOriginal",
  );
  const originalLog =
    globalScope.__NH3D_ORIGINAL_CONSOLE_LOG__ || console.log.bind(console);
  originalLog(...args);
}

// Enforce default-off logging policy as soon as this module is loaded.
applyConsoleLogState();
