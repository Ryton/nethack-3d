// Node.js script to check WASM exports vs required entrypoints
// Usage: node scripts/wasm/check-evilhack-exports.mjs

import path from 'path';
import { fileURLToPath } from 'url';
import fs from 'fs';

// List of required entrypoints (from previous EvilHack/SLASHEM mapping)
const requiredEntrypoints = [
  'hack_init',
  'hack_exit',
  'hack_tick',
  'hack_key',
  'hack_mouse',
  'hack_save',
  'hack_restore',
  'hack_resize',
  'hack_clipboard',
  'hack_debug',
  'malloc',
  'free',
  'realloc',
  'memcpy',
  'memset',
  // Add more if needed
];

// Path to EvilHack JS glue and WASM
const evilhackJs = path.resolve('public/evilhack.js');

async function main() {
  if (!fs.existsSync(evilhackJs)) {
    console.error('evilhack.js not found!');
    process.exit(1);
  }

  let EvilHackModule;
  try {
    EvilHackModule = (await import('file://' + evilhackJs)).default;
  } catch (e) {
    console.error('Failed to import evilhack.js:', e);
    process.exit(1);
  }

  let instance;
  try {
    instance = await EvilHackModule();
  } catch (e) {
    console.error('Failed to instantiate EvilHackModule:', e);
    process.exit(1);
  }

  const exports = Object.keys(instance).sort();
  console.log('--- EvilHack WASM Exports ---');
  console.log(exports.join('\n'));

  // Compare with required entrypoints
  const missing = requiredEntrypoints.filter(fn => !exports.includes(fn));
  const extra = exports.filter(fn => !requiredEntrypoints.includes(fn));

  console.log('\n--- Missing Entrypoints ---');
  if (missing.length) console.log(missing.join('\n'));
  else console.log('None!');

  console.log('\n--- Extra Exports ---');
  if (extra.length) console.log(extra.join('\n'));
  else console.log('None!');
}

main();
