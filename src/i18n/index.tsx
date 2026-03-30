import {
  createContext,
  useContext,
  useMemo,
  useState,
  type PropsWithChildren,
} from "react";
import {
  en,
  getTranslationStrings,
  type SupportedLocale,
  type TranslationDictionary,
} from "./core";

type I18nContextValue = {
  locale: SupportedLocale;
  setLocale: (locale: SupportedLocale) => void;
  strings: TranslationDictionary;
};

const I18nContext = createContext<I18nContextValue>({
  locale: "en",
  setLocale: () => undefined,
  strings: en,
});

export function TranslationProvider({
  children,
  initialLocale = "en",
}: PropsWithChildren<{ initialLocale?: SupportedLocale }>): JSX.Element {
  const [locale, setLocale] = useState<SupportedLocale>(initialLocale);
  const strings = useMemo(() => getTranslationStrings(locale), [locale]);

  return (
    <I18nContext.Provider
      value={{
        locale,
        setLocale,
        strings,
      }}
    >
      {children}
    </I18nContext.Provider>
  );
}

export function useI18n(): I18nContextValue {
  return useContext(I18nContext);
}
