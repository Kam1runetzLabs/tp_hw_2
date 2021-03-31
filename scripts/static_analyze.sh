#!/usr/bin/env bash

C_CPPCHECK_OPTIONS="--language=c --std=c11 --verbose "
CXX_CPPCHECK_OPTIONS="--language=c++ --std=c++11 --verbose "

cppcheck $C_CPPCHECK_OPTIONS --xml --xml-version=2 ./src 2>stat-analyze-report-src.xml
cppcheck $CXX_CPPCHECK_OPTIONS --xml --xml-version=2 ./tests 2>stat-analyze-report-tests.xml
