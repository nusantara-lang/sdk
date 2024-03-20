#!/bin/bash

if [[ $1 -gt 0 ]] then
    clang-format-$1 -i src/**/*.cc src/*.cc
    clang-format-$1 -i include/**/*.h
    clang-format-$1 -i test/*.cc
else
    clang-format -i src/**/*.cc src/*.cc
    clang-format -i include/**/*.h
    clang-format -i test/*.cc
fi