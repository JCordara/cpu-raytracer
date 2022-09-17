#!/usr/bin/env python

import os
import sys
import hashlib
import time

def build():
    os.system("g++ -D_DEBUG -g main\\*.cpp lib\\*.cpp -o bin\\cpu_raytracer.exe")

def run():
    os.system(".\\bin\\cpu_raytracer.exe >nul")

def md5(fname):
    hash_md5 = hashlib.md5()
    with open(fname, "rb") as f:
        for chunk in iter(lambda: f.read(4096), b""):
            hash_md5.update(chunk)
    return hash_md5.hexdigest()

def main():
    last_checksum = md5("main\\main.cpp")
    while(True):
        current_checksum = md5("main\\main.cpp")
        if current_checksum != last_checksum:
            last_checksum = current_checksum
            build()
        else:
            time.sleep(0.5)
        run()

if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt as e:
        print("\nStopping...")
        sys.exit(0)