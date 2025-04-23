# Google Test 测试项目

## 目的
学习如何将 Google Test（gtest）引入项目工程，以对开发的功能函数进行单元测试。

## 步骤

### 1. 安装 Google Test
可以通过以下命令从 GitHub 克隆 Google Test 的指定版本并进行编译安装：
```bash
git clone -b release-1.11.0 https://github.com/google/googletest.git 
cd googletest && mkdir build && cd build
cmake .. && make && sudo make install
```

### 2. 创建简易项目工程 Gtest_Demo
本项目使用 C 语言编写，其目录结构如下：
```plaintext
- Gtest_Demo
  - CMakeLists.txt
  - include/  # 项目头文件目录
  - src/      # 项目源文件目录
  - tests/    # 项目测试文件目录
  - build/    # 项目编译文件目录
  - .vscode/
```

### 3. 注意事项
`test.cc` 是 C++ 文件，而 `example.c` 是 C 文件。为了确保在 C++ 代码里调用 C 函数时，链接时函数名不会被 C++ 的名称修饰机制改变，需要在头文件 `example.h` 中添加 `extern "C"`。示例如下：
```cpp
// 在 include/example.h 头文件中
#ifdef __cplusplus
extern "C" {
#endif

// 这里放置函数声明等内容
int example_function(int param);

#ifdef __cplusplus
}
#endif
```
上述代码借助 `#ifdef __cplusplus` 预处理器指令，确保 `extern "C"` 仅在 C++ 编译器中生效。这样一来，无论是 C 代码还是 C++ 代码都能包含该头文件，并且能正确处理其中声明的函数。

### 4. CMakeLists 编写

#### 4.1 `Gtest_Demo/CMakeLists.txt` 解释
```cmake
cmake_minimum_required(VERSION 3.12)

set(Project_Name Gtest_Demo)

project(${Project_Name})

enable_language(C)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

enable_testing()

set(Headers
    include/example.h
)

set(Sources
    src/example.c
)

add_library(${Project_Name} STATIC ${Sources} ${Headers})

# 设置头文件搜索路径
target_include_directories(${Project_Name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(tests)
```

| 代码行 | 解释 |
| --- | --- |
| `cmake_minimum_required(VERSION 3.12)` | 指定运行此 `CMakeLists.txt` 文件所需的最小 CMake 版本为 3.12，确保使用的 CMake 版本能正确解析和执行该文件。 |
| `project(${Project_Name})` | 定义项目名称为 `Gtest_Demo`，后续生成的构建文件可能会使用该名称标识项目。 |
| `enable_language(C)` | 启用 C 语言支持，让 CMake 能正确配置编译器和构建环境。 |
| `set(CMAKE_C_STANDARD 99)` | 设置 C 语言标准为 C99，编译器编译 C 代码时会遵循此标准。 |
| `set(CMAKE_CXX_STANDARD 17)` | 设置 C++ 语言标准为 C++17，编译器编译 C++ 代码时会遵循此标准。 |
| `set(CMAKE_EXPORT_COMPILE_COMMANDS ON)` | 启用编译命令的导出功能，CMake 会在构建目录下生成 `compile_commands.json` 文件，供开发工具了解项目编译配置。 |
| `enable_testing()` | 启用 CMake 的测试功能，后续可使用 `add_test` 命令定义和管理测试用例。 |
| `set(Headers include/example.h)` | 定义名为 `Headers` 的 CMake 变量，将 `include/example.h` 文件添加到该变量中，方便管理和引用文件。 |
| `set(Sources src/example.c)` | 定义名为 `Sources` 的 CMake 变量，将 `src/example.c` 文件添加到该变量中，方便管理和引用源文件。 |
| `add_library(${Project_Name} STATIC ${Sources} ${Headers})` | 创建一个名为 `Gtest_Demo` 的静态库，使用之前定义的 `Sources` 和 `Headers` 变量指定库的源文件和头文件。 |
| `target_include_directories(${Project_Name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)` | 设置 `Gtest_Demo` 库的头文件搜索路径，`PUBLIC` 表示这些目录在编译库和链接使用该库的其他目标时都会被使用。 |
| `add_subdirectory(tests)` | 告诉 CMake 处理 `tests` 子目录下的 `CMakeLists.txt` 文件，将子目录的构建规则集成到整个项目中。 |

#### 4.2 `Gtest_Demo/tests/CMakeLists.txt` 解释
```cmake
cmake_minimum_required(VERSION 3.12)

set(Project_Name Gtest_Demo)
set(Test_Name Exampletest)

set(Sources
    test.cc
)

add_executable(${Test_Name} ${Sources})

target_link_libraries(${Test_Name} PRIVATE
    gtest
    gtest_main
    ${Project_Name}
)

add_test(
    NAME ${Test_Name}
    COMMAND ${Test_Name}
)
```

| 代码行 | 解释 |
| --- | --- |
| `cmake_minimum_required(VERSION 3.12)` | 指定运行此 `CMakeLists.txt` 文件所需的最小 CMake 版本为 3.12，确保使用的 CMake 版本能正确解析和执行该文件。 |
| `set(Test_Name Exampletest)` | 定义名为 `Test_Name` 的 CMake 变量，值为 `Exampletest`，方便后续引用该名称。 |
| `set(Sources test.cc)` | 定义名为 `Sources` 的 CMake 变量，将 `test.cc` 文件添加到该变量中，方便管理和引用源文件。 |
| `add_executable(${Test_Name} ${Sources})` | 使用 `add_executable` 命令创建名为 `Exampletest` 的可执行文件，源文件为 `test.cc`。 |
| `target_link_libraries(${Test_Name} PRIVATE gtest gtest_main ${Project_Name})` | 使用 `target_link_libraries` 命令将 `gtest`、`gtest_main` 和 `Gtest_Demo` 库链接到 `Exampletest` 可执行文件上，`PRIVATE` 表示这些库仅在编译和链接 `Exampletest` 时使用。 |
| `add_test(NAME ${Test_Name} COMMAND ${Test_Name})` | 使用 `add_test` 命令将 `Exampletest` 可执行文件注册为一个测试用例，运行 `ctest` 命令时，CMake 会自动执行该测试用例。 |

### 5. 使用 ctest 执行测试
完成项目构建后，可在 `build` 目录中使用 `ctest` 执行测试。常见的操作如下：
1. **执行所有测试用例**：在项目 `build` 目录下，直接运行 `ctest` 命令，即可执行所有注册的测试用例。
```bash
cd Gtest_Demo/build
ctest
```
2. **详细模式执行**：添加 `-V` 参数，以详细模式运行测试，输出每个测试用例的详细执行信息，便于排查问题。
```bash
ctest -V
```
3. **运行指定测试用例**：通过 `-R` 参数并结合正则表达式，可运行名称匹配的测试用例。例如，运行名称为 `Exampletest` 的测试用例：
```bash
ctest -R Exampletest
```
4. **通过编号运行**：`ctest` 输出中每个测试用例都有编号，使用 `-I` 参数可指定运行的测试用例编号范围。如运行编号为 1 的测试用例：
```bash
ctest -I 1,1
```

综上所述，`Gtest_Demo/CMakeLists.txt` 主要用于定义 `Gtest_Demo` 静态库项目，设置编译标准和头文件搜索路径，启用测试功能并纳入 `tests` 子目录的构建规则；`Gtest_Demo/tests/CMakeLists.txt` 用于创建 `Exampletest` 可执行文件，链接 Google Test 框架和 `Gtest_Demo` 静态库，并将其注册为测试用例 。借助 `ctest`，开发者能灵活管理和执行测试用例，保障项目质量。 