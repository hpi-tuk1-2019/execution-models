#!/bin/bash


export COMPILERVARS_ARCHITECTURE=intel64
export COMPILERVARS_PLATFORM=linux
source /opt/intel/compilers_and_libraries_2019.4.243/linux/bin/compilervars.sh
export CMAKE_CXX_COMPILER=/opt/intel/compilers_and_libraries_2019.4.243/linux/bin/intel64/icc
export CMAKE_C_COMPILER=/opt/intel/compilers_and_libraries_2019.4.243/linux/bin/intel64/icc
