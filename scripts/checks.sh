#!/usr/bin/env bash

set -e

export CTEST_OUTPUT_ON_FAILURE=true
export ASAN_OPTIONS=allocator_may_return_null=1
export TSAN_OPTIONS=allocator_may_return_null=1


# address sanitizer
CMAKE_CONFIG_OPTIONS="-DHUNTER_CONFIGURATION_TYPES=Debug -DCMAKE_BUILD_TYPE=Debug"
CMAKE_TOOLCHAIN_OPTIONOS="-DCMAKE_TOOLCHAIN_FILE='$(pwd)/tools/polly/sanitize-address.cmake'"
CMAKE_OPTIONS="$CMAKE_CONFIG_OPTIONS $CMAKE_TOOLCHAIN_OPTIONS"

cmake -H. -B_builds/sanitize_address $CMAKE_OPTIONS
cmake --build _builds/sanitize_address
./_builds/sanitize_address/tests/unit_tests/unit_tests


# thread sanitizer
CMAKE_CONFIG_OPTIONS="-DHUNTER_CONFIGURATION_TYPE=Debug -DCMAKE_BUILD_TYPE=Debug"
CMAKE_TOOLCHAIN_OPTIONS="-DCMAKE_TOOLCHAIN_FILE='$(pwd)/tools/polly/sanitize-thread.cmake'"
CMAKE_OPTIONS="$CMAKE_TOOLCHAIN_OPTIONS $CMAKE_CONFIG_OPTIONS"

cmake -H. -B_builds/sanitize_thread $CMAKE_OPTIONS
cmake --build _builds/sanitize_thread
./_builds/sanitize_thread/tests/unit_tests/unit_tests


# valgrind memcheck
CMAKE_CONFIG_OPTIONS="-DHUNTER_CONFIGURATION_TYPE=Debug -DCMAKE_BUILD_TYPE=Debug"
CMAKE_OPTIONS="$CMAKE_CONFIG_OPTIONS"

cmake -H. -B_builds/memcheck $CMAKE_OPTIONS
cmake --build _builds/memcheck
valgrind --tool=memcheck --leak-check=full --track-origins=yes ./_builds/memcheck/tests/unit_tests/unit_tests

