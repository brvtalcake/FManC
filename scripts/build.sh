#!/bin/bash
function notdir() {
    echo $(basename $1)
}

command="make_latest -j$1 --jobserver-style=pipe $2"

if [ -z "$1" ]; then
    echo "Usage: $0 <job_count> <target>"
    exit 1
fi

# test if $1 is a positive integer
if ! [[ $1 =~ ^[0-9]+$ ]] ; then
    echo "Error: job_count must be a positive integer"
    exit 1
fi

if [ -z "$2" ]; then
    command="make_latest -j$1 --jobserver-style=pipe"
fi

# run cog only if 'clean' is not in $2
if [[ $2 != *"clean"* ]]; then
    # Run cog on all files in src/ and src/'s subdirectories
#    COG_OUT_DIR=obj/cog_processed/
#
#    COG_FILES=($(find src/ -type f -name '*.c' -printf '%P\n') $(find src/ -type f -name '*.h' -printf '%P\n') $(find src/ -type f -name '*.cpp' -printf '%P\n') $(find src/ -type f -name '*.hpp' -printf '%P\n'))
#
#    for file in "${COG_FILES[@]}"; do
#        rm -f $COG_OUT_DIR$file
#        echo "cog -d -o $COG_OUT_DIR$file src/$file"
#        cog -d -o $COG_OUT_DIR$file src/$file
#    done
    python3 -OO ./scripts/build.py
fi

# Run the command
$command