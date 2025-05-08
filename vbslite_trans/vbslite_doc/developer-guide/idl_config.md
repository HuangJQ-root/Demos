# VBSLite IDL工具配置文档

## 概述

VBSLite IDL工具采用antir4+python+jinja2框架设计，基于Antil4对IDL源文件进行词法和语法解析，生成相应的语法树和回调函数，再由Python构造数据字典constructMapList，最后由jinja2渲染成VBSLite源代码

要声明结构化数据，必须使用IDL格式。IDL是一种规范语言，由OMG（对象管理组）制作，它以独立于语言的方式描述接口，允许不共享同一语言的软件组件之间进行通信。VBSLite IDL工具读取IDL文件并解析OMG IDL规范的子集，以生成用于数据序列化的源代码。此子集包括通过IDL定义数据类型中包含的数据类型描述。文件内容的其余部分将被忽略

VBSLite IDL工具生成的源代码使用CDR提供数据序列化和编码机制。因此，如RTPS标准中所述，当发送数据时，使用相应的公共数据表示（CDR）对数据进行序列化和编码。CDR传输语法是代理间传输的低级表示，从OMG IDL数据类型映射到字节流。VBSLite IDL工具的主要功能是在不了解序列化或反序列化机制的情况下，方便DDS应用程序的实现

## IDL定义示例

VBSLite IDL工具支持生成Topic的数据处理接口，也支持生成RPC代码接口，只需要在IDL中采用不同关键字区分即可，基础示例如下：

### DDS-IDL示例

```C
#include "HelloWorld.idl"

module LiAuto {
    const long ARR_MAX_SIZE = 10;
    const short STR_MAX_SIZE = 5;
    const short SEQ_MAX_SIZE = 3;

    struct Navigation_SigHeader {
        unsigned long long timestamp;
        unsigned long      frame_id;
        unsigned short     version;
    };

    struct bytes_10 {
        Navigation_SigHeader    header;
        char                    msg[10];
    };

    struct bytes_100 {
        Navigation_SigHeader    header;
        char                    msg[100];
    };

    struct bytes_500 {
        Navigation_SigHeader    header;
        char                    msg[500] ;
    };

    struct bytes_1000 {
        Navigation_SigHeader    header;
        char                    msg[1000];
    };

    struct bytes_1500 {
        Navigation_SigHeader    header;
        char                    msg[1500];
    };

    struct bytes_2000 {
        Navigation_SigHeader    header;
        char                    msg[2000];
    };

    struct sdatatype {
        long data1;
        long data2;
        long data3;
    };

    enum edatatype {
        ZERO_SIZE,
        ONE_SIZE,
        TWO_SIZE,
        THREE_SIZE
    };

    typedef long arrayType[0X0a];
    typedef long longarrayType[ARR_MAX_SIZE];
    typedef short shortarrayType[THREE_SIZE];


    typedef long arrayType[10];
    typedef sdatatype arrayType1[20];
    struct Mvbs_All_Type {
        Navigation_SigHeader    header;
        long                    id;
        string<64>              msg;
        char                    tag;
        octet                   u8_data;
        short                   short_data;
        unsigned short          ushort_data;
        unsigned long           ulong_data;
        long long               llong_data;
        unsigned long long      ullong_data;
        float                   float_data;
        double                  double_data;
        boolean                 bool_data;
        sdatatype               struct_data;
        edatatype               enum_data;
        arrayType               array_data;
        longarrayType           arrayType1_data;
        shortarrayType          arrayType2_data;

        sdatatype               sarraytype[5];

        long                    long_array_data[0x0a];
        octet                   octet_array_data[ARR_MAX_SIZE];
        short                   short_array_data[THREE_SIZE];

        string<0x0a>            string_16_data;
        string<STR_MAX_SIZE>    string_const_data;       string<THREE_SIZE>      string_enum_data;


    };
 };

module LiAutoTest {
    struct Test {
        Mvbs_All_Type  mvbs_all_type_data;
        sdatatype       sdatatype_data;
    };
};
```

### RPC-IDL示例

```java
module RPC{
    interface TEST {
        long add(long a, long b);
        long hello_stream(uint32 count, out string recv_string);
        long client_stream(uint32 count, uint32 add);
    };
};
```

## 命令行参数设计

工具源码在VBSLite工程中tools/mvbs-idl目录下，其中mvbs-idl.py为最终可执行文件，在此目录下执行此脚本即可生成源代码
```shell
Example1: python mvbs-idl.py --test -i example/dds.idl -d example --test
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

## 数据类型支持

### 基础数据类型

* boolean
* char
* int8
* octet
* uint8
* short（int16）
* unsigned short（uint16）
* long（int32)
* unsigned long （uint32)
* long long（int64)
* unsigned long long（uint64)
* float
* double
* long double
* string（默认长度为255）

### 扩展数据类型

#### Const

```bash
const long CONST_VALUE = 10;
```

#### Arrays

```C
const long ARR_SIZE_10 = 10;

