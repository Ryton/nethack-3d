#!/bin/bash
# Copy dungeon, dungeon.def, dungeon.pdf from native build to wasm build
dat_native="/home/mixo/repos/nethack-3d/imported/evilhack-wasm/build/EvilHack-0.9.2_native/EvilHack-0.9.2/dat"
dat_wasm="/home/mixo/repos/nethack-3d/imported/evilhack-wasm/build/EvilHack-0.9.2_wasm/EvilHack-0.9.2/dat"

for f in dungeon dungeon.def dungeon.pdf; do
  if [ -f "$dat_native/$f" ]; then
    cp -v "$dat_native/$f" "$dat_wasm/"
  else
    echo "Warning: $f not found in native build!"
  fi
done
