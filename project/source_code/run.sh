#!/usr/bin/env bash

#Name of the script
SCRIPT=$( basename "$0" )

#Current version
VERSION="0.2 - WORK IN PROGRESS BUGS EXPECTED"

function usage
{
  local txt=(
    "Script $SCRIPT that enables only executing simulation or rebuilding it and then executing."
    "Programs are executed in separate terminal tabs and after execution is terminated they"
    "wait for any user input to be closed."
    ""
    "Usage: bash $SCRIPT [options]"
    ""
    "Options:"
    "  --help,    -h  Print help"
    "  --version, -v  Script version"
    "  --build,   -b  Rebuild old version"
    "  --run,     -r  Run without rebuild"
    "  --doxygen, -d  Run doxygen script execution, checks if installed, if no then it does it for you"
    "  --check,   -c  Run cppcheck --enable=all"
    "  --test,    -t  Run unit tests"
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

  #fetch submodules like the google test repo
  git submodule init
  git submodule update

  mkdir build
  cd build
  cmake ..
  make
  if [ "$?" -eq 0 ]
  then
    echo "make succeeded"
    run
  else
    echo "make failed"
    echo "Check log for errors in code"
  fi


}

function run
{
  local txt=(
    "Executing simulation in separate terminal tabs"
  )
  printf "%s\n" "${txt[@]}"
  cd build
  gnome-terminal --geometry=260x25-0+0 --tab --title="input_handler" -e "bash -c './input_handler/input_handler vcan0; read -n1'" \
                                       --tab --title="drivetrain" -e "bash -c './drivetrain/drivetrain vcan0; read -n1' "
                                       #--tab --title="output_handler" -e "bash -c './output_handler/output_handler vcan0; read -n1' "
  ./utils/output_panel/app/avic/avic -c "vcan0"
}

function codecheck
{
  local txt=(
    "Running cppcheck"
  )
  printf "%s\n" "${txt[@]}"
  printf "%s\n"
  bash -c 'cppcheck --enable=all -I drivetrain/include/ -I utils/include -I input_handler/include \
            drivetrain/src drivetrain/include utils/src utils/include input_handler/src input_handler/include'

  REQUIRED_PKG="llvm clang clang-tools"
  PKG_OK=$(dpkg-query -W --showformat='${Status}\n' $REQUIRED_PKG|grep "install ok installed")
  echo "Checking for $REQUIRED_PKG: $PKG_OK"
  if [ "" = "$PKG_OK" ]; then
    echo "No $REQUIRED_PKG. Setting up $REQUIRED_PKG."
    sudo apt-get --yes install $REQUIRED_PKG
  fi
  if [ -d "build_codecheck" ]; then
    rm -rf build_codecheck
  fi
  mkdir build_codecheck
  cd build_codecheck
  local txt=(
    "Running Clang Analyzer"
  )
  printf "%s\n" "${txt[@]}"
  printf "%s\n"
  scan-build cmake ..
  scan-build -o scanbuild/ make


  REQUIRED_PKG="clang-tidy"
  PKG_OK=$(dpkg-query -W --showformat='${Status}\n' $REQUIRED_PKG|grep "install ok installed")
  echo "Checking for $REQUIRED_PKG: $PKG_OK"
  if [ "" = "$PKG_OK" ]; then
    echo "No $REQUIRED_PKG. Setting up $REQUIRED_PKG."
    sudo apt-get --yes install $REQUIRED_PKG
  fi
  local txt=(
    "Running Clang Tidy"
  )
  printf "%s\n" "${txt[@]}"
  printf "%s\n"
  cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ..
  clang-tidy -p .  $(find ../drivetrain/src/ -name *.cpp) $(find ../drivetrain/include/ -name *.h) \
                   $(find ../input_handler/src/ -name *.cpp) $(find ../input_handler/include/ -name *.h) \
                   $(find ../utils/src/ -name *.cpp) $(find ../utils/include -name *.h) \
                   --checks=* --export-fixes=fixes.yml >> output.txt
}


function doxygen
{
  local txt=(
    "Executing doxygen script"
  )
  printf "%s\n" "${txt[@]}"
  cd ..
  cd documents
  cd doxygen_code_documentation
  if [ -d "html" ]; then
    echo removing html folder
    rm -rf html
  fi
  if [ -d "latex" ]; then
    echo removing latex folder
    rm -rf latex
  fi

  REQUIRED_PKG="doxygen"
  PKG_OK=$(dpkg-query -W --showformat='${Status}\n' $REQUIRED_PKG|grep "install ok installed")
  echo Checking for $REQUIRED_PKG: $PKG_OK
  if [ "" = "$PKG_OK" ]; then
    echo "No $REQUIRED_PKG. Setting up $REQUIRED_PKG."
    sudo apt-get --yes install $REQUIRED_PKG
  fi

  gnome-terminal --geometry=260x25-0+0 --tab --title="input_handler" -e "bash -c 'doxygen'"

  firefox html/index.html

}

function test
{
  local txt=(
    "Executing unit tests"
  )
  printf "%s\n" "${txt[@]}"

  ./build/drivetrain/test/engine_test
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
      --doxygen | -d)
          doxygen
          exit 0
      ;;
      --check | -c)
          codecheck
          exit 0
      ;;
      --test | -t)
          test
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