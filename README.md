# WinMsvcLibfuzzer
对于llvm编译的程序可以很方便地使用libfuzzer进行白盒fuzz，然而对于msvc编译的程序，很多人选择改用llvm重新编译一遍项目再进行fuzz，  
但这有很多坏处，比如说有些项目中使用的宏只有msvc编译器可以识别出来，而且换了编译器后你无法确保程序的执行路径还和原来一致，甚至部分系统api也无法保证运行结果一致，  
  
***这里就是介绍如何在windows使用libfuzzer对msvc编译的程序进行白盒fuzz。***

# 目录
* examples  
包含若干测试示例，构建环境：cmake + "Visual Studio 16 2019"
* fuzzer_lib  
包含在白盒fuzz环境搭建过程中需要的所有静态库；  
其中包含了若干从"C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Tools\MSVC\14.29.30133\lib"目录下拷贝得到的lib库；  
也包含了对libfuzzer源码进行一些修改后的lib库fuzzer_x64.lib和fuzzer_x86.lib；
* src  
包含文件夹fuzzer_lib中静态库fuzzer_x64.lib和fuzzer_x86.lib的源码，按照src/README.md编译

# 注意
我试了下"Visual Studio 17 2022"，发现是不行的，只能是"Visual Studio 16 2019"，希望有人能帮忙找到原因
