#!/bin/bash

# do for one time setup.
# sudo apt-get install libgtk-3-dev build-essential checkinstall
# tar -xvf wxWidgets-3.1.0.tar.bz2
# mkdir wxWidgets-3.1.0/gtk_build
# cd wxWidgets-3.1.0/{gtk_build,gtk_build_release}
# ../configure --disable-shared --enable-unicode --enable-debug --enable-debug_gdb
# cd ../gtk_build_release
# export CXXFLAGS="-ffunction-sections -fdata-sections -Os"
# export LDFLAGS="-Wl,--gc-sections"
# ../configure --disable-shared --enable-unicode --disable-debug
# make -j8

export PATH=$PATH:./wxWidgets-3.1.0/gtk_build_release
