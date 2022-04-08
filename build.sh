rm -rf build
mkdir build && cd build   # make a build directory
conan install .. # conan install packages
cmake .. -GNinja -DCMAKE_BUILD_TYPE=Release # use ninja as a generator
ninja  # build with ninja
cd bin && ./Novek --help # project name
cd ../../ # go back home