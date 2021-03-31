#!/usr/bin/env bash

set -e
CMAKE_CONFIG_OPTS="-DCMAKE_BUILD_TYPE=Debug"
CMAKE_TOOLCHAIN_OPTS="-DCMAKE_TOOLCHAIN_FILE='$(pwd)/tools/polly/gcc-pic.cmake' '$(pwd)/tools/polly/sanitize-address.cmake'"
CMAKE_OPTS="$CMAKE_CONFIG_OPTS $CMAKE_TOOLCHAIN_OPTS"

export VECTORS_PATH="vectors.txt"
export VECTORS_COUNT=33000000
export VECTORS_DIMS=3

echo "Generating vectors file..."
python "$(pwd)/scripts/generator.py"

cmake -H. -B_builds -DMTHREADING_CALC=ON "$CMAKE_OPTS"
cmake --build _builds --target stress_tests
mthreading="$(./_builds/tests/stress_tests/stress_tests $VECTORS_COUNT $VECTORS_DIMS $VECTORS_PATH)"

rm -rf _builds
cmake -H. -B_builds -DMTHREADING_CALC=OFF "$CMAKE_OPTS"
cmake --build _builds --target stress_tests
not_mthreading="$(./_builds/tests/stress_tests/stress_tests $VECTORS_COUNT $VECTORS_DIMS $VECTORS_PATH)"

echo "Not use multithreading: "
echo "$not_mthreading"
echo "Use multithreading: "
echo "$mthreading"
