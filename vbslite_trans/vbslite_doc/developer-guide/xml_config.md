# VBSLite XML工具配置文档

## 基本结构

```XML

<?xml version="1.0" ?>
<dds>
    <idl>pingpong.idl</idl>
    <network>
        <master>
            ...
        </master>
    </network>
    <discovery>
        <initial_announcements>
           ...
        </initial_announcements>
        <heartbeat>
            ...
        </heartbeat>
        <liveliness>
            ...
        </liveliness>
    </discovery>
    <qos>
        <writer>
            ...
        </writer>
        <reader>
            ...
        </reader>
    </qos>
    <participant>
        <name>node_1</name>
        <domain_id>0</domain_id>
        <discovery>DPSE</discovery>
        <max_remote_participants>8</max_remote_participants>
        <preferred_remote_participant>node_2</preferred_remote_participant>
        <local_rx_buffer>12</local_rx_buffer>
        <udp_rx_buffer>12</udp_rx_buffer>
        <check_crc>false</udp_rx_buffer>
        <writers>
            ...
        </writers>
        <readers>
            ...
        </readers>
    </participant>
</dds>
```

| 根标签 | 一级标签    | 二级标签                     | 使用说明                       |
| ------ | ----------- | ---------------------------- | ------------------------------ |
| dds    |             |                              |                                |
|        | idl         |                              | 设置idl                        |
|        | network     |                              |                                |
|        |             | master                       | 设置网络接口参数               |
|        |             | backup                       | 设置链路冗余                   |
|        | discovery   |                              |                                |
|        |             | initial_announcements        | 设置早期快速发现报文发送频率   |
|        |             | heartbeat                    | 设置 reliable writer 心跳参数  |
|        |             | liveliness                   | 设置 participant 保活参数      |
|        | qos         |                              |                                |
|        |             | writer                       | 设置 data writer QoS 参数      |
|        |             | reader                       | 设置 data reader QoS 参数      |
|        | participant |                              |                                |
|        |             | name                         | 设置本节点 participant 名称    |
|        |             | domain_id                    | 设置本节点所属 rtps domain id  |
|        |             | discovery                    | 设置节点发现类型               |
|        |             | max_remote_participants      | 设置本节点的远端连接的最大数量 |
|        |             | preferred_remote_participant | 设置本节点远端白名单           |
|        |             | local_rx_buffer              | 设置本节点的本地通信buffer大小 |
|        |             | udp_rx_buffer                | 设置本节点的udp通信buffer大小  |
|        |             | check_crc                    | 设置本节点的crc校验的使能状态  |
|        |             | writers                      | 设置发布实体的节点信息         |
|        |             | readers                      | 设置订阅实体的节点信息         |

## IDL 配置

| **标签** | **父标签** | **子标签** | **取值类型** | **使用说明**                  |
| -------------- | ---------------- | ---------------- | ------------------ | ----------------------------------- |
| idl            | dds              | 无               | 字符串             | 1. 指定idl的名称  2. 可以配置多个 |

## 网络配置

### 设置网络接口

| 标签名称 | 父标签  | 子标签  | 取值范围          | 使用说明                                                           |
| -------- | ------- | ------- | ----------------- | ------------------------------------------------------------------ |
| master   | network |         |                   |                                                                    |
|          |         | address | IP格式：A.B.C.D   | 1. 配置网卡 IP  2. 用于向外宣告，本节点 IP                       |
|          |         | netmask | mask格式：A.B.C.D | 1. 配置网卡 IP 掩码  2. 用于判定远端宣告地址是否与当前网卡同网段 |
| backup   | network |         |                   |                                                                    |
|          |         | address | IP格式：A.B.C.D   |                                                                    |
|          |         | netmask | mask格式：A.B.C.D |                                                                    |

## 服务发现

### 设置快速发现

| 标签名称              | 父标签    | 子标签         | 参数标签 | 取值范围 | 使用说明                                      |
| --------------------- | --------- | -------------- | -------- | -------- | --------------------------------------------- |
| announce | discovery |                |          |          |                                               |
|                       |           | times |          | uint16_t | 快速发现阶段，pdp报文发送次数，推荐配置为5    |
|                       |           | period         |          |          | 快速发现阶段，pdp报文发送周期，推荐配置为20ms |
|                       |           |                | sec      | int32_t  |                                               |
|                       |           |                | nanosec  | uint32_t |                                               |

