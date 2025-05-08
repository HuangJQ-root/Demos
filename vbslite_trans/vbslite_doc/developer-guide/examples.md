# VBSLite示例教程

## 1. 示例介绍

在examples仓库下，本项目介绍6种场景的使用示例，涵盖了本地通信、UDP通信、RPC 通信、多topic通信等场景

* local_test: 本地通信示例，展示域内通信配置和使用方法
* udp_test: UDP通信示例，展示UDP（1V1）通信配置和使用方法
* multi_topic_test:多topic通信示例，展示10个topic通信配置和使用方法
* rte_interface_test: 接口使用示例，展示主要的RTE层接口的使用方法
* rpc_test: RPC 通信示例，底层基于TCP通信，展示RPC配置和使用方法
* vbslite_perf_demo: 性能测试示例，展示300个topic下的内存、时延和丢包率结果

## 2. 示例运行

以udp_test举例，在linux和windows平台其编译和运行方式分别如下

* linux平台编译

  * pub端

  ```Bash
  $ source build/envsetup.sh
  $ lunch linux
  $ make udp_test_pub
  ```
  * sub端

  ```Bash
  $ source build/envsetup.sh
  $ lunch linux
  $ make udp_test_sub
  ```
* windows平台编译

  * pub端

  ```Bash
  $ source build/envsetup.sh
  $ lunch MINGW
  $ make udp_test_pub
  ```
  * sub端

  ```Bash
  $ source build/envsetup.sh
  $ lunch MINGW
  $ make udp_test_sub
  ```
* 运行

  * pub端

  ```Bash
  $ ./udp_test_pub
  ```
  * sub端

  ```Bash
  $ ./udp_test_sub
  ```
