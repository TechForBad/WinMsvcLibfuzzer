## 测试用例
共包含了4个测试用例，每一个测试用例都分别提供了32位和64位的构建方式；

构建环境：cmake + "Visual Studio 16 2019"

# easy
最简单的白盒fuzz示例；

提供了3种fuzz方式：

1. 针对exe进行fuzz

2. 针对lib进行fuzz

3. 针对dll进行fuzz

# nlohmann_json
json解析库，源码地址：https://github.com/nlohmann/json

只提供了针对exe进行fuzz

# rapidxml-1.13
xml解析库，官网地址：http://rapidxml.sourceforge.net

只提供了针对exe进行fuzz

# tinyxml2
xml解析库，源码地址：https://github.com/leethomason/tinyxml2

提供了2种fuzz方式：

1. 针对exe进行fuzz

2. 针对lib进行fuzz
