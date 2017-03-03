#! /bin/sh

FILE_PATH="$(find `pwd` -name librubik3d.so)"
LIB_PATH="$(dirname $FILE_PATH)"
echo $2
export LD_LIBRARY_PATH=$LIB_PATH ; $1 "$2"
