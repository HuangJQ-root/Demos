# vbslite_mvbs代码仓库说明

## 1. 代码仓库简介

- MVBS，全称为 Micro Vehicle Bus Service，是VBSLite工程的核心组件之一
- 面向MCU领域设计的通信中间件，实现资源受限环境下的高效业务互联互通
- 主要采用以数据为中心的发布-订阅（DCSP, Data-Centric Publish Subscribe）通信模型
  并通过RTPS协议进行数据传输，提供低时延、高可靠的数据通信，同时支持若干必要的QoS策略
- 提供RPC（Remote Function Call）功能，支持请求-调用通信模型，构建支持多种通信模式的统一通信平台

**MVBS特性**

1. 实现RTPS标准最小子集
   - MVBS符合协议规范但仅实现RTPS标准中最小子集
   - 精简行为部分实现协议中的stateless与stateful两种参考分别可以为best-effort和reliable两种通信可靠性提供协议支持
   - 精简的实体：participant、writer、reader
   - 精简的QoS（8种规范QoS+1种自定义QoS）
2. 支持自定义子消息
   - 实现对E2E报文的支持
3. 互操作性
   - MVBS协议可以和外部RTPS Entity进行相互操作
4. 容错恢复
   - 单点故障不影响网络通信
   - 重启后可以重新加入通讯网络，继续通信
   - 支持Reliability QoS进行可靠传输
5. 较低的资源消耗
6. 支持动态和静态发现
7. 支持RPC通信模式

## 2. 代码目录

vbslite_mvbs 源代码在 haloosspace/vbs/vbslite/mvbs 目录下，目录结构如下图所示：

```shell
mvbs
├── README.md                    # 这个是MVBS仓库的readme
├── build.mk                     # 用于构建的makefile文件
├── CMakeLists.txt               # cmake编译脚本
├── posix_aux                    # 为linux和windows平台提供扩展支持库
├── include
│   ├── mcdr                     # 序列化接口
│   ├── mvbs                     # MVBS头文件集合
│   │   ├── adapter              # 适配层头文件
│   │   ├── core                 # MVBS内部核心的实体定义和操作
│   │   ├── diag                 # 诊断相关的头文件
│   │   ├── rte                  # RTE接口文件
│   │   ├── rtps                 # RTPS协议元素定义文件
│   │   ├── sections             # 用于支持内存layout
│   │   └── utils                # 常用的工具文件
│   └── rpc                      # RPC头文件
└── src
    ├── adapter                  # 适配层实现
    │   ├── auto                 # 基于VCOS 适配层的参考实现
    │   └── posix                # 基于POSIX提供的适配层实现
    ├── core
    │   ├── diag                 # 诊断工具的实现
    │   ├── discovery            # 实体发现协议的实现
    │   ├── entities             # MVBS内部实体的实现
    │   ├── include              # 提供给MVBS内部的头文件
    │   ├── messages             # 报文组装的实现
    │   ├── mvbs                 # MVBS内部接口层的实现
    │   ├── netio                # 网络接口的封装实现
    │   ├── qos                  # E2E和WLP的实现
    │   ├── storages             # CacheChange和History的实现
    │   ├── transport            # Transport的实现
    │   └── utils                # 常用工具的实现
    ├── mcdr                     # 序列化库的实现
    ├── rpc                      # RPC的实现
    └── rte                      # RTE接口的实现
```

## 3. 仓库使用入门

参考 [VBS开发者手册 —— 快速入门](https://gitee.com/haloos/vbs/blob/master/developer-guide/quick_start.md "VBS开发者手册——快速入门")
