#!/bin/bash
rm build -rf
cmake -S . -B build -G "Ninja"
