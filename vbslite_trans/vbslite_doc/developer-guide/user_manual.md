# VBSLite开发者手册

## 1. 简介

随着汽车产业向电动化、智能化、网联化加速转型，车载电子电气架构正经历革命性重构。传统分布式ECU架构已无法满足高速数据传输、跨域协同和软件定义汽车（SDV）的需求，而车载通信总线作为连接整车传感器与控制器的“中枢神经”，其性能与自主可控性直接决定了车企的核心竞争力

星环OS通信总线（VBS，Vehicle Bus System）是理想汽车面向智能汽车领域开发的高效数据交互通信平台。它通过一套标准化的通信协议、模块化架构和实时数据传输能力，为整车电子电气系统提供实时、可靠的信息通道，实现辅助驾驶、动力控制、信息娱乐、主动安全等服务间的无缝协同

VBSLite，也称为MVBS（Micro Vehicle Bus System），是星环OS通信总线的精简版本。它引入了简化的QoS策略，支持自定义子消息，并具备强大的互操作性、容错恢复能力和低资源消耗等特点。VBSLite 可以部署在资源有限的MCU上，为资源受限设备的DDS实现提供了高效的解决方案和最佳实践

## 2. 代码目录介绍

* [mvbs目录](https://gitee.com/haloos/vbslite_mvbs/blob/master/README.md)
* [example目录](https://gitee.com/haloos/vbslite_examples/blob/master/README.md)
* [build目录](https://gitee.com/haloos/vbslite_build/blob/master/README.md)
* [tools目录](https://gitee.com/haloos/vbslite_tools/blob/master/README.md)

## 3. 功能介绍

VBSLite针对车控MCU资源受限场景下，突破传统DDS实现范式，通过三大创新性技术路径实现低开销、低时延、高可靠的通信性能

1. RAM消耗低

   - XML 驱动开发

     用户采用XML定义通信矩阵以及资源规格，通过代码生成器生成协议栈所需要数据, 规避了运行时动态资源分配开销, 以及内存碎片引发的不确定性

   - 资源预分配策略

     仅仅将运行时需要动态修改的数据部署到RAM，其他数据部署到ROM中，使得RAM内存占用显著降低

   - 协议实现突破固有的范式

     VBSLite 不再存储很多传统DDS内置节点大量的缓冲数据, 在需要这些数据时, 创新性通过数据模板产生这些必要的数据, 既节省了内存, 也没有导致CPU使用率激增

2. 微秒级实时传输引擎

   - 零拷贝传输机制

     在 UDP 收包中断处理流程中，采用直接解析 DDS 数据包的策略，省去将数据包拷贝至用户任务的中间环节，从而将通信时延精准控制在 100 微秒以内，显著提升数据传输效率

   - 裸数据处理范式

     针对车控领域常见的定长数据,  摒弃了传统序列化/反序列化流程，采用了数据直接拷贝方式，使得端到端时延得到大幅降低

3. 车规级可靠性增强

   - 轻量化可靠传输协议

     保留DDS核心ACK/NACK机制

   - 系统级别鲁棒性设计

     基于确定性设计理念，着重保障内存资源使用的可预测性，并在系统内部全面采用 O (1) 常数级查找算法，有效增强系统运行的稳定性与抗干扰能力，切实提升整体鲁棒性

## 4. 配置流程

* [VBSLite 快速开始](./quick_start.md)

## 5. 示例教程

* [VBSLite 示例教程](./examples.md)

## 6. 配置项参考文档

* [VBSLite XML工具配置文档](./xml_config.md)
* [VBSLite IDL工具配置文档](./idl_config.md)

## 7. API参考连接

* [VBSLite接口文档](./vbslite_api.md)
