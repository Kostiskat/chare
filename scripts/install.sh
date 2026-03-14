#!/bin/bash
set -e

cd "$(dirname "$0")/.."

echo "(1/3) configuring the build environment"

# make a dedicated build dir
mkdir -p build
cd build

sudo apt install qrencode -y

cmake ..

echo "(2/3) compiling chare..."
cmake --build .

echo "(3/3) installing to /usr/local/bin/ (sudo permissions required)"
sudo cp chare /usr/local/bin/

echo "chare is installed!"