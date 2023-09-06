# compile and run x64
mkdir build_x64

cd build_x64

cmake .. -A x64 -G "Visual Studio 16 2019"

cmake --build . --config RelWithDebInfo

cd RelWithDebInfo

./fuzz_json.exe

# compile and run x86
mkdir build_x86

cd build_x86

cmake .. -A Win32 -G "Visual Studio 16 2019"

cmake --build . --config RelWithDebInfo

cd RelWithDebInfo

./fuzz_json.exe
