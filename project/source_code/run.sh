#!/usr/bin/env bash

#Name of the script
SCRIPT=$( basename "$0" )

#Current version
VERSION="0.1 - WORK IN PROGRESS BUGS EXPECTED"

function usage
{
  local txt=(
    "Script $SCRIPT that enables only executing simulation or rebuilding it and then executing"
    "Usage: bash $SCRIPT [options]"
    ""
    "Options:"
    "  --help,    -h  Print help"
    "  --version, -v  Script version"
    "  --build,   -b  Rebuild old version"
    "  --run,     -r  Run without rebuild"
  )
  printf "%s\n" "${txt[@]}"
}

#When bad usage

function badUsage
{
  local message="$1"
  local txt=(
    "Invalid argument"
    # "For an overview of the avalaible commands, execute:"
    # "$SCRIPT --help"
  )
  [[ $message ]] && printf "$message\n"

  printf "%s\n" "${txt[@]}"
  printf "\n" 
  usage

}

function version
{
  local txt=(
    "$SCRIPT version $VERSION"
  )
  printf "%s\n" "${txt[@]}"
  
}

function build
{
  local txt=(
    "Removing old ./build file, creating a new one and executing CMakeLists"
  )
  printf "%s\n" "${txt[@]}"

  if [ -d "build" ]; then
    rm -rf build
  fi
  mkdir build
  cd build
  cmake ..
  make
  run
  
}

function run
{
  local txt=(
    "Executing simulation in separate terminal tabs"
  )
  printf "%s\n" "${txt[@]}"
  cd build
  gnome-terminal --tab --title="input_handler" -e "./input_handler/input_handler" --tab --title="drivetrain" -e "./drivetrain/drivetrain" --tab --title="output_handler" -e "./output_handler/output_handler"

  
}

while (( $# ))
do
    case "$1" in
      --help | -h)
          usage
          exit 0
      ;;
      --version | -v)
          version
          exit 0
      ;;
      --run | -r)
          run
          exit 0
      ;;
      --build | -b)
          build
          exit 0
      ;;

      *)
        badUsage #"Option/command not recognized"
        exit 1
      ;;
#more functionality
    esac
done

badUsage
exit 1