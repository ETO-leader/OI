#!/bin/bash
g++ -O2 -o grader grader.cpp Anna.cpp Bruno.cpp -Wall -fsanitize=address,undefined -std=c++26