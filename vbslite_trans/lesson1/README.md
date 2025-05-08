# vbslite移植适配posix的测试

## 官方用例
local_test

## 移植内容
local_test测试源码、通信库mvbs、生成工具库tools、python依赖的虚拟环境

## 操作步骤
### 3. 构建与编译
#### 3.1 构建local_test的CMakeLists.txt文件
为local_test构建`CMakeLists.txt`。具体的构建逻辑和细节需根据项目实际需求进行编写，以确保local_test能够正确编译。

#### 3.2 修改mvbs库的CMakeLists.txt文件
修改mvbs库的`CMakeLists.txt`，将其依赖修改为posix而不是autosar。这一步需要仔细检查和调整相关的源文件引用、头文件路径以及编译选项等，以适应新的依赖环境。

#### 3.3 执行编译操作
确保在env环境下，在lesson目录下执行以下命令：
```bash
mkdir build && cd build
cmake ..
make 
```
在执行上述命令时，`mkdir build`用于创建名为`build`的目录，`cd build`进入该目录，`cmake ..`用于根据上一级目录的`CMakeLists.txt`文件生成编译配置，`make`则根据生成的配置进行实际的编译操作。

### 4. 运行
在build目录下，执行以下命令来运行程序：
```bash
./local_test_app
```

## 警告
官方解析xml和idl脚本命令有误。

### XML工具
```bash
Example: python mvbs-config.py -s ./example/dds_cfg.xml -t example/dds_cfg.c
Arguments:
    [-h] or [--help]        Show this help message and exit
    [-s] or [--source]      Source path or file of json config
    [-t] or [--targets]     Target file path or file to generated
    [--test]                Generate source code with test mode
```

### IDL工具
```bash
Example1: python mvbs-idl.py -i example/dds.idl -d example -t TEST
       [-h] or [--help]         Prints this message.
       [-i] or [--input_file]   input file dir.
       [-d] or [--destinate_path] destinate file dir.
       [--test]                 Generate source code with test mode 
```



### 正确做法：
- `XML工具`：取消 `--test` 选项，生成的文件才能正常运行。
- `IDL工具`：保留 `--test` 选项，生成的文件才能正常运行。（有无 `test` 生成文件内容不一致） 