### 设置心跳周期

| 标签名称  | 父标签    | 子标签          | 参数标签 | 取值范围 | 使用说明                                                                   |
| --------- | --------- | --------------- | -------- | -------- | -------------------------------------------------------------------------- |
| heartbeat | discovery |                 |          |          |                                                                            |
|           |           | period          |          |          | 配置 reliable writer 心跳周期                                              |
|           |           |                 | sec      | uint32_t |                                                                            |
|           |           |                 | nanosec  | uint32_t |                                                                            |
|           |           | per_samples |          | uint16_t | 配置 reliable writer，心跳随 sample发送频率，每发送n个sample，发送一个心跳 |

### 设置 participant 保活

| 标签名称   | 父标签    | 子标签         | 参数标签 | 取值范围             | 使用说明                                                                                                                                                                 |
| ---------- | --------- | -------------- | -------- | -------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| liveliness | discovery |                |          |                      |                                                                                                                                                                          |
|            |           | period  |          |                      | 快速发现阶段后，pdp 报文发送周期                                                                                                                                         |
|            |           |                | sec      | int32_t[最大5000000] |                                                                                                                                                                          |
|            |           |                | nanosec  | uint32_t             |                                                                                                                                                                          |
|            |           | lease_duration |          |                      | 1. 配置节点租期参数，远端超出该时间未收到该节点发出的 pdp 报文，视为该节点失活 2. 推荐将 lease_duration 配置为 period 的三倍及以上防止由于偶发丢包导致的断开重连 |
|            |           |                | sec      | int32_t              |                                                                                                                                                                          |
|            |           |                | nanosec  | uint32_t             |                                                                                                                                                                          |

## 服务质量

### 设置绑定key

| 标签名称 | 父标签         | 子标签 | 参数标签 | 取值范围 | 使用说明    |
| -------- | -------------- | ------ | -------- | -------- | ----------- |
| key      | reader或writer |        |          | 字符串   | QoS唯一标识 |

### 设置reliability策略

| 标签名称    | 父标签         | 子标签 | 参数标签 | 取值范围                        | 使用说明                                |
| ----------- | -------------- | ------ | -------- | ------------------------------- | --------------------------------------- |
| reliability | reader或writer |        |          |                                 | 设置writer或reader的reliablity策略      |
|             |                | kind   |          |                                 | 默认值：DDS_BEST_EFFORT_RELIABILITY_QOS |
|             |                |        |          | DDS_RELIABLE_RELIABILITY_QOS    | 丢包重传                                |
|             |                |        |          | DDS_BEST_EFFORT_RELIABILITY_QOS | 丢包不重传                              |

### 设置history策略

| 标签名称 | 父标签         | 子标签      | 参数标签 | 取值范围                  | 使用说明                                                                                                                                                                    |
| -------- | -------------- | ----------- | -------- | ------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| history  | reader或writer |             |          |                           | 设置writer的history策略                                                                                                                                                     |
|          |                | kind        |          |                           | 默认值：DDS_KEEP_LAST_HISTORY_QOS                                                                                                                                           |
|          |                |             |          | DDS_KEEP_LAST_HISTORY_QOS | DDS 实体只保留最新的一些样本。具体来说，当新样本到达时，DDS 将其添加到已有样本的末尾，并删除最旧的样本，以保持指定数量的样本数。这个数量可以通过 history.depth 属性进行设置 |
|          |                |             |          | DDS_KEEP_ALL_HISTORY_QOS  | DDS 实体保留所有接收到的样本，无论其数量如何。当订阅者启动时，它将立即收到所有已发布的样本，而不仅仅是最新的一个。这可能会导致内存使用过多，所以需要谨慎使用。              |
|          |                | depth       |          | uint16_t                  | KEEP_LAST模式下有效，历史缓存的深度（大小）                                                                                                                                 |
|          |                | max_samples |          | uint16_t                  | KEEP_ALL时有效，整个topic的历史缓存大小。                                                                                                                                   |

