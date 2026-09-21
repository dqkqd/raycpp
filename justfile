build:
    cmake -B build
    cp ./build/compile_commands.json .
    cmake --build build

format:
    clang-format -i include/**.hpp src/**.cpp tests/**.cpp

check:
    clang-tidy include/**.hpp src/**.cpp tests/**.cpp

fix:
    clang-tidy --fix include/**.hpp src/**.cpp tests/**.cpp

test:
    cmake -B build
    cmake --build build --target tests
    ./build/tests

run:
    cmake -B build -DCMAKE_BUILD_TYPE=Release
    cmake --build build --target raycpp
    ./build/raycpp

run_debug:
    cmake -B build -DCMAKE_BUILD_TYPE=Debug
    cmake --build build --target raycpp
    ./build/raycpp

clean:
    rm -rf build
