#!/bin/sh

cd boot

# Configure for OrangePi using Kbuild
make distclean
make orangepi_pc_defconfig

make -j all
#ToDo: Setup CROSS_COMPILER env var
