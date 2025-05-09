#!/usr/bin/bash

if [ $# -ne 1 ]; then
  echo "Usage: $0 <executable>"
  exit 1
fi

executable="$1"

# Ensure the provided argument is an executable
if ! [ -x "$executable" ]; then
  echo "Error: $executable is not a valid executable."
  exit 2
fi

sorted_cnt=0;
for count in {1..100}
  do 

  # Capture the output of the executable
  input=$($executable)

  # Convert the output into an array
  numbers=($input)

  # Check if the array is sorted
  is_sorted=true
  for ((i = 1; i < ${#numbers[@]}; i++)); do
    if ((numbers[i] < numbers[i-1])); then
      is_sorted=false
      break
    fi
  done

  # Output result
  if $is_sorted; then
    echo "The array is sorted."
    ((sorted_cnt++))
  else
    echo "The array is not sorted."
  fi
done
echo "Sorted results: ${sorted_cnt}"

