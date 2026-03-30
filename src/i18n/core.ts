import { en, type TranslationDictionary } from "./locales/en";

export type SupportedLocale = "en";

const dictionaries: Record<SupportedLocale, TranslationDictionary> = {
  en,
};

const localeStorageKey = "nh3d-locale";

const localeLabels: Record<SupportedLocale, string> = {
  en: "English",
};

const supportedLocales = Object.keys(dictionaries) as SupportedLocale[];

function normalizeLocaleTag(value: string): string {
  return String(value || "")
    .trim()
    .replace(/_/g, "-")
    .toLowerCase();
}

export function resolveSupportedLocale(
  value: string | null | undefined,
): SupportedLocale | null {
  const normalized = normalizeLocaleTag(value || "");
  if (!normalized) {
    return null;
  }
  if (supportedLocales.includes(normalized as SupportedLocale)) {
    return normalized as SupportedLocale;
  }
  const languageCode = normalized.split("-")[0];
  if (supportedLocales.includes(languageCode as SupportedLocale)) {
    return languageCode as SupportedLocale;
  }
  return null;
}

function readStoredLocale(): SupportedLocale | null {
  if (
    typeof window === "undefined" ||
    typeof window.localStorage === "undefined"
  ) {
    return null;
  }
  try {
    return resolveSupportedLocale(window.localStorage.getItem(localeStorageKey));
  } catch {
    return null;
  }
}

export function resolveSystemLocale(): SupportedLocale {
  const preferredLocaleCandidates =
    typeof navigator === "undefined"
      ? []
      : Array.isArray(navigator.languages) && navigator.languages.length > 0
        ? navigator.languages
        : [navigator.language];
  for (const candidate of preferredLocaleCandidates) {
    const matchedLocale = resolveSupportedLocale(candidate);
    if (matchedLocale) {
      return matchedLocale;
    }
  }
  return "en";
}

function resolveInitialLocale(): SupportedLocale {
  return readStoredLocale() ?? resolveSystemLocale();
}

let currentLocale: SupportedLocale = resolveInitialLocale();

export function getCurrentLocale(): SupportedLocale {
  return currentLocale;
}

export function setCurrentLocale(locale: SupportedLocale): SupportedLocale {
  currentLocale = resolveSupportedLocale(locale) ?? "en";
  if (
    typeof window !== "undefined" &&
    typeof window.localStorage !== "undefined"
  ) {
    try {
      window.localStorage.setItem(localeStorageKey, currentLocale);
    } catch {
      // Ignore localStorage write failures and keep the in-memory locale.
    }
  }
  return currentLocale;
}

export function getTranslationStrings(
  locale: SupportedLocale = currentLocale,
): TranslationDictionary {
  return dictionaries[locale] ?? en;
}

export function getSupportedLocaleOptions(): Array<{
  value: SupportedLocale;
  label: string;
}> {
  return supportedLocales.map((locale) => ({
    value: locale,
    label: localeLabels[locale],
  }));
}

export { en, type TranslationDictionary };
