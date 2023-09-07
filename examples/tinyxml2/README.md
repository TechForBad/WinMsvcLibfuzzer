* compile and run x64
```
mkdir build_x64
cd build_x64
cmake .. -A x64 -G "Visual Studio 16 2019"
cmake --build . --config RelWithDebInfo
cd RelWithDebInfo
./fuzz_exe.exe
./fuzz_lib.exe
```

* compile and run x86
```
mkdir build_x86
cd build_x86
cmake .. -A x86 -G "Visual Studio 16 2019"
cmake --build . --config RelWithDebInfo
cd RelWithDebInfo
./fuzz_exe.exe
./fuzz_lib.exe
```
