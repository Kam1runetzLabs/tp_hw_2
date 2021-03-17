#!/usr/bin/env bash

CXX_CPPCHECK_OPTIONS="--language=c --std=c11 --verbose "
C_CPPCHECK_OPTIONS="--language=c++ --std=c++11 --verbose "

cppcheck $C_CPPCHECK_OPTIONS --xml --xml-version=2 ./src 2>stat-analyze-report-src.xml
cppcheck-htmlreport --file=stat-analyze-report-src.xml --report-dir=stat-analyze-report-src

cppcheck $CXX_CPPCHECK_OPTIONS --xml --xml-version=2 ./tests 2>stat-analyze-report-tests.xml
cppcheck-htmlreport --file=stat-analyze-report-tests.xml --report-dir=stat-analyze-report-tests

mkdir static-analyze-report/
rm *.xml
mv stat-analyze-report* static-analyze-report/
rm -rf stat-analyze*