### 设置durability策略

| 标签名称   | 父标签         | 参数标签 | 取值范围                           | 使用说明                                                                                                                             |
| ---------- | -------------- | -------- | ---------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------ |
| durability | reader或writer |          |                                    | 设置writer的durability策略                                                                                                           |
|            |                | kind     |                                    | 默认值:DDS_TRANSIENT_LOCAL_DURABILITY_QOS。                                                                                          |
|            |                |          | DDS_VOLATILE_DURABILITY_QOS        | 指定数据不需要持久性。这意味着当订阅者离线或重新启动后，它将无法获取历史数据，只能接收到发布者在其重新连接后发送的新数据。           |
|            |                |          | DDS_TRANSIENT_LOCAL_DURABILITY_QOS | 指定数据应该在本地缓存，以便在订阅者离线期间继续使用。这意味着当订阅者重新连接到发布者时，它可以获取历史数据并且可以继续接收新数据。 |

### 设置deadline策略

| 标签名称 | 父标签         | 子标签 | 参数标签 | 取值范围 | 使用说明                 |
| -------- | -------------- | ------ | -------- | -------- | ------------------------ |
| deadline | reader或writer |        |          |          | 设置writer的deadline策略 |
|          |                | period |          |          |                          |
|          |                |        | sec      | int32_t  | 默认值:TIME_INFINITE_SEC |
|          |                |        | nanosec  | uint32_t | 默认值:TIME_INFINITE_SEC |

### 设置lifeSpan策略

| 标签名称 | 父标签         | 子标签 | 参数标签 | 取值范围 | 使用说明                 |
| -------- | -------------- | ------ | -------- | -------- | ------------------------ |
| lifespan | reader或writer |        |          |          | 设置writer的lifespan策略 |
|          |                | period |          |          |                          |
|          |                |        | sec      | int32_t  | 默认值:TIME_INFINITE_SEC |
|          |                |        | nanosec  | uint32_t | 默认值:TIME_INFINITE_SEC |

### 设置liveliness策略

DDS支持Endpoint级别的保活机制，不会真正触发发布/订阅端的配对数据变化，只是通知用户层状态变化，以便用户做出合适的处理。该保活机制主要在发布端（针对本地writer）和订阅端（针对远端writer）启动lease定时器，若发布端lease定时器超时后，发布端和接收端会收到失活通知。

| 标签名称   | 父标签 | 子标签         | 参数标签 | 取值范围                                 | 使用说明                                                                                                                                                                                                                                                                      |
| ---------- | ------ | -------------- | -------- | ---------------------------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| liveliness | writer |                |          |                                          | 设置writer的保活策略                                                                                                                                                                                                                                                          |
|            |        | kind           |          |                                          | 默认值：DDS_AUTOMATIC_LIVELINESS_QOS<br />AUTOMATIC：DDS自动保活，无需用户关注；MANUAL_BY_PARTICIPANT：只要participant中有writer活跃即所有writer均活跃；MANUAL_BY_TOPIC：单个writer控制是否活跃，不予其他writer有联系。MANUAL方式需要用户层发包或者周期调用保活来保持活跃状态 |
|            |        |                |          | DDS_AUTOMATIC_LIVELINESS_QOS             | DDS 实体将自动发送活跃性消息，并在一定时间内未收到来自另一个实体的消息时，认为该实体已失效。这些消息是由 DDS 中间件自动发送的                                                                                                                                                 |
|            |        |                |          | DDS_MANUAL_BY_PARTICIPANT_LIVELINESS_QOS | 表示活跃性消息由应用程序手动发送，但只需要在 DDS participant级别上进行处理。也就是说，当某个实体的活跃性超时时，将通知该实体所在的所有主题。                                                                                                                                  |
|            |        |                |          | DDS_MANUAL_BY_TOPIC_LIVELINESS_QOS       | 表示活跃性消息由应用程序手动发送，并需要在 DDS topic级别上进行处理。也就是说，当某个发布者或订阅者的活跃性超时时，将通知仅与其相关联的主题。                                                                                                                                  |
|            |        | lease_duration |          |                                          | 设置保活超时周期                                                                                                                                                                                                                                                              |
|            |        |                | sec      | int32_t                                  |                                                                                                                                                                                                                                                                               |
|            |        |                | nanosec  | uint32_t                                 |                                                                                                                                                                                                                                                                               |

