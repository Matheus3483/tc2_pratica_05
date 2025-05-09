#!/bin/bash
MAINFILE="$1"
EXECNAME="$2"
if ls *.o >/dev/null 2>&1; then
    rm ./*.o
fi
gcc -c -I../INC/ ../INC/*.c  ./$MAINFILE
gcc -I../INC/ ./*.o -o ./$EXECNAME
if ls *.o >/dev/null 2>&1; then
    rm ./*.o
fi