// scripts/wasm/build-evilhack.mjs
// Build EvilHack WASM/JS for NetHack-3D
// Usage: node scripts/wasm/build-evilhack.mjs
//
// Compiles EvilHack from source using emcc (Emscripten compiler).
// EvilHack source should be at ../EvilHack (same level as nethack-3d)

import { execSync } from 'child_process';
import { existsSync, mkdirSync, readdirSync, writeFileSync } from 'fs';
import path from 'path';

const projectRoot = path.resolve('.');
const outDir = path.resolve(projectRoot, 'public');
const outBase = 'evilhack';

// EvilHack source must be in a peer directory at the same level as nethack-3d
const evilhackRootDir = path.resolve(projectRoot, '..', 'EvilHack');
const evilhackSrcDir = path.join(evilhackRootDir, 'src');
const evilhackIncludeDir = path.join(evilhackRootDir, 'include');
const evilhackSysShareDir = path.join(evilhackRootDir, 'sys', 'share');

// Validate EvilHack directories
if (!existsSync(evilhackSrcDir)) {
  console.error(`
ERROR: EvilHack source not found at: ${evilhackSrcDir}

Expected directory structure:
  ../EvilHack/
    ├── src/           (C source files)
    ├── include/       (headers - should exist if build was started)
    └── sys/share/     (system-specific files)

To set up EvilHack:
  1. Clone or copy EvilHack to: ${evilhackRootDir}
  2. Run the build to generate headers:
     cd ${evilhackRootDir}
     make clean
     make
  `);
  process.exit(1);
}

if (!existsSync(evilhackIncludeDir)) {
  console.error(`
ERROR: EvilHack include directory not found at: ${evilhackIncludeDir}

The build system needs generated headers (pm.h, onames.h, etc.).
Run the EvilHack build first:
  cd ${evilhackRootDir}
  make
  `);
  process.exit(1);
}

// Create output directory if needed
if (!existsSync(outDir)) {
  mkdirSync(outDir, { recursive: true });
}

// Collect all .c files from EvilHack src directory
const cFiles = readdirSync(evilhackSrcDir)
  .filter(f => f.endsWith('.c'))
  .map(f => path.join(evilhackSrcDir, f));

// Add posixregex from sys/share if it exists (for regex support)
if (existsSync(path.join(evilhackSysShareDir, 'posixregex.c'))) {
  cFiles.push(path.join(evilhackSysShareDir, 'posixregex.c'));
}

// Add WASM shims for Unix-specific functions
const shimsPath = path.join(projectRoot, 'scripts', 'wasm', 'evilhack-wasm-shims.c');
if (existsSync(shimsPath)) {
  cFiles.push(shimsPath);
}

// Add EvilHack WASM winshim (new, analogous to winshim_367.c)
const winshimEvilPath = path.join(projectRoot, 'imported', 'evilhack-wasm', 'evilhack', 'wasm-wasm', 'win', 'winshim_evil.c');
if (existsSync(winshimEvilPath)) {
  cFiles.push(winshimEvilPath);
}

if (cFiles.length === 0) {
  console.error(`ERROR: No .c files found in ${evilhackSrcDir}`);
  process.exit(1);
}

console.log(`\n=== EvilHack WASM Build ===`);
console.log(`Found ${cFiles.length} source files to compile`);
console.log(`Include directory: ${evilhackIncludeDir}`);
console.log(`Output directory: ${outDir}\n`);

// Build emcc command with proper flags
// Reference: emscripten documentation and NetHack build conventions
//
// Includes graphics shim functions needed for NetHack 3D integration
const emccCmd = [
  'emcc',
  ...cFiles,
  '-O2',
  // Modularize to get a proper JS module
  '-s', 'MODULARIZE=1',
  '-s', 'EXPORT_NAME=EvilHackModule',
  // Export all required NetHack3D entrypoints and memory management
  '-s', 'EXPORTED_FUNCTIONS=["_hack_init","_hack_exit","_hack_tick","_hack_key","_hack_mouse","_hack_save","_hack_restore","_hack_resize","_hack_clipboard","_hack_debug","_malloc","_free","_realloc","_memcpy","_memset","_shim_graphics_set_callback","_nh_wasm_init","_nh3d_glyph_at","_nh_top_item_glyph_under_player","_recover_savefile","_resume_checkpoint_save"]',
  // Export utility functions for JS interop
  '-s', 'EXPORTED_RUNTIME_METHODS=["cwrap","ccall","getValue","setValue","stringToUTF8","UTF8ToString"]',
  // Enable async support (ASYNCIFY) for callback handling
  '-s', 'ASYNCIFY=1',
  '-s', 'ASYNCIFY_STACK_SIZE=4096',
  // Output files
  '-o', path.join(outDir, `${outBase}.js`),
  // Include paths for headers
  '-I', evilhackIncludeDir,
  '-I', evilhackSrcDir,
  // Include sys/share for regex and other utilities
  '-I', evilhackSysShareDir,
  // Suppress non-critical warnings
  '-Wno-error=unused-function',
  '-Wno-error=unused-variable',
  '-Wno-error=undefined' // Allow undefined symbols that may be resolved at runtime
].join(' ');

console.log('Build command:');
console.log('emcc \\');
cFiles.forEach(f => console.log(`  ${path.relative(projectRoot, f)} \\`));
console.log(`  [compiler flags]`);
console.log('');

try {
  execSync(emccCmd, { stdio: 'inherit', cwd: projectRoot });
  console.log('\n✓ Build successful!');
  console.log('Output:');
  console.log(`  - ${path.relative(projectRoot, path.join(outDir, `${outBase}.js`))}`);
  console.log(`  - ${path.relative(projectRoot, path.join(outDir, `${outBase}.wasm`))}`);
  console.log('');

  // Post-process: Ensure the JS module exports correctly as default export
  const jsPath = path.join(outDir, `${outBase}.js`);
  let jsContent = fs.readFileSync(jsPath, 'utf-8');

  // Check if it already has the correct export
  if (!jsContent.includes('export default')) {
    console.log('Post-processing: Adding ES module export...');
    // Ensure the module exports properly for ES modules
    if (!jsContent.endsWith('\n')) {
      jsContent += '\n';
    }
    if (!jsContent.trim().endsWith('export default Module;') && !jsContent.trim().endsWith('export default EvilHackModule;')) {
      jsContent += 'export default EvilHackModule;\n';
    }
    writeFileSync(jsPath, jsContent);
    console.log('✓ Added ES module default export');
  }

} catch (error) {
  console.error('\n✗ Build failed!');
  console.error('');
  console.error('Common issues and solutions:');
  console.error('');
  console.error('1. Missing headers (hack.h, pm.h, etc.)');
  console.error(`   Solution: cd ${evilhackRootDir} && make`);
  console.error('');
  console.error('2. Missing system functions (regex_*, dosh, dosuspend, etc.)');
  console.error('   These are Unix-specific functions not available in WASM.');
  console.error('   Solution: Comment out or stub these in the source, or');
  console.error('   adjust build flags to ignore missing symbols.');
  console.error('');
  console.error('3. Linker errors about undefined symbols');
  console.error('   Solution: Add -Wno-error=undefined-symbols to ignore them');
  console.error('');
  console.error(`4. File not found errors`);
  console.error(`   Check that source exists at: ${evilhackSrcDir}`);
  console.error('');
  process.exit(1);
}