### 设置ownership策略

| 标签名称  | 父标签         | 子标签 | 参数标签 | 取值范围                    | 使用说明                                                                       |
| --------- | -------------- | ------ | -------- | --------------------------- | ------------------------------------------------------------------------------ |
| ownership | reader或writer |        |          |                             | 设置reader的ownership策略                                                      |
|           |                |        | kind     |                             | 默认值：DDS_SHARED_OWNERSHIP_QOS                                               |
|           |                |        |          | DDS_SHARED_OWNERSHIP_QOS    | 允许多个发布者同时拥有该对象的所有权，每个发布者都可以写入该对象               |
|           |                |        |          | DDS_EXCLUSIVE_OWNERSHIP_QOS | 指定只有一个发布者可以拥有数据对象的所有权，其他发布者无法访问该对象或写入它。 |

### 设置ownership_strength策略

| 标签名称           | 父标签 | 子标签 | 参数标签 | 取值范围 | 使用说明                                                          |
| ------------------ | ------ | ------ | :------- | -------- | ----------------------------------------------------------------- |
| ownership_strength | writer |        |          |          | 设置writer的ownershipStrength策略，仅在ownership为EXCLUSIVE时生效 |
|                    |        |        | value    | uint16_t | 值越大，优先级越高                                                |

### 设置E2E功能

| 标签名称   | 父标签         | 子标签 | 参数标签                  | 取值范围 | 使用说明             |
| ---------- | -------------- | ------ | ------------------------- | :------- | -------------------- |
| e2e_policy | reader或writer |        |                           |          |                      |
|            |                |        | enable                    | 布尔值   | 启用或禁用E2E功能    |
|            |                |        | e2e_p04_min_data_length   | uint16_t | 允许数据包长度最小值 |
|            |                |        | e2e_p04_max_data_length   | uint16_t | 允许数据包长度最大值 |
|            |                |        | e2e_p04_max_delta_counter | uint16_t | 允许数据包最大丢包数 |

## 节点配置

### 设置participant数据标识符

| **标签** | **父标签** | **子标签** | **取值范围** | **使用说明**  |
| -------------- | ---------------- | ---------------- | ------------------ | ------------------- |
| name           | participant      | 无               | 字符串             | participant唯一标识 |

### 设置participant所属域

| **标签** | **父标签** | **子标签** | **取值范围** | **使用说明**    |
| -------------- | ---------------- | ---------------- | ------------------ | --------------------- |
| domain_id      | participant      | 无               | 0-127              | 指定participant的域ID |

### 设置participant发现模式

| **标签** | **父标签** | **子标签** | **取值范围** | **使用说明**                                                                      |
| -------------- | ---------------- | ---------------- | ------------------ | --------------------------------------------------------------------------------------- |
| discovery      | participant      | 无               | [DPSE,DPDE]        | 指定participant的发现模式，DPSE表示静态发现，DPDE表示动态发现。动态发现可以不配置此项。 |

### 设置participant对端节点的个数

|     **标签**     | **父标签** | **子标签** | **取值范围** | **使用说明**                             |
| :---------------------: | ---------------- | ---------------- | ------------------ | ---------------------------------------------- |
| max_remote_participants | participant      | 无               | 1 - 255            | 指定participant的最大对端节点的个数，默认值：8 |

### 设置participant的对端节点白名单

| **标签**               | **父标签** | **子标签** | **取值范围** | **使用说明**                            |
| ---------------------------- | ---------------- | ---------------- | ------------------ | --------------------------------------------- |
| preferred_remote_participant | participant      | 无               | 字符串             | 指定participant优先匹配的对端节点，默认值为空 |

### 设置participant的本地通信收包buffer

