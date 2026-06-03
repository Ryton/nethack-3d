#!/bin/bash
# Make all .o files in the project mutable again
find . -name '*.o' -exec chattr -i {} \;
echo "All .o files are now mutable (unlocked)."