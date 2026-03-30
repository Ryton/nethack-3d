import { en, type TranslationDictionary } from "./locales/en";
import { esOverrides } from "./locales/es";
import { ptBrOverrides } from "./locales/pt-br";
import { zhCnOverrides } from "./locales/zh-cn";
import { mergeTranslations } from "./locale-helpers";

export type SupportedLocale = "en" | "es" | "pt-br" | "zh-cn";

const dictionaries: Record<SupportedLocale, TranslationDictionary> = {
  en,
  es: mergeTranslations(en, esOverrides),
  "pt-br": mergeTranslations(en, ptBrOverrides),
  "zh-cn": mergeTranslations(en, zhCnOverrides),
};

const localeStorageKey = "nh3d-locale";

const localeLabels: Record<SupportedLocale, string> = {
  en: "English",
  es: "Español",
  "pt-br": "Português (Brasil)",
  "zh-cn": "简体中文",
};

const supportedLocales = Object.keys(dictionaries) as SupportedLocale[];

function normalizeLocaleTag(value: string): string {
  return String(value || "")
    .trim()
    .replace(/_/g, "-")
    .toLowerCase();
}

const localeAliases: Record<string, SupportedLocale> = {
  es: "es",
  "es-es": "es",
  "es-mx": "es",
  "es-419": "es",
  "es-us": "es",
  pt: "pt-br",
  "pt-br": "pt-br",
  "pt-pt": "pt-br",
  zh: "zh-cn",
  "zh-cn": "zh-cn",
  "zh-hans": "zh-cn",
  "zh-hans-cn": "zh-cn",
};

export function resolveSupportedLocale(
  value: string | null | undefined,
): SupportedLocale | null {
  const normalized = normalizeLocaleTag(value || "");
  if (!normalized) {
    return null;
  }
  const alias = localeAliases[normalized];
  if (alias) {
    return alias;
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
