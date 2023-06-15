#!/bin/bash

command="make_latest -j$1 --jobserver-style=pipe $2"

if [ -z "$1" ]; then
    echo "Usage: $0 <jobs> <target>"
    exit 1
fi

if [ -z "$2" ]; then
    command="make_latest -j$1 --jobserver-style=pipe"
fi

# Run the command
$command