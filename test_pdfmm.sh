#!/usr/bin/env bash

function get_gcc_version() {
    gcc --version | grep -o "[0-9]*\.[0-9]*\.[0-9]*$"
}

function get_clang_version() {
    clang++ --version | grep -o "[0-9]*\.[0-9]*\.[0-9]*"
}

TEST_DIR=~/dev/conda-forge-recipes/staged-recipes/recipes/pdfmm
cd ${TEST_DIR}

GCC_INCLUDE_PATH=${CONDA_PREFIX}/x86_64-conda-linux-gnu/include/c++/$(get_gcc_version)

gcc test.cpp \
  -std=c++17 \
  -I${CONDA_PREFIX}/include \
  -I${CONDA_PREFIX}/include/pdfmm \
  -I${GCC_INCLUDE_PATH} \
  -I${GCC_INCLUDE_PATH}/x86_64-conda-linux-gnu \
  -I${CONDA_PREFIX}/lib/clang/$(get_clang_version)/include \
  -L${CONDA_PREFIX}/lib \
  -o /tmp/a.out
