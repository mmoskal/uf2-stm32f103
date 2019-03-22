#!/bin/sh

./bmp.sh > build/debug.gdb
arm-none-eabi-gdb --command=build/debug.gdb