| **标签**  | **父标签** | **子标签** | **取值范围** | **使用说明**                                                                            |
| --------------- | ---------------- | ---------------- | ------------------ | --------------------------------------------------------------------------------------------- |
| local_rx_buffer | participant      | 无               | 0 - 32             | 本地通信中配置的rx_buffer的大小，默认值为12，实际取值为2的n次幂，即buffer的大小为 2^12 = 4096 |

### 设置participant的udp通信收包buffer

| **标签** | **父标签** | **子标签** | **取值范围** | **使用说明**                                                                           |
| -------------- | ---------------- | ---------------- | ------------------ | -------------------------------------------------------------------------------------------- |
| udp_rx_buffer  | participant      | 无               | 0 - 32             | udp通信中配置的rx_buffer的大小，默认值为12，实际取值为2的n次幂，即buffer的大小为 2^12 = 4096 |

### 设置participant crc校验的使能状态

| **标签** | **父标签** | **子标签** | **取值范围** | **使用说明**                                               |
| -------------- | ---------------- | ---------------- | ------------------ | ---------------------------------------------------------------- |
| check_crc      | participant      | 无               | 字符串             | 默认值：false，仅支持在 DPDE 中启用 check_crc，值为 false 时禁用 |

### 设置participant的发布实体

| 标签名称 | 父标签      | 子标签           | 参数标签  | 取值范围 | 使用说明                                                                         |
| -------- | ----------- | ---------------- | --------- | -------- | -------------------------------------------------------------------------------- |
| writers  | participant |                  |           |          |                                                                                  |
|          |             | key              |           | 字符串   | writer唯一标识                                                                   |
|          |             | topic            |           | 字符串   | writer发布的topic名称                                                            |
|          |             | type             |           | 字符串   | topic对应的数据类型                                                              |
|          |             | qos              |           | 字符串   | 缺省或者值为default时表示使用默认配置。取值范围限定在 qos 子标签 key             |
|          |             | max_remote_peers |           | uint16_t | 可发现的对端reader实体的最大数量，默认值：1                                      |
|          |             | net_redundancy   |           | 布尔值   | 链路冗余的使能开关，默认值：false                                                |
|          |             | enabled          |           | 布尔值   | 默认值：true。值为 false 时，则该节点则为无效节点。                              |
|          |             | object_id        |           | uint16_t | DPSE 下用户提供，writer标签下值唯一                                              |
|          |             | static_peers     |           |          |                                                                                  |
|          |             |                  | qos       | 字符串   | 设置peer reader qos策略对应的key，用户提供，取值范围限定在 qos 子标签 reader key |
|          |             |                  | object_id | int16_t  | 设置静态发现对端reader的object_id                                                |

### 设置participant的订阅实体

| 标签名称 | 父标签      | 子标签           | 参数标签  | 取值范围 | 使用说明                                                                         |
| -------- | ----------- | ---------------- | --------- | -------- | -------------------------------------------------------------------------------- |
| readers  | participant |                  |           |          |                                                                                  |
|          |             | key              |           | 字符串   | reader唯一标识                                                                   |
|          |             | topic            |           | 字符串   | reader发布的topic名称                                                            |
|          |             | type             |           | 字符串   | topic对应的数据类型                                                              |
|          |             | qos              |           | 字符串   | 缺省或者值为default时表示使用默认配置。取值范围限定在 qos 子标签 key             |
|          |             | max_remote_peers |           | uint16_t | 可发现的对端writer实体的最大数量，默认值：1                                      |
|          |             | net_redundancy   |           | 布尔值   | 链路冗余的使能开关，默认值：false                                                |
|          |             | enabled          |           | 布尔值   | 默认值：true。值为 false 时，则该节点则为无效节点。                              |
|          |             | object_id        |           | uint16_t | DPSE 下用户提供，reader标签下值唯一                                              |
|          |             | static_peers     |           |          |                                                                                  |
|          |             |                  | qos       | 字符串   | 设置peer writer qos策略对应的key，用户提供，取值范围限定在 qos 子标签 writer key |
|          |             |                  | object_id | int16_t  | 设置静态发现对端writer的object_id                                                |

## 配置示例

### 动态发现

sub端配置一个reader，pub端配置一个writer进行动态发现

#### sub端配置

