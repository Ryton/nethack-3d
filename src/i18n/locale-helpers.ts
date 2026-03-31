export type LocaleOverrides<T> = {
  [K in keyof T]?: T[K] extends (...args: any[]) => any
    ? T[K]
    : T[K] extends string
      ? string
      : T[K] extends number
        ? number
        : T[K] extends boolean
          ? boolean
          : T[K] extends bigint
            ? bigint
            : T[K] extends symbol
              ? symbol
              : T[K] extends object
                ? LocaleOverrides<T[K]>
                : T[K];
};

function isPlainObject(value: unknown): value is Record<string, unknown> {
  return typeof value === "object" && value !== null && !Array.isArray(value);
}

export function mergeTranslations<T>(base: T, overrides: LocaleOverrides<T>): T {
  if (!isPlainObject(base) || !isPlainObject(overrides)) {
    return (overrides as T) ?? base;
  }

  const result: Record<string, unknown> = {
    ...(base as Record<string, unknown>),
  };

  for (const [key, overrideValue] of Object.entries(overrides)) {
    if (overrideValue === undefined) {
      continue;
    }

    const baseValue = (base as Record<string, unknown>)[key];
    if (isPlainObject(baseValue) && isPlainObject(overrideValue)) {
      result[key] = mergeTranslations(baseValue, overrideValue as never);
    } else {
      result[key] = overrideValue;
    }
  }

  return result as T;
}
