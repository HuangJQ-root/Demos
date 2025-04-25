
以下是将您提供的 Doxygen 测试步骤转换为 **Markdown 格式** 的内容，便于阅读和分享：


# Doxygen 测试指南  
**目的**：学习如何使用 Doxygen 为项目生成基础文档  


## 一、安装 Doxygen  
### Ubuntu/Debian  
```bash  
sudo apt-get install doxygen graphviz  
```  

## 二、创建 Doxyfile 配置文件  
### 方法 1：命令行生成默认配置  
在项目根目录执行：  
```bash  
doxygen -g Doxyfile  # 生成默认配置文件  
```  

## 三、配置 Doxyfile  
打开 `Doxyfile`，修改以下关键参数（根据项目需求调整）：  

### 1. 基本信息配置  
```makefile  
PROJECT_NAME         = "My Project"       # 项目名称  
PROJECT_NUMBER       = "1.0"              # 版本号  
OUTPUT_DIRECTORY     = doc                # 输出目录（自动创建）  
INPUT                = src include        # 需要扫描的源码目录（空格分隔）  
FILE_PATTERNS        = *.h *.cpp *.cc     # 匹配的文件类型  
```  

### 2. 文档生成选项  
```makefile  
GENERATE_LATEX       = NO                 # 生成 LaTeX 文档（默认 NO）  
GENERATE_HTML        = YES                # 生成 HTML 文档（默认 YES）  
GENERATE_XML         = NO                 # 生成 XML 文档（用于其他工具，如 Eclipse）  
```  

### 3. 代码扫描范围  
```makefile  
EXTRACT_ALL          = YES                # 提取所有类/函数（包括静态和私有成员）  
EXTRACT_STATIC       = YES                # 提取静态成员  
EXTRACT_PRIVATE      = YES                # 提取私有成员（谨慎使用）  
```  

### 4. 图形生成（需安装 Graphviz）  
```makefile  
HAVE_DOT             = YES                # 启用 Graphviz  
CALL_GRAPH           = YES                # 生成函数调用图  
CLASS_DIAGRAMS       = YES                # 生成类继承图  
```  

### 5. 其他常用配置 (我没试过)
```makefile  
QUIET                = YES                # 静默模式（不输出冗余信息）  
JAVADOC_AUTOBRIEF    = YES                # 自动提取注释第一行作为简要说明  
```  


## 四、生成文档  
### 1. 简单模式（使用默认配置）  
```bash  
doxygen Doxyfile  # 执行后在 OUTPUT_DIRECTORY 生成文档  
```  

### 2. 分步模式（用于调试配置）  
```bash  
doxygen -s Doxyfile  # 仅扫描代码，生成配置摘要（检查 INPUT 是否正确）  
doxygen -g Doxyfile  # 重新生成配置文件（覆盖现有）  
doxygen             # 直接使用当前目录的 Doxyfile 生成文档  
```  


## 五、查看生成的文档  
生成的 HTML 文档位于 `OUTPUT_DIRECTORY/html` 目录下，打开 `index.html` 即可浏览：  

- **Linux**：  
  ```bash  
  xdg-open doc/html/index.html  
  ```  

## 六、示例目录结构  
```plaintext  
project/  
├─ src/               # 源码目录  
│  ├─ main.cpp  
│  └─ module.h  
├─ include/           # 头文件目录  
├─ Doxyfile           # 配置文件  
└─ doc/               # 生成的文档目录（自动创建）  
   └─ html/  
      ├─ index.html   # 主页  
      └─ classes/     # 类文档  
```  


## 七、注意事项  
- **中文支持**：若文档出现乱码，需在 `Doxyfile` 中设置 `INPUT_ENCODING = UTF-8`，并确保代码文件以 UTF-8 编码保存。  
- **图形依赖**：生成函数调用图或类图前，需确保 Graphviz 已正确安装且 `dot` 命令可在终端调用。  
- **注释规范**：代码中需使用 Doxygen 风格注释（如 `@brief`、`@param`、`@return`），否则可能无法提取有效文档信息。  
- **特别注意**：Doxyfile  文件的位置需要在include 和 src 同级。
  
通过以上步骤，即可快速上手使用 Doxygen 为项目生成结构化文档。