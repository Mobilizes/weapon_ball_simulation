#!/bin/bash

build_result=$(cmake -S . -B build && cd build && make)

STATUS=$?

if [ $STATUS -ne 0 ]; then
  echo "Compilation failed with exit code $STATUS!"
  exit 1
fi

echo "Compilation success!"
exit 0
