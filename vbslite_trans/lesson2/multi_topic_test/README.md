# 描述

- 本示例演示了10个topic的通信配置和使用
- app1从app2接收5个topic的数据，并向app2发送5个topic的数据
- app2从app1接收5个topic的数据，并向app1发送5个topic的数据

# 注意

有两种方法可以修改IP地址：

1. 在XML文件中修改IP地址

   例如：`<address>`172.31.3.71 `</address>`

2. 在终端中修改IP地址

   例如：export MVBS_LOCATOR_INFO=172.31.3.71/24

# 编译

## app1

```
$ source build/envsetup.sh
$ lunch linux				# 选择Linux平台
$ make multi_topic_test_app1
```

## app2

```
$ source build/envsetup.sh
$ lunch linux				# 选择Linux平台
$ make multi_topic_test_app2
```

# 运行

## app1

```
$ ./multi_topic_test_app1
```

## app2

```
$ ./multi_topic_test_app2
```

成功运行的标志：打印出“Run successfully”日志

# 终止

按 ctrl+c 终止程序
