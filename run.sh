#!/bin/bash

set -u  


if [ $# -eq 0 ]; then      
    g++ -std=c++17 source/src/finder.cc source/src/find.cc -o source/src/finder.exe    
elif [ "$1" == "multi" ]; then
    echo "Executing multi-threaded version..."
    g++ -std=c++17 source/src/efficientFinder.cc source/src/find.cc source/src/threadPool.cc  -o source/src/finder.exe 
fi

source/src/finder.exe

