#! /bin/bash

if [ "$#" -eq 0 ]; then
  echo "Usage: hh <file-a> <file-b>..."
  exit 1
fi

# PATH CONSTANTS
upper_dir="/"
initial_dir=$(pwd)
target_file="project.hh"

while [ "$(pwd)" != "$upper_dir" ]; do
  if [ -e "$target_file" ]; then
    for hack_file in $@; do
      exec_path="$initial_dir/$hack_file"
      echo "### HHVM: $exec_path"
      output=$(hhvm $target_file $exec_path)
      if [ ! -z "$output" ]; then
        echo $output
      fi
    done
    exit 0
  fi

  cd ../
done

echo "ERROR: unable to locate $target_file in parent file chain."
exit 1
