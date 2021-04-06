#!/bin/sh
printf "\033c"
flags="-Wall -Wno-missing-braces -lm -O3 -Winline"
gcc main.c $flags -o main.out
