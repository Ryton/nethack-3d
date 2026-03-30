import "./logging";
import { createRoot } from "react-dom/client";
import { TranslationProvider } from "./i18n";
import App from "./ui/App";
import "./styles/app.scss";

if (import.meta.hot) {
  import.meta.hot.on("vite:beforeUpdate", () => {
    window.location.reload();
  });
}

const rootElement = document.getElementById("root");
if (!rootElement) {
  throw new Error("Failed to find #root mount element");
}

createRoot(rootElement).render(
  <TranslationProvider>
    <App />
  </TranslationProvider>,
);
