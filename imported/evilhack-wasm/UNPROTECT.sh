#!/bin/sh
# Remove immutable flag from native tools so they can be updated or rebuilt
sudo chattr -i EvilHack-0.9.2/util/makedefs EvilHack-0.9.2/util/lev_comp EvilHack-0.9.2/util/dgn_comp EvilHack-0.9.2/util/dlb EvilHack-0.9.2/util/tilemap