```XML
<?xml version="1.0" ?>
<dds>
        <idl>HelloWorld.idl</idl>
        <network>
                <master>
                        <address>172.31.10.31</address>
                        <netmask>255.255.255.0</netmask>
                </master>
        </network>
        <discovery>
                <initial_announcements>
                        <announce_times>50</announce_times>
                        <period>3 0</period>
                </initial_announcements>
                <heartbeat>
                        <per_max_samples>5</per_max_samples>
                        <period>5 0</period>
                </heartbeat>
                <liveliness>
                        <lease_duration>10 0</lease_duration>
                        <assert_period>5 0</assert_period>
                </liveliness>
        </discovery>
        <qos>
                <reader>
                        <key>r_qos</key>
                        <durability>
                                <kind>DDS_VOLATILE_DURABILITY_QOS</kind>
                        </durability>
                        <reliability>
                                <kind>DDS_RELIABLE_RELIABILITY_QOS</kind>
                        </reliability>
                        <ownership>
                                <kind>DDS_SHARED_OWNERSHIP_QOS</kind>
                        </ownership>
                        <deadline>
                                <period>10 0</period>
                        </deadline>
                        <liveliness>
                                <kind>DDS_AUTOMATIC_LIVELINESS_QOS</kind>
                                <lease_duration>20 0</lease_duration>
                        </liveliness>
                        <history>
                                <kind>DDS_KEEP_LAST_HISTORY_QOS</kind>
                                <depth>5</depth>
                                <max_samples>5</max_samples>
                                <max_instances>1</max_instances>
                                <max_samples_per_instance>5</max_samples_per_instance>
                        </history>
                </reader>
        </qos>
        <participant>
                <name>node_1</name>
                <domain_id>0</domain_id>
                <discovery>DPDE</discovery>
                <max_remote_participants>8</max_remote_participants>
                <reader>
                        <key>r0</key>
                        <topic>domain_0_topic_0Topic</topic>
                        <type>HelloWorld</type>
                        <qos>r_qos</qos>
                        <max_remote_peers>1</max_remote_peers>
                </reader>
        </participant>
</dds>
```

#### pub端配置

```XML
<?xml version="1.4" ?>
<dds>
        <idl>HelloWorld.idl</idl>
        <network>
                <master>
                        <address>172.31.10.111</address>
                        <netmask>255.255.255.0</netmask>
                </master>
        </network>
        <discovery>
                <initial_announcements>
                        <announce_times>50</announce_times>
                        <period>3 0</period>
                </initial_announcements>
                <heartbeat>
                        <per_max_samples>5</per_max_samples>
                        <period>5 0</period>
                </heartbeat>
                <liveliness>
                        <lease_duration>10 0</lease_duration>
                        <assert_period>5 0</assert_period>
                </liveliness>
        </discovery>
        <qos>
                <writer>
                        <key>w_qos</key>
                        <durability>
                                <kind>DDS_VOLATILE_DURABILITY_QOS</kind>
                        </durability>
                        <reliability>
                                <kind>DDS_RELIABLE_RELIABILITY_QOS</kind>
                        </reliability>
                        <ownership>
                                <kind>DDS_SHARED_OWNERSHIP_QOS</kind>
                        </ownership>
                        <ownership_strength>
                                <value>0</value>
                        </ownership_strength>
                        <deadline>
                                <period>10 0</period>
                        </deadline>
                        <liveliness>
                                <kind>DDS_AUTOMATIC_LIVELINESS_QOS</kind>
                                <lease_duration>2 0</lease_duration>
                        </liveliness>
                        <history>
                                <kind>DDS_KEEP_LAST_HISTORY_QOS</kind>
                                <depth>5</depth>
                                <max_samples>5</max_samples>
                                <max_instances>1</max_instances>
                                <max_samples_per_instance>5</max_samples_per_instance>
                        </history>
                </writer>
        </qos>
        <participant>
                <name>node_2</name>
                <domain_id>0</domain_id>
                <discovery>DPDE</discovery>
                <max_remote_participants>8</max_remote_participants>
                <writer>
                        <key>w0</key>
                        <topic>domain_0_topic_0Topic</topic>
                        <type>HelloWorld</type>
                        <qos>w_qos</qos>
                        <max_remote_peers>1</max_remote_peers>
                </writer>
        </participant>
</dds>

```

### 静态发现

sub端配置一个reader，pub端配置一个writer进行静态发现

#### sub端配置

```XML
<?xml version="1.0" ?>
<dds>
    <idl>HelloWorld.idl</idl>
            <network>
                    <master>
                            <address>172.31.10.31</address>
                            <netmask>255.255.255.0</netmask>
                    </master>
            </network>
            <discovery>
                    <announce>
                            <times>50</times>
                            <period>3 0</period>
                    </announce>
                    <heartbeat>
                            <per_samples>5</per_samples>
                            <period>5 0</period>
                    </heartbeat>
                    <liveliness>
                            <lease_duration>20 0</lease_duration>
                            <period>5 0</period>
                    </liveliness>
            </discovery>
            <qos>
                <reader>
                        <key>reader0_qos</key>
                        <durability>
                                <kind>DDS_VOLATILE_DURABILITY_QOS</kind>
                        </durability>
                        <reliability>
                                <kind>DDS_RELIABLE_RELIABILITY_QOS</kind>
                        </reliability>
                        <ownership>
                                <kind>DDS_SHARED_OWNERSHIP_QOS</kind>
                        </ownership>
                        <deadline>
                                <period>10 0</period>
                        </deadline>
                        <liveliness>
                                <kind>DDS_AUTOMATIC_LIVELINESS_QOS</kind>
                                <lease_duration>20 0</lease_duration>
                        </liveliness>
                        <history>
                                <kind>DDS_KEEP_LAST_HISTORY_QOS</kind>
                                <depth>50</depth>
                                <max_samples>50</max_samples>
                                <max_instances>1</max_instances>
                                <max_samples_per_instance>50</max_samples_per_instance>
                        </history>
                </reader>
                <writer>
                        <key>peer_writer</key>
                        <durability>
                                <kind>DDS_VOLATILE_DURABILITY_QOS</kind>
                        </durability>
                        <reliability>
                                <kind>DDS_RELIABLE_RELIABILITY_QOS</kind>
                        </reliability>
                        <ownership>
                                <kind>DDS_SHARED_OWNERSHIP_QOS</kind>
                        </ownership>
                        <ownership_strength>
                                <value>0</value>
                        </ownership_strength>
                        <deadline>
                                <period>10 0</period>
                        </deadline>
                        <liveliness>
                                <kind>DDS_AUTOMATIC_LIVELINESS_QOS</kind>
                                <lease_duration>20 0</lease_duration>
                        </liveliness>
                        <history>
                                <kind>DDS_KEEP_LAST_HISTORY_QOS</kind>
                                <depth>50</depth>
                                <max_samples>50</max_samples>
                                <max_instances>1</max_instances>
                                <max_samples_per_instance>50</max_samples_per_instance>
                        </history>
                </writer>
        </qos>
        <participant>
                <name>app1</name>
                <domain_id>0</domain_id>
                <discovery>DPSE</discovery>
                <reader>
                        <key>r0</key>
                        <topic>domain_0_topic_0Topic</topic>
                        <type>HelloWorld</type>
                        <qos>reader0_qos</qos>
                        <object_id>100</object_id>
                        <max_remote_peers>1</max_remote_peers>
                        <static_peers>
                                <object_id>50</object_id>
                                <qos>peer_writer</qos>
                        </static_peers>
                </reader>
        </participant>
</dds>
```

#### pub端配置

