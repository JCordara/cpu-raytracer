#!/bin/bash

mkdir -p bin/tests
g++ tests/test_main.cpp lib/*.cpp -o bin/tests/cpu_raytracer_tests.exe && ./bin/tests/cpu_raytracer_tests
