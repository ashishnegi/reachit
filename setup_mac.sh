tar -xvf wxWidgets-3.1.0.tar.bz2
mkdir -p wxWidgets-3.1.0/{build_debug,build_release}
cd wxWidgets-3.1.0/build_debug
../configure --disable-shared --enable-unicode --enable-debug --enable-debug_gdb
make -j8

cd ../..
export PATH=$PATH:./wxWidgets-3.1.0/build_debug

## if build fails. add --disable-mediactrl to ../configure command
# ../configure --disable-shared --enable-unicode --enable-debug --enable-debug_gdb --disable-mediactrl

# back to project root.
# use this command to build :
g++ -mmacosx-version-min=10.7 binReach.cpp `wx-config --cxxflags --libs std` -o reachit
