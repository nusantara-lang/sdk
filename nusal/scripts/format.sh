#!/bin/bash

if [[ $1 -gt 0 ]] then
    clang-format-$1 -i src/**/*.cc src/*.cc
    clang-format-$1 -i include/**/*.h
else
    clang-format -i src/**/*.cc src/*.cc
    clang-format -i include/**/*.h
fi