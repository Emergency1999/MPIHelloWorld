#!/bin/bash
set -e

function usage {
    echo "Usage: $0 <file.c> <processes number>"
    exit 1
}


# check first argument is given
if [ -z "$1" ]; then
    echo "Error: No file given"
    usage
fi
in=$1

# check if second argument is given
if [ -z "$2" ]; then
    processes=4
else
    # check if second argument is a number
    if ! [[ "$2" =~ ^[0-9]+$ ]]; then
        echo "Error: $2 is not a number"
        usage
    fi
    processes=$2
fi


# check first argument is a C file
if [ ! -f "$in" ]; then
    echo "Error: $in is not a file"
    usage
fi

# change .c to .out
out=_${1%.c}.out

# build
echo "[ BUILD ] Building $in"
mpicc $in -o $out

# run
echo "[  RUN  ] Running $out with $processes processes"
/usr/bin/mpirun -np $processes $out

echo "[       ] Done"
