#!/bin/bash

set -u

g++ -std=c++17 source/src/finder.cc source/src/find.cc -o source/src/finder.exe

source/src/finder.exe > Results.txt
