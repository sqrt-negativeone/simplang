#!/usr/bin/env bash

cmake -S . -B out/buid-debug -DCMAKE_BUILD_TYPE=Debug && cmake --build out/buid-debug/