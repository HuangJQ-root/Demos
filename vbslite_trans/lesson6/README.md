# vbslite移植适配posix的测试

## 官方用例
vbslite_perf

## 移植内容
vbslite_perf测试源码、通信库mvbs、生成工具库tools、python依赖的虚拟环境

## 操作步骤
### 3. 构建与编译
#### 3.1 构建vbslite_perf的CMakeLists.txt文件
为vbslite_perf构建`CMakeLists.txt`。具体的构建逻辑和细节需根据项目实际需求进行编写，以确保vbslite_perf能够正确编译。

#### 3.2 修改mvbs库的CMakeLists.txt文件
修改mvbs库的`CMakeLists.txt`，将其依赖修改为posix而不是autosar。这一步需要仔细检查和调整相关的源文件引用、头文件路径以及编译选项等，以适应新的依赖环境。

#### 3.3 修改xml配置文件
需要修改的xml文件为Node1_Config.xml 和 Node2_config.xml，主要修改其中的`<address>`标签。

**当前`ip addr show`查询结果**：
```
2: ens33: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc fq_codel state UP group default qlen 1000
    link/ether 00:0c:29:59:18:3c brd ff:ff:ff:ff:ff:ff
    altname enp2s1
    inet 192.168.186.136/24 brd 192.168.186.255 scope global dynamic noprefixroute ens33
       valid_lft 1679sec preferred_lft 1679sec
    inet6 fe80::9329:6582:f016:ce9f/64 scope link noprefixroute 
       valid_lft forever preferred_lft forever
```
根据上述结果，Node1_Config.xml的`<address>`标签应设置为`<address>192.168.186.136</address>`。

接着，输入命令添加一个同网段ip：
```
sudo ip addr add 192.168.186.137/24 dev ens33 label ens33:1
```

添加新ip后再次`ip addr show`的结果：
```
2: ens33: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc fq_codel state UP group default qlen 1000
    link/ether 00:0c:29:59:18:3c brd ff:ff:ff:ff:ff:ff
    altname enp2s1
    inet 192.168.186.136/24 brd 192.168.186.255 scope global dynamic noprefixroute ens33
       valid_lft 1539sec preferred_lft 1539sec
    inet 192.168.186.137/24 scope global secondary ens33:1
       valid_lft forever preferred_lft forever
    inet6 fe80::9329:6582:f016:ce9f/64 scope link noprefixroute 
       valid_lft forever preferred_lft forever
```
此时，Node2_Config.xml的`<address>`标签应设置为`<address>192.168.186.137</address>`。

注意：通过上述命令添加的ip是临时方法，重启后失效。

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
source linux
./app1
./app2
```

### 5.验证环境变量设置
```bash
echo $TARGET_PRODUCT_LINUX
```

### 6.一些tips
vbslite_perf.idl文件生成 vbslite_perfPlugin.c 和 vbslite_perfPlugin.h
在源文件如app.c 引用 #include "vbslite_perfPlugin.h"

## 警告
官方解析xml和idl脚本命令有误。

### XML工具
```shell
Example: python -B mvbs-config.py -s ./example/dds_cfg.xml -t example/dds_cfg.c
Arguments:
	[-h] or [--help]	Show this help message and exit
	[-s] or [--source]	Source path or file of json config
	[-t] or [--targets]	Target file path or file to generated
       [-B]                 prevent the generation of .pyc files.
```

### IDL工具
```shell
Example1: python -B mvbs-idl.py -i example/dds.idl -d example/Libdds -t TEST
       [-h] or [--help]			Prints this message.
       [-i] or [--input_file]		input file dir.
       [-d] or [--destinate_path]	destinate file dir.
       [-t]				Generte source code with test mode(required)
       [-B]                        prevent the generation of .pyc files.

Example2: python -B mvbs-rpc.py -i example/rpc.idl -d example/Librpc
       [-h] or [--help]			Prints this message.
       [-i] or [--input_file]		input file dir.
       [-d] or [--destinate_path]	destinate file dir.
       [-B]                        prevent the generation of .pyc files.
``` 