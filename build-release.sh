#!/bin/bash

mkdir -p bin
g++ main/*.cpp lib/*.cpp lib/math/*.cpp -s -Os -ffunction-sections -fdata-sections -Wl,--gc-sections -fno-exceptions -o bin/cpu_raytracer.exe
