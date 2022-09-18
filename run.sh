#!/bin/bash

mkdir -p bin
g++ -D_DEBUG -g main/*.cpp lib/*.cpp lib/math/*.cpp -O0 -o bin/cpu_raytracer.exe && ./bin/cpu_raytracer
