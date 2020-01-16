#!/bin/bash

if [ -d ../../output/linux ]; then
    rm -r ../../output/linux
fi

mkdir -p ../../output/linux

g++ -O0 -Wall -std=c++17 -c -g -I../../main/headers ../../snake/snake.cpp -o ../../output/linux/snake.o
g++ -shared -o ../../output/linux/snake.so ../../output/linux/snake.o
rm ../../output/linux/snake.o

g++ -O0 -Wall -std=c++17 -c -g -I../../main/headers ../../tictactoe/tictactoe.cpp -o ../../output/linux/tictactoe.o
g++ -shared -o ../../output/linux/tictactoe.so ../../output/linux/tictactoe.o
rm ../../output/linux/tictactoe.o


g++ -O0 -Wall -std=c++17 -g -I../../main/headers ../../main/linux/main.cpp -o ../../output/linux/MiniGames.a -ldl
