#!/bin/bash

mkdir -p bin
g++ -Wall -D_DEBUG -g main/*.cpp lib/*.cpp lib/math/*.cpp -s -Os -o bin/cpu_raytracer.exe && ./bin/cpu_raytracer
