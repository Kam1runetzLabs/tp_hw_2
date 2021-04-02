#!/usr/bin/env bash

set -e
CMAKE_CONFIG_OPTS="-DCMAKE_BUILD_TYPE=Debug"
CMAKE_TOOLCHAIN_OPTS="-DCMAKE_TOOLCHAIN_FILE='$(pwd)/tools/polly/gcc-pic.cmake'"
CMAKE_OPTS="$CMAKE_CONFIG_OPTS $CMAKE_TOOLCHAIN_OPTS"

export VECTORS_PATH="vectors.txt"
export VECTORS_COUNT=33000000
export VECTORS_DIMS=3

echo "Generating vectors file..."
python "$(pwd)/scripts/generator.py"

cmake -H. -B_builds/mthreading -DMTHREADING_CALC=ON "$CMAKE_OPTS"
cmake --build _builds/mthreading --target m_v_calculating
cmake --build _builds/mthreading --target demo

cmake -H. -B_builds/sync -DMTHREADING_CALC=OFF "$CMAKE_OPTS"
cmake --build _builds/sync --target demo

echo "WITH MULTITHREADING"
./_builds/mthreading/demo/demo $VECTORS_COUNT $VECTORS_DIMS $VECTORS_PATH
sleep 1
echo ""
echo "WITHOUT MULTITHREADING"
./_builds/sync/demo/demo $VECTORS_COUNT $VECTORS_DIMS $VECTORS_PATH
