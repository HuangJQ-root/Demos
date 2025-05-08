# vbslite_tools代码仓库说明

## 1. 代码仓库说明

该仓库属于VBSlite项目的工具目录，主要涵盖IDL工具和XML工具，用于解析XML和IDL文件，并自动生成相应的C代码

### 1.1. XML工具

XML工具包括XML解析器和C代码生成器，基于xmltodict和jinja2库实现。其主要功能是生成应用程序配置代码，例如IP、节点和QoS等信息。这些配置信息在协议栈初始化时会被导入，用于节点的创建和初始化。有关XML配置的详细说明，[XML配置说明](https://gitee.com/haloos/vbs/blob/master/developer-guide/xml_config.md "XML配置说明")

### 1.2. IDL工具

IDL工具涵盖IDL预处理器、IDL解析器和C代码生成器，基于pcpp、antlr4和jinja2库实现。其主要功能是生成业务数据的序列化和反序列化代码，这些代码在协议栈通信时需要被调用，以实现数据的序列化和反序列化。更详细的IDL配置说明， [IDL配置说明](https://gitee.com/haloos/vbs/blob/master/developer-guide/idl_config.md "IDL配置说明")

### 1.3. 集成与平台支持

这两个工具已经通过Makefile文件集成到构建系统中，项目编译时将自动完成相应的解析和代码生成过程。此外，这些工具支持跨平台使用，可在Linux和Windows系统上运行

## 2. 代码目录

vbslite_tools源代码在haloosspace/vbs/vbslite/tools目录下，目录结构如下图所示：

```shell
tools
├── Makefile                #工具构建编译文件
├── mvbs-cfg                #XML工具目录
│   ├── example             #示例xml
│   ├── Makefile            #XML工具构建编译文件
│   ├── mvbs-config.py      #XML工具主代码
│   ├── template            #jinja2模板文件目录
│   └── utils               #XML解析器代码目录
├── mvbs-idl
│   ├── calc_topic_crc.py   #计算topic crc代码
│   ├── calc_topic_size.py  #计算topic size代码
│   ├── example             #示例idl
│   ├── Makefile            #IDL工具构建编译文件
│   ├── mvbs-idl.py         #DDS IDL工具主代码
│   ├── mvbs-rpc.py         #RPC IDL工具主代码
│   ├── parser_idl.py       #IDL解析器代码
│   ├── resources           #antlr4生成代码和jinja2模板文件目录
│   └── typeprocess         #IDL类型处理代码目录
└── README.md
```

## 3. 仓库使用入门

### 3.1. 依赖

```shell
python -m pip install xmltodict
python -m pip install jinja2
python -m pip install argparse
python -m pip install pcpp
python -m pip install antlr4-python3-runtime==4.13.0
```

### 3.2. 运行命令

#### 3.2.1. XML工具

```shell
Example: python mvbs-config.py -s ./example/dds_cfg.xml -t example/dds_cfg.c
Arguments:
	[-h] or [--help]	Show this help message and exit
	[-s] or [--source]	Source path or file of json config
	[-t] or [--targets]	Target file path or file to generated

```
#### 3.2.2. IDL工具

```shell
Example1: python mvbs-idl.py --test -i example/dds.idl -d example -t TEST
       [-h] or [--help]			Prints this message.
       [-i] or [--input_file]		input file dir.
       [-d] or [--destinate_path]	destinate file dir.
       [--test]				Generte source code with test mode

Example2: python mvbs-rpc.py -i example/rpc.idl -d example
       [-h] or [--help]			Prints this message.
       [-i] or [--input_file]		input file dir.
       [-d] or [--destinate_path]	destinate file dir.
       [--test]				Generte source code with test mode
```