enum edatatype {
    ZERO_SIZE,
    ONE_SIZE,
    TWO_SIZE,
    THREE_SIZE
};
struct sdatatype {
    long                long_data1;
    long                long_data2;
};

typedef long            arrayType[10];
typedef sdatatype       arrayType1[20];

struct DataType {
    short               short_data1[3];                  //支持普通数组
    sdatatype           arraysdatatype[20];              //支持结构体数组
    boolean             bool_data1[0x03];                //支持数组元素为16进制
    octet               octet_array_data[ARR_SIZE_10];   //支持数组元素为const元素
    short               short_array_data[THREE_SIZE];    //支持数组元素为枚举元素
    arrayType           structarrayarray_data;           //支持typedef 普通数组
    arrayType1          arrayType1_data;                 //支持typedef 结构体数组
};
```

#### Struct

**目前支持结构体嵌套其他扩展数据类型，跨module需要加module name**

**支持跨idl文件引用变量**

A.idl：

```Python
module MVBS1{
        struct test1 {
                long   longdata;
        };
};

module MVBS2{
        struct test2 {
                short   sdata;
        };

        struct test3 {
                MVBS1_test1    data;    //跨module
                test2          data1;   //同module
        };
};
```

B.idl

```Python
#include "A.idl"
module test1{
    struct test2 {
        MVBS1_test1   longdata;//跨文件
        }
    }
```

#### Enum

```C
enum PACKAGE_TYPE1 {
    INT32,
    UINT32,
    FLOAT
};

enum PACKAGE_TYPE2 {
    INT32 = 0,
    UINT32 = 1,
    FLOAT = 2
};

enum PACKAGE_TYPE3 {
    INT32 = 0,
    UINT32,
    FLOAT
};

enum PACKAGE_TYPE4 {
    INT32,
    UINT32 = 9,
    FLOAT
};
```

#### Union & Switch

```C
enum PACKAGE_TYPE {
    INT32,
    UINT32,
    FLOAT,
    INT16,
    UINT16,
    INT8,
    UINT8
};

union uniontype switch (PACKAGE_TYPE) {
    case INT8:
    char value_i8;
    case UINT8:
    octet value_u8;
    case INT16:
    short value_i16;
    case UINT16:
    unsigned short value_u16;
    case INT32:
    long value_i32;
    case UINT32:
    unsigned long value_u32;
    case FLOAT:
    float value_float;
};
```

#### Sequence

sequence不支持改变最大值，如果IDL中定义最大长度，则按最大长度来，如果没有定义最大长度，则默认为100个单位

用户在发送和接收sequence数据之前需要为其申请内存并绑定数据

```Python

const short SEQ_MAX_SIZE = 10;
enum edatatypeseq {
    ZERO_SIZE,
    ONE_SIZE,
    TWO_SIZE,
    THREE_SIZE
};

struct Helloworld1{
    long id;
    short ad;
};

struct Hello {
    sequence<octet, SEQ_MAX_SIZE> seq_const_data;
    sequence<unsigned long, THREE_SIZE> seq_enum_data;
    sequence<long long, 0x16> seq_16_data;
    sequence<short> short_data;//默认100
    sequence<long, 10> seq1_data;
    sequence<Helloworld1, 10> data;
};

module MVBS{
    struct Helloworld2{
        long id;
        short ad;
    };

    struct Seqtest {
        sequence<Helloworld2, 10> data;
    };

};
```

```C
--------------------PUB----------------------------
uint32_t seqsize = 2;

buffer = (int *)malloc(10 * sizeof(int));
if (buffer == NULL) {
    pr_err("long_buffer malloc error\n");
    return;
}

DDS_LongSeq_set_contiguous_buffer(&sample1->seq1_data, buffer, 10);//内存绑定数据

DDS_LongSeq_set_length(&sample1->seq1_data, seqsize);//设置数据长度
for(uint32_t i = 0; i <seqsize ; i++) {
    *DDS_LongSeq_get_reference(&sample1->seq1_data,i) = i;//赋值
}
---------------------SUB----------------------------
uint32_t max_size = DDS_LongSeq_get_maximum(&sample1.seq1_data);//获取最大长度
buffer = (int32_t *)malloc(max_size * sizeof(int32_t));
if (buffer == NULL) {
    pr_err("long_buffer malloc error\n");
    return;
}
DDS_LongSeq_set_contiguous_buffer(&sample1.seq1_data, buffer, max_size);//绑定buffer


