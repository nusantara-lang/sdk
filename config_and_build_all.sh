#!/bin/bash
cd nusal
./scripts/config.sh
cd ../nusap
./scripts/config.sh
cd ../nusai
./scripts/config.sh
cd ../nusal
./scripts/build.sh
cd ../nusap
./scripts/build.sh
cd ../nusai
./scripts/build.sh
cd ..
