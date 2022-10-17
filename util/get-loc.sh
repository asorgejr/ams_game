#!/usr/bin/env bash
# use cloc to count lines of code in project.

# project dir = script dir/../
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# use cloc to get lines of code in multiple dirs
EXCL_DIRS="build,third_party,cmake,cmake-build-debug,cmake-build-release,cmake-build-relwithdebinfo,cmake-build-minsize,.idea,.git,.vscode,.vs"

# get lines of code in project
cloc --exclude-dir=$EXCL_DIRS "${DIR}/../"
