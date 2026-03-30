import { en, type TranslationDictionary } from "./locales/en";

export type SupportedLocale = "en";

const dictionaries: Record<SupportedLocale, TranslationDictionary> = {
  en,
};

export function getTranslationStrings(
  locale: SupportedLocale = "en",
): TranslationDictionary {
  return dictionaries[locale] ?? en;
}

export { en, type TranslationDictionary };
