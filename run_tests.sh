#!/bin/bash

mkdir -p bin/tests
g++ -D_DEBUG -g tests/test_main.cpp lib/*.cpp lib/math/*.cpp -o bin/tests/cpu_raytracer_tests.exe && ./bin/tests/cpu_raytracer_tests
