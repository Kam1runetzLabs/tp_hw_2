#!/usr/bin/env bash

set -e
CMAKE_CONFIG_OPTS="-DCMAKE_BUILD_TYPE=Debug"
CMAKE_TOOLCHAIN_OPTS="-DCMAKE_TOOLCHAIN_FILE='$(pwd)/tools/polly/gcc-pic.cmake'"
CMAKE_OPTS="$CMAKE_CONFIG_OPTS $CMAKE_TOOLCHAIN_OPTS"

export VECTORS_PATH="vectors.txt"
export VECTORS_COUNT=33
export VECTORS_DIMS=3

python "$(pwd)/scripts/generator.py"

cmake -H. -B_builds -DMTHREADING_CALC=OFF "$CMAKE_OPTS"
mv vectors.txt _builds/tests/stress_tests
cmake --build _builds
echo "Not use multithreading: "
./_builds/tests/stress_tests/stress_tests $VECTORS_COUNT $VECTORS_DIMS $VECTORS_PATH

cmake -H. -B_builds -DMTHREADING_CALC=ON "$CMAKE_OPTS"
cmake --build _builds
echo "Use multithreading: "
./_builds/tests/stress_tests/stress_tests $VECTORS_COUNT $VECTORS_DIMS $VECTORS_PATH
