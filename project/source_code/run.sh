#!/usr/bin/env bash

A=$1

if(( A == 1 )); then
  if [ -d "build" ]; then
    rm -rf build
  fi
  mkdir build
  cd build
  cmake ..
  make
else
  cd build
fi



gnome-terminal --tab --title="input_handler" -e "./input_handler/input_handler" --tab --title="drivetrain" -e "./drivetrain/drivetrain" --tab --title="output_handler" -e "./output_handler/output_handler"
