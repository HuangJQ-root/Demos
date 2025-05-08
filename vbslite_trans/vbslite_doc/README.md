# VBSLite文档仓库说明

## 1. 文档仓库简介

本仓库是VBSLite的综合文档中心，专为开发者、集成商及用户提供一站式技术支持。文档内容涵盖API参考、快速入门、示例教程和开发者手册，旨在帮助用户高效入门并深入理解通信总线

| **文档类型** | **内容简介**                                           | **快速跳转链接**                           |
| :----------------- | ------------------------------------------------------------ | ------------------------------------------------ |
| VBSLite概览        | 概览VBSLite的核心特性与功能                                  | [OVERVIEW](./OVERVIEW.md)                           |
| 开发者手册         | 提供VBSLite的详尽功能说明，帮助用户深入理解功能定义          | [开发者手册](./developer-guide/user_manual.md)      |
| 快速开始           | 提供VBSLite代码获取方式、环境配置流程以及开发示例            | [快速开始](./developer-guide/quick_start.md)        |
| 示例教程           | 提供VBSLite在不同场景下的使用示例和教程                      | [示例教程](./developer-guide/examples.md)           |
| 轻量化实践         | 展示VBSLite轻量化方面（包含低开销、低时延、搞可靠）的创新实践 | [轻量化实践](./developer-guide/vbslite_practice.md) |
| XML工具            | 提供VBSLite XML配置参数说明，便于用户根据需求定义不同的Qos   | [XML工具](./developer-guide/xml_config.md)          |
| IDL工具            | 提供VBSLite IDL关键字的详细说明，便于用户自定义IDL配置文件   | [IDL工具](./developer-guide/idl_config.md)          |
| API接口            | 提供VBSLite API详细的说明和使用示例，方便用户快速使用        | [API接口](./developer-guide/vbslite_api.md)         |

## 2. 文档目录

VBSLite文档在haloosspace/vbs/docs目录下，目录结构如下图所示：

```shell
docs
├── OVERVIEW.md                 # VBSLite概览
├── README.md                   # docs目录描述文档
├── developer-guide             # VBSLite 开发者文档目录
│   ├── examples.md             # VBSLite 示例教程
│   ├── idl_config.md           # VBSLite IDL配置工具文档
│   ├── quick_start.md          # VBSLite 快速开始
│   ├── user_manual.md          # VBSLite 开发者手册
│   ├── vbslite_api.md          # VBSLite 接口文档
│   ├── vbslite_practice.md     # VBSLite 轻量化实践展示
│   └── xml_config.md           # VBSLite XML配置工具文档
└── _static/image               # 文档所使用的所有图片
```
