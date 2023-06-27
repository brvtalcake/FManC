#!/bin/bash

rm -rf $1/*

if [ -z "$1" ]; then
    echo "Destination directory is not specified"
    exit 1
fi

if [ ! -d "$1" ]; then
    echo "Destination directory does not exist"
    exit 1
fi

rsync --quiet -av -f"+ */" -f"- *" "src/" "$1"