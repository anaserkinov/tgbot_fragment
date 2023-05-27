CURRENT_DIR=$(pwd)

cd ../sqlite_cpp
mkdir -p build && cd build

cmake ..
make
make install

cd "$CURRENT_DIR"