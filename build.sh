#!/bin/sh
g++ -std=c++14 -o $( echo $1 | awk '{ split($0, a, "."); print a[1]}') $1