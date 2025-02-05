#!/bin/bash

set -u

g++ -std=c++17 source/src/finder.cc source/src//find.cc -o source/finder.exe
./source/finder