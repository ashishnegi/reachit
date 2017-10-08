#!/bin/bash

# do for one time setup.
# sudo apt-get install libgtk-3-dev build-essential checkinstall
# tar -xvf wxWidgets-3.1.0.tar.bz2
# mkdir -p wxWidgets-3.1.0/{build_debug,build_release}
# cd wxWidgets-3.1.0/build_debug
# ../configure --disable-shared --enable-unicode --enable-debug --enable-debug_gdb
# cd ../build_release
# export CXXFLAGS="-ffunction-sections -fdata-sections -Os"
# export LDFLAGS="-Wl,--gc-sections"
# ../configure --disable-shared --enable-unicode --disable-debug
# make -j8

## windows.
# debug :
# ../configure --disable-shared --enable-unicode --enable-debug --enable-debug_gdb -C --host=i686-w64-mingw32 --build=i686-pc-cygwin
# i686-w64-mingw32-g++ -O0 -ggdb  binReach.cpp `wx-config --cxxflags --libs std` -Wall -o program -static-libgcc -static-libstdc++ -Wl,-Bstatic,-lstdc++,-lpthread -Wl,-Bdynamic

# release :
# ../configure --disable-shared --enable-unicode --enable-debug --enable-debug_gdb -C --host=i686-w64-mingw32 --build=i686-pc-cygwin
# i686-w64-mingw32-g++ -Os binReach.cpp `wx-config --cxxflags --libs std` -Wall -o program -static-libgcc -static-libstdc++ -Wl,-Bstatic,-lstdc++,-lpthread -Wl,-Bdynamic
# source set_project.sh && i686-w64-mingw32-g++ $CXXFLAGS  binReach.cpp `wx-config --cxxflags --libs std` -Wall -o program -static-libgcc -static-libstdc++ -Wl,--gc-sections,-Bstatic,-lstdc++,-lpthread -Wl,-Bdynamic
# strip -s program.exe
# mv program.exe bin/win/release/reachit.exe

## vs code debugging in windows.
# -exec set substitute-path /cygdrive/c/Users /Users
# -exec set substitute-path ../src /Users/ashish/work/reachit/wxWidgets-3.1.0/src

# mac
# build with --disable-mediactrl
# g++ -mmacosx-version-min=10.7 binReach.cpp `wx-config --cxxflags --libs std` -o program


export PATH=$PATH:./wxWidgets-3.1.0/build_debug

## making gifs
# sudo apt-get install byzanz key-mon
# key-mon
# byzanz-record --delay=3 --duration=15 --x=0 --y=0 --width=2700 --height=1400 demo.gif
