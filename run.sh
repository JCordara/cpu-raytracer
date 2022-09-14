#!/bin/bash

mkdir -p bin
g++ main/*.cpp lib/*.cpp -o bin/cpu_raytracer.exe && ./bin/cpu_raytracer