```xml
<?xml version="1.4" ?>
<dds>
    <idl>HelloWorld.idl</idl>
            <network>
                    <master>
                            <address>172.31.10.111</address>
                            <netmask>255.255.255.0</netmask>
                    </master>
            </network>
            <discovery>
                    <announce>
                            <times>50</times>
                            <period>3 0</period>
                    </announce>
                    <heartbeat>
                            <per_samples>5</per_samples>
                            <period>5 0</period>
                    </heartbeat>
                    <liveliness>
                            <lease_duration>20 0</lease_duration>
                            <period>5 0</period>
                    </liveliness>
            </discovery>
            <qos>
                <reader>
                        <key>peer_reader</key>
                        <durability>
                                <kind>DDS_VOLATILE_DURABILITY_QOS</kind>
                        </durability>
                        <reliability>
                                <kind>DDS_RELIABLE_RELIABILITY_QOS</kind>
                        </reliability>
                        <ownership>
                                <kind>DDS_SHARED_OWNERSHIP_QOS</kind>
                        </ownership>
                        <deadline>
                                <period>10 0</period>
                        </deadline>
                        <liveliness>
                                <kind>DDS_AUTOMATIC_LIVELINESS_QOS</kind>
                                <lease_duration>20 0</lease_duration>
                        </liveliness>
                        <history>
                                <kind>DDS_KEEP_LAST_HISTORY_QOS</kind>
                                <depth>50</depth>
                                <max_samples>50</max_samples>
                                <max_instances>1</max_instances>
                                <max_samples_per_instance>50</max_samples_per_instance>
                        </history>
                </reader>
                <writer>
                        <key>writer0_qos</key>
                        <durability>
                                <kind>DDS_VOLATILE_DURABILITY_QOS</kind>
                        </durability>
                        <reliability>
                                <kind>DDS_RELIABLE_RELIABILITY_QOS</kind>
                        </reliability>
                        <ownership>
                                <kind>DDS_SHARED_OWNERSHIP_QOS</kind>
                        </ownership>
                        <ownership_strength>
                                <value>0</value>
                        </ownership_strength>
                        <deadline>
                                <period>10 0</period>
                        </deadline>
                        <liveliness>
                                <kind>DDS_AUTOMATIC_LIVELINESS_QOS</kind>
                                <lease_duration>20 0</lease_duration>
                        </liveliness>
                        <history>
                                <kind>DDS_KEEP_LAST_HISTORY_QOS</kind>
                                <depth>50</depth>
                                <max_samples>50</max_samples>
                                <max_instances>1</max_instances>
                                <max_samples_per_instance>50</max_samples_per_instance>
                        </history>
                </writer>
        </qos>
        <participant>
                <name>app2</name>
                <domain_id>0</domain_id>
                <discovery>DPSE</discovery>
                <writer>
                        <key>w0</key>
                        <topic>domain_0_topic_0Topic</topic>
                        <type>HelloWorld</type>
                        <qos>writer0_qos</qos>
                        <object_id>50</object_id>
                        <max_remote_peers>1</max_remote_peers>
                        <static_peers>
                                <object_id>100</object_id>
                                <qos>peer_reader</qos>
                        </static_peers>
                </writer>
        </participant>
</dds>
```

### 本地通信配置

配置本地通信时，reader和writer的topic、type、qos需要保持一致。

#### 本地配置1个writer和1个reader

```XML
<?xml version="1.0" ?>
<dds>
        <idl>HelloWorld.idl</idl>
        <network>
                <master>
                        <!-- 替换成本地ip -->
                        <address>172.31.3.71</address>
                        <netmask>255.255.255.0</netmask>
                </master>
        </network>
        <discovery>
                <announce>
                        <times>50</times>
                        <period>3 0</period>
                </announce>
                <heartbeat>
                        <per_samples>5</per_samples>
                        <period>5 0</period>
                </heartbeat>
                <liveliness>
                        <lease_duration>10 0</lease_duration>
                        <period>5 0</period>
                </liveliness>
        </discovery>
        <participant>
                <name>node_1</name>
                <domain_id>0</domain_id>
                <max_remote_participants>9</max_remote_participants>
                <local_rx_buffer>13</local_rx_buffer>
                <writer>
                        <key>w1</key>
                        <topic>MVBS_topic1</topic>
                        <type>MVBS::HelloWorld</type>
                        <qos>default</qos>
                        <max_remote_peers>1</max_remote_peers>
                </writer>
                <reader>
                        <key>r1</key>
                        <topic>MVBS_topic1</topic>
                        <type>MVBS::HelloWorld</type>
                        <qos>default</qos>
                        <max_remote_peers>1</max_remote_peers>
                </reader>
        </participant>
</dds>
```
