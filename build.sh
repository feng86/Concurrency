set -o errexit

if [[ ! -d build ]]; then {
    mkdir build
} fi
cd build

BUILD_TYPE=DEBUG
cmake -D CMAKE_BUILD_TYPE=${BUILD_TYPE} ..
make -j32 VERBOSE=1
