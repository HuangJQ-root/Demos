# vbslite 移植适配 posix 的测试环境搭建

## 一、Linux 平台编译工具安装
根据你的 Linux 发行版本，安装 `make`、`gcc`、`python`、`pip` 等工具。以 Debian 或 Ubuntu 系统为例，在终端中使用管理员权限（`sudo`）运行以下命令：
```bash
$ sudo apt install make
$ sudo apt install gcc
$ sudo apt install python3
$ sudo apt install python3-pip
```
安装完成后，可通过以下命令查询是否安装成功：
```bash
$ make --version
$ gcc --version
$ python3 --version
$ pip3 --version
```

## 二、编译依赖库安装
本项目依赖一些关键的 Python 库和工具，请确保在开始编译之前安装以下依赖库：
```
crcmod==1.7
pcpp==1.30
Jinja2==3.1.2
antlr4-python3-runtime==4.13.0
xmltodict==0.13.0
ply==3.11
```

### （一）安装 python3-venv 包
打开终端，使用管理员权限（`sudo`）运行以下命令安装 `python3.10-venv` 包（如果你的 Python 版本是 3.10，若为其他版本，需将 3.10 替换为实际版本号）：
```bash
$ sudo apt install python3.10-venv
运行命令后，系统会提示你确认安装，输入 y 并回车，等待安装完成。
```

### （二）重新创建虚拟环境
安装完成后，重新执行创建虚拟环境的命令。在 `/home/cheeco/Demos/vbslite_trans/` 目录下创建名为 `vbslitetransenv` 的虚拟环境，命令如下：
```bash
$ python3 -m venv /home/cheeco/Demos/vbslite_trans/vbslitetransenv/bin/activate
```

### （三）激活虚拟环境（可选）
如果创建成功，可以激活虚拟环境来使用它。在 Debian 或 Ubuntu 系统中，使用以下命令激活：
```bash
$ source /home/cheeco/Demos/vbslite_trans/vbslitetransenv/bin/activate
```
使用以下命令退出虚拟环境：
```bash
$ deactivate
```

### （四）在虚拟环境下一次性安装所有依赖库
在激活虚拟环境后，运行以下命令一次性安装所有依赖库：
```bash
$ pip3 install crcmod==1.7 pcpp==1.30 Jinja2==3.1.2 antlr4-python3-runtime==4.13.0 xmltodict==0.13.0 ply==3.11
```

### （五）安装 requirements.txt 中的依赖
进入 `vbslitetransenv` 目录，在根目录中有 `requirements.txt` 文件，请使用以下命令安装其中的依赖：
```bash
$ pip install -r requirements.txt
```

至此，vbslite 移植适配 posix 的测试环境搭建完成，可进行后续的测试相关操作。 后续测试用例都移植 idl mvbs tools envsetup.sh 4个文件（夹） 