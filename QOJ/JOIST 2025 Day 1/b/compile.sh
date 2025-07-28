#!/bin/bash
g++ -std=c++26 -O2 -o grader grader.cpp Anna.cpp Bruno.cpp -Wall -fsanitize=address,undefined -g