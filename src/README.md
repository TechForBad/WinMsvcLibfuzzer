## 编译目标
fuzzer_x64.lib

fuzzer_x86.lib

## 编译环境
cmake + "Visual Studio 16 2019"

## 编译过程

# 编译fuzzer_x64.lib
mkdir build_x64

cd build_x64

cmake .. -A x64 -G "Visual Studio 16 2019"

cmake --build . --config RelWithDebInfo

# 编译fuzzer_x86.lib
mkdir build_x86

cd build_x86

cmake .. -A Win32 -G "Visual Studio 16 2019"

cmake --build . --config RelWithDebInfo

## 如何使用
将"src\build_x64\RelWithDebInfo\fuzzer_x64.lib"拷贝到"fuzzer_lib\x64"

将"src\build_x86\RelWithDebInfo\fuzzer_x86.lib"拷贝到"fuzzer_lib\win32"
