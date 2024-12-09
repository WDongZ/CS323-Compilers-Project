#!/bin/bash

input_dir="/root/compiler/CS323-Compilers-Project/Project 2/input_dir"  
output_dir="./result"

mkdir -p "$output_dir"

for file_path in "$input_dir"/*.spl; do
    if [ ! -e "$file_path" ]; then
        echo "No *.spl files found in $input_dir"
        break
    fi

    file_name=$(basename "$file_path")

    echo "$file_name"

    ./a "$file_path" > "$output_dir/$file_name.out"
done