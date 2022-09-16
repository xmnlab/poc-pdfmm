#!/usr/bin/env bash

PROJECT_PATH="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && cd .. && pwd )"
CODE_PATH=${PROJECT_PATH}/poc-pdfmm

set -ex

clang-tidy \
    --config-file="${PROJECT_PATH}/.clang-tidy" \
    --header-filter="${CONDA_PREFIX}/include" \
    --extra-arg="-I${CODE_PATH}/include" \
    -p=build \
    ${CODE_PATH}/**/*.cpp \
    ${CODE_PATH}/**/*.h
