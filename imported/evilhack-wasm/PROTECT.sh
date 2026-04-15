#!/bin/sh
# Make native tools immutable to protect them from deletion/overwrite during build
sudo chattr +i EvilHack-0.9.2/util/makedefs EvilHack-0.9.2/util/lev_comp EvilHack-0.9.2/util/dgn_comp EvilHack-0.9.2/util/dlb EvilHack-0.9.2/util/tilemap
