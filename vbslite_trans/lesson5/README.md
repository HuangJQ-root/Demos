# vbslite移植适配posix的测试

## 官方用例
rte_interface_test

## 移植内容
rte_interface_test
测试源码、通信库mvbs、生成工具库tools、python依赖的虚拟环境

## 操作步骤
### 3. 构建与编译
#### 3.1 构建rte_interface_test的CMakeLists.txt文件
为rte_interface_test构建`CMakeLists.txt`。具体的构建逻辑和细节需根据项目实际需求进行编写，以确保rte_interface_test能够正确编译。

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
source ../envsetup.sh
lunch linux
./sub_test
./pub_test
```

### 5.验证环境变量设置
```bash
echo $TARGET_PRODUCT_LINUX
```
