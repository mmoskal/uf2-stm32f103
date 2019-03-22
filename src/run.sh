#!/bin/sh

set -e
make
(./bmp.sh && echo load && echo quit) > build/flash.gdb
arm-none-eabi-gdb --command=build/flash.gdb
