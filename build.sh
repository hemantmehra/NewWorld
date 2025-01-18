#!/bin/sh

set -xe

cc main.cpp unit.cpp settlement.cpp game.cpp -o main -I/usr/local/include -L/usr/local/lib -lraylib -lstdc++
