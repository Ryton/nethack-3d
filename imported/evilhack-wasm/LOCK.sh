#!/bin/bash
# Make all .o files in the project immutable
find . -name '*.o' -exec chattr +i {} \;
echo "All .o files are now immutable (locked)."