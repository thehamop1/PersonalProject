# Personal Project
## How to Build
- Dependencies:
  - CMake 3.18 or Newer
  - GCC 10 or newer (tested with 10 and 12)
  - Google Test

- Instructions:
  - Create build folder
    mkdir build
  - Change directory to build folder:
    cd build
  - Run this command for configuring a debug build:
    cmake -DCMAKE_BUILD_TYPE=Debug ..
  - Run this command for configuring a release build:
    cmake -DCMAKE_BUILD_TYPE=Release ..
  - Build the code like this:
    make -j

- Binaries can be found in:  lru/build/bin
- The Binary called MAIN is the coderpad example
- The Binary called LRUTEST is the gtest set from the test folder

## Problem Description

## Notes
