#!/usr/bin/env bash

set -e
CMAKE_CONFIG_OPTS="-DCMAKE_BUILD_TYPE=Debug"
CMAKE_TOOLCHAIN_OPTS="-DCMAKE_TOOLCHAIN_FILE='$(pwd)/tools/polly/gcc-pic.cmake' '$(pwd)/tools/polly/sanitize-address.cmake'"
CMAKE_OPTS="$CMAKE_CONFIG_OPTS $CMAKE_TOOLCHAIN_OPTS"

export VECTORS_PATH="vectors.txt"
export VECTORS_COUNT=33000000
export VECTORS_DIMS=3

python "$(pwd)/scripts/generator.py"

cmake -H. -B_builds/sync -DMTHREADING_CALC=OFF "$CMAKE_OPTS"
cmake --build _builds/sync --target stress_tests
cmake -H. -B_builds/mthreading -DMTHREADING_CALC=ON "$CMAKE_OPTS"
cmake --build _builds/mthreading --target stress_tests

echo "Not use multithreading: "
./_builds/sync/tests/stress_tests/stress_tests $VECTORS_COUNT $VECTORS_DIMS $VECTORS_PATH
echo "Use multithreading: "
./_builds/mthreading/tests/stress_tests/stress_tests $VECTORS_COUNT $VECTORS_DIMS $VECTORS_PATH
