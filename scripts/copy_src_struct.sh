#!/bin/bash

rm -rf ./include/*

if [ -z "$1" ]; then
    echo "Destination directory is not specified"
    exit 1
fi

if [ ! -d "$1" ]; then
    echo "Destination directory does not exist"
    exit 1
fi

rsync -av -f"+ */" -f"- *" "src/" "$1"