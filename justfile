build:
    cmake -B build
    cp ./build/compile_commands.json .
    cmake --build build

format:
    clang-format -i include/**.h src/**.cpp

check:
    clang-tidy include/**.h src/**.cpp

fix:
    clang-tidy --fix include/**.h src/**.cpp

run:
    cmake -B build -DCMAKE_BUILD_TYPE=Release
    cmake --build build
    ./build/raycpp

run_debug:
    cmake -B build -DCMAKE_BUILD_TYPE=Debug
    cmake --build build
    ./build/raycpp

clean:
    rm -rf build