for(uint32_t i = 0; i < DDS_LongSeq_get_length(&sample1.seq1_data); i++) {//获取实际长度
    if(*DDS_LongSeq_get_reference(&sample1.seq1_data,i) != (long)i){//读取数据
        return  MVBS_TEST_FAIL;
    }
}
```

## Annotations

### @compatible

@compatible关键字用于版本的前向兼容，当idl版本需要前后兼容时，需要在struct前增加该注释

目前对于@compatible的处理是:

1. 若配置了@compatible，如果该node下的某个数据反序列化失败，则会给其赋默认值0，并且返回true（即反序列化成功）
2. 若没有配置@compatible，如果该node下的某个数据反序列化失败，则会直接返回false（即反序列化失败）

需要注意的是，@compatible的使用具有一定的约束，其约束如下：

* **新版本只能在原始版本的基础上在topic的末尾只增加或只删除，不允许在开头或者中间增删，也不允许在末尾基增加也删除（修改）**
* **新版本不能改变topic数据类型的顺序，即无法乱序**

```Python
V1：
@compatible struct MVBS1 {
    long                 id;
    char                 tag;
};

V2：
@compatible struct MVBS1 {
    long                 id;
    char                 tag;
    short                short_data;
};
V3：
@compatible struct MVBS1 {
    long                  id;
};
```

### @default

IDL支持@default来为基础数据类型赋默认值，生成代码会生成xxx_init函数，在函数中为数据赋初始值，如果加了@default,则采用括号中的值，否则初始值为0，示例如下：

```C
struct HelloWorld
    {
        @default(1) unsigned long index;
        long index1;
        string message;
    };

//生成代码
void HelloWorld_init(HelloWorld *sample)
{
    if (sample != NULL) {
        sample->index = 1;
        sample->index1 = 0;
        os_memzero(sample->message, 255 + 1);
    }
}
```

**注：目前仅支持基础数据类型，不支持为复杂数据类型赋默认值，如：**

```Python
struct test{
    long a;
    long b;
    long c;
    };
type long array_type[4];
@compatible struct AR_MCU_IDL_11_A {
    long                  id;
    char                 tag;
    short                short_data;
    @default(2,2,2)test                  data;不支持
    @default(1,1,1,1)array_type           array;不支持
}
```

## comments

字符 /* 开始注释，以字符 */ 结束。 这些评论不嵌套

字符 // 开始注释，注释在它们出现的行的末尾终止

注释字符 // 、 /* 和 / 在 // 注释中没有特殊含义，并且与其他字符一样处理。 同样，注释字符 // 和 / 在 /* 注释中没有特殊含义

注释可能包含字母、数字、图形、空格、水平制表符、垂直制表符、换页符和换行符

```C
#ifndef _ACCURATEMILEAGESERVICENORMAL_IDL
#define _ACCURATEMILEAGESERVICENORMAL_IDL
struct MyStruc
{
    string mymessage;   // mymessage data member.
};
#endif
```

## 预处理

```c++
#ifndef RUNTIME_UPLOADING_IDL
#define RUNTIME_UPLOADING_IDL

//#define WORD_LENGH_64
#define WORD_LENGH_32
#define FIXED_LENGTH

#ifdef WORD_LENGH_64
  #define WORD_LENGH_32
#endif

#ifdef FIXED_LENGTH
  #define LENGH_LIMIT (1024 - 128)
  #ifdef WORD_LENGH_64
    #define CELL_COUNT (LENGH_LIMIT/12)
  #else
    #define CELL_COUNT (LENGH_LIMIT/8)
  #endif
#endif
#define CELL_COUNT 48

module mvbs_idls {
  module idls {
    module transfer_layer {
      const unsigned short cell_count = CELL_COUNT;
      enum PACKAGE_TYPE {
#ifdef WORD_LENGH_64
        INT64,
        UINT64,
        DOUBLE,
#endif
#ifdef WORD_LENGH_32
        INT32,
        UINT32,
        FLOAT,
#endif
        INT16,
        UINT16,
        INT8,
        UINT8
      };

      union VALUE switch (PACKAGE_TYPE) {
      case INT8:
        char value_i8;
      case UINT8:
        octet value_u8;
      case INT16:
        short value_i16;
      case UINT16:
        unsigned short value_u16;
#ifdef WORD_LENGH_32
      case INT32:
        long value_i32;
      case UINT32:
        unsigned long value_u32;
      case FLOAT:
        float value_float;
#endif
#ifdef WORD_LENGH_64
      case INT64:
        long long value_i64;
      case UINT64:
        unsigned long long value_u64;
      case DOUBLE:
        double value_double;
#endif
      };

      struct PACKAGE {
        unsigned short key;
        VALUE value;
      };
    };
  };
};

#endif
```
