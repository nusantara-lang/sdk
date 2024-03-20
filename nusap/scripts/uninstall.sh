#!/bin/bash

# Script location
script_dir=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

# Read install manifest file
file_list=$(<"$script_dir/../build/install_manifest.txt")

# Uninstall function with error handling
uninstall_file() {
  if [ -f "$1" ] || [ -L "$1" ]; then
    rm -f "$1"
    echo "  - Removed file: $1"
  elif [ -d "$1" ]; then
    rm -rf "$1"
    echo "  - Removed directory: $1"
  else
    echo "  - Warning: Skipped '$1' (not a file or directory)"
  fi
}

# Uninstall process
echo "**Uninstalling nusap...**"

# Set IFS to newline to handle spaces in filenames correctly
IFS=$'\n'

for file in $(sed 's/'\''//g' <<< "$file_list"); do
  uninstall_file "$file"
done

echo "**Uninstall complete!**"