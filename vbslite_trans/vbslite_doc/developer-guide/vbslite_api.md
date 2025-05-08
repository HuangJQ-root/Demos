# VBSLite接口文档

## RTE 层API

### Rte_Dds_Init

**接口原型：**

```C
typedef struct participant *         Rte_Dds_Participant;

Rte_Dds_ReturnType Rte_Dds_Init(Rte_Dds_Participant ptcp);
```

**功能描述：**

  rte适配层初始化接口，初始化指定的particpant实例

  初始化完成之后才可以进行数据的收发操作

**入参：**

  `Rte_Dds_Participant ptcp`：ptcp为获取的paricipant实体

* 由XML工具生成的接口 **`Rte_Dds_Participant Rte_Dds_GetParticipant()`** 来获取指定的participant

**出参：**

  **无**

**返回值：**

  返回值类型为 `Rte_Dds_ReturnType`

* RTE_DDS_RETCODE_OK：初始化成功
* RTE_DDS_RETCODE_ILLEGAL_OPERATION：重复初始化
* RTE_DDS_RETCODE_BAD_PARAMETER：传入参数为无效参数
* RTE_DDS_RETCODE_PRECONDITION_NOT_MET：读取配置信息失败
* RTE_DDS_RETCODE_ERROR：启动participant失败

**注意事项** ：

* 只在初始化时调用一次，避免重复初始化
* 若返回值为RTE_DDS_RETCODE_PRECONDITION_NOT_MET，表明底层以太网没有准备好，建议用户重新调用该接口进行初始化

**样例代码：**

```C
extern Rte_Dds_Participant Rte_Dds_GetParticipant();

Rte_Dds_Participant ptcp = Rte_Dds_GetParticipant();
if (Rte_Dds_Init(ptcp) != RTE_DDS_RETCODE_OK) {
        return NULL;
}

pr_info("Rte_Dds_Init OK!");
```

### Rte_Dds_GetReader

**接口原型：**

```C
typedef struct reader*        Rte_Dds_Reader;

Rte_Dds_Reader Rte_Dds_GetReader(Rte_Dds_Participant ptcp, const char* topic_name);
```

**功能描述：**

  DDS初始化之后，就可以获取指定 topic_name 的读Topic操作对象，此对象可用来接收DDS数据

**入参：**

  `Rte_Dds_Participant ptcp`：获取的participant实体

  `const char* topic_name`： 指定一个 topic_name

**出参：**

  **无**

**返回值：**

返回值类型为 `Rte_Dds_Reader`(一个不完整类型的指针)

* NULL： 获取失败，（参数不合法或者不存在 `topic_name`对应的 `Rte_Dds_Reader`对象）
* 非NULL： 有效的 `Rte_Dds_Reader` 对象

**注意事项** ：

* 建议在初始化时获取对应的Reader对象，避免重复查找

**样例代码：**

```C
static Rte_Dds_Reader r;
r = Rte_Dds_GetReader(ptcp, topic_r.name);
```

### Rte_Dds_GetWriter

**接口原型：**

```C
typedef struct writer*        Rte_Dds_Writer;

Rte_Dds_Writer Rte_Dds_GetWriter(Rte_Dds_Participant ptcp, const char* topic_name);
```

**功能描述：**

  DDS初始化之后，就可以获取指定 topic_name 的写Topic操作对象，此对象可用来发送DDS数据

**入参：**

  `Rte_Dds_Participant ptcp`：获取的participant实体

  `const char* topic_name`： 指定一个 topic_name

**出参：**

  **无**

**返回值：**

  返回值类型为 `Rte_Dds_Writer`(一个不完整类型的指针)

* NULL： 获取失败，（参数不合法或者不存在 `topic_name`对应的 `Rte_Dds_Writer`对象）
* 非NULL： 有效的 `Rte_Dds_Writer`对象

 **注意事项** ：

* 建议在初始化时获取对应的Writer对象，避免重复查找

**样例代码：**

```C
static Rte_Dds_Writer w;
w = Rte_Dds_GetWriter(ptcp, topic_w.name);
```

### Rte_Dds_GetReaderStats

**接口原型：**

```C
Rte_Dds_ReturnType Rte_Dds_GetReaderStats(Rte_Dds_Reader r, Rte_Dds_TopicStats *stats);
```

**功能描述：**

  获取一个 `Rte_Dds_Reader`对象的状态，包括当前在线读写者数量、离线读写者数量、接收数据、丢失数据等信息

 **入参** ：

  `Rte_Dds_Reader r`： 指定一个Reader对象

 **出参** ：

struct Rte_Dds_TopicStats stats* ：获取该Reader对象的状态，反映了topic所有可感知的状态变化，包括：

* *size_t instances* ：当前已经注册的instance个数
* *size_t remotes_online* ：目前在线的对端writer数量
* *size_t total_remotes_online* ：所有匹配过的writer数量
* *size_t total_remotes_offline* ：所有离线的writer数量（ *total_remotes_offline = total_remotes_online - remotes_online* ）
* *size_t deadline_timeout* ：未在截止时间内接收的样本的累计数量
* *size_t sample_lost* ：丢失的样本数量
* *size_t sample_committed* ：所有已接收的且数据不为空的样本数量
* *size_t sample_rejected* ：拒绝的样本数量
* *size_t event_bitmap* ： 未使用

 **返回值** ：

  类型为Rte_Dds_ReturnType

* RTE_DDS_RETCODE_OK：获取状态成功
* RTE_DDS_RETCODE_BAD_PARAMETER：参数错误
* RTE_DDS_RETCODE_ERROR：获取状态失败

 **注意事项** ：

* 在读取状态信息时，deadline_timeout、sample_lost、sample_committed和sample_rejected等字段，可能存在后期数目小于前期的情况，这是由于dds在不停地接收数据，整体数目超过了stats能够正常计数的范围，出现了反转

 **样例代码** ：

```C
void show_info(Rte_Dds_Reader r)
{
        Rte_Dds_TopicStats stats;
        Rte_Dds_ReturnType ret = Rte_Dds_GetReaderStats(r, &stats);

        if (RTE_DDS_RETCODE_OK != ret) {
                return;
        }

        pr_info("instances: %lu\n", stats.instances);
        pr_info("remotes_online: %lu\n", stats.remotes_online);
        pr_info("total_remotes_offline: %lu\n", stats.total_remotes_offline);
        pr_info("deadline_timeout: %lu\n", stats.deadline_timeout);
        pr_info("sample_lost: %lu\n", stats.sample_lost);
        pr_info("sample_committed: %lu\n", stats.sample_committed);
        pr_info("sample_rejected: %lu\n", stats.sample_rejected);
}
```

### Rte_Dds_GetWriterStats

**接口原型：**

```C
Rte_Dds_ReturnType Rte_Dds_GetWriterStats(Rte_Dds_Writer w, Rte_Dds_TopicStats *stats);
```

**功能描述：**

  获取一个 `Rte_Dds_Writer`对象的状态

 **入参** ：

  `Rte_Dds_Writer w`： 指定一个Writer对象

 **出参** ：

struct Rte_Dds_TopicStats stats* ：获取该Writer对象的状态，反映了topic所有可感知的状态变化，包括：

* *size_t instances* ：当前已经注册的instance个数
* *size_t remotes_online* ：目前在线的对端reader数量
* *size_t total_remotes_online* ：所有匹配过的reader数量
* *size_t total_remotes_offline* ：所有离线的reader数量（ *total_remotes_offline = total_remotes_online - remotes_online* ）
* *size_t deadline_timeout* ：未在截止时间内接收的样本的累计数量
* *size_t sample_lost* ：丢失的样本数量
* *size_t sample_committed* ：所有已接收的且数据不为空的样本数量
* *size_t sample_rejected* ：拒绝的样本数量
* *size_t event_bitmap* ： 未使用

 **返回值** ：

  返回值类型为 `Rte_Dds_ReturnType`

* RTE_DDS_RETCODE_OK：获取状态成功
* RTE_DDS_RETCODE_BAD_PARAMETER：参数错误
* RTE_DDS_RETCODE_ERROR：获取状态失败

 **注意事项** ：

* 在读取状态信息时，deadline_timeout、sample_lost、sample_committed和sample_rejected等字段，可能存在后期数目小于前期的情况，这是由于dds在不停地接收数据，整体数目超过了stats能够正常计数的范围，出现了反转

 **样例代码** ：

```C
void show_info(Rte_Dds_Writer w)
{
        Rte_Dds_TopicStats stats;
        Rte_Dds_ReturnType ret = Rte_Dds_GetWriterStats(w, &stats);

        if (RTE_DDS_RETCODE_OK != ret) {
                return;
        }

        pr_info("instances: %lu\n", stats.instances);
        pr_info("remotes_online: %lu\n", stats.remotes_online);
        pr_info("total_remotes_offline: %lu\n", stats.total_remotes_offline);
        pr_info("deadline_timeout: %lu\n", stats.deadline_timeout);
        pr_info("sample_lost: %lu\n", stats.sample_lost);
        pr_info("sample_committed: %lu\n", stats.sample_committed);
        pr_info("sample_rejected: %lu\n", stats.sample_rejected);
}
```

### Rte_Dds_GetReaderOnlinePeers

**接口原型：**

```C
size_t Rte_Dds_GetReaderOnlinePeers(Rte_Dds_Reader r, Rte_Dds_Peers *peer, size_t n);
```

 **功能描述** ：

  查询该Reader的远端节点状态, 比如在发送数据之前，判断远端节点是否在线

**入参：**

  `Rte_Dds_Reader r`： 指定一个Reader对象

  `size_t n`： peers的数组大小

**出参：**

  `struct Rte_Dds_Peers* peers`：Rte_Dds_Peers数组，包含在远端信息

```C
struct Rte_Dds_Peers {
    struct guid guid;// 远端节点的 guid
    char *remote_name;// 远端节点的 name
};
```

**返回值：**

  返回值类型为 `size_t`，表示远端节点数量：

1. 如果 `peer == NULL` 或者 `n = 0`，该接口会返回已经匹配远端节点的个数
2. 如果 `peer != NULL` 且 `n != 0`，则会将已经匹配的远端节点的信息填入到指定 peer 数组中去
   1. 如果实际匹配节点数 > n, 只填入 n 个远端节点信息，返回 n
   2. 如果实际匹配节点数 <= n, 会填入所有匹配节点信息，并返回所有匹配节点的数量

 **注意事项** ：

1. 返回值返回匹配的远端个数，即peer数组中有效数据个数
2. remote_name 可能为空指针。如远端下线后获取数据，使用时需注意
3. 若remote_name不为NULL，则为XML中配置（VBSLite）的node配置的key+ip，如node_1_127.0.0.1；如果是VBSPro发出的partcipant_name，按照VBSPro配置输出

**样例代码：**

```C
int peers_num = 5;
struct Rte_Dds_Peers peers[5];
Rte_Dds_Reader r = Rte_Dds_GetReader(topic_r.name);

size_t ret_num = Rte_Dds_GetReaderOnlinePeers(r, peers, peers_num);
// ret_num不一定等于peers_num
// 用户可能需要知道当前在线的5个对端，但实际只有2个，ret_num表示实际个数
for (int i = 0; i < ret_num; i++) {
    struct Rte_Dds_Peers *peer = &peers[i];
    pr_info("guid_prefix: %d %d %d %d %d %d %d %d %d %d %d %d",
                    peer->guid.prefix.id[0], peer->guid.prefix.id[1],
                    peer->guid.prefix.id[2], peer->guid.prefix.id[3],
                    peer->guid.prefix.id[4], peer->guid.prefix.id[5],
                    peer->guid.prefix.id[6], peer->guid.prefix.id[7],
                    peer->guid.prefix.id[8], peer->guid.prefix.id[9],
                    peer->guid.prefix.id[10], peer->guid.prefix.id[11]);
    pr_info("entity_kind: %d, entity_key: %d %d %d",
                    peer->guid.eid.entity_kind, peer->guid.eid.entity_key[0],
                    peer->guid.eid.entity_key[1], peer->guid.eid.entity_key[2]);
    pr_info("remote_name: %s", (peer->remote_name == NULL)? "NULL": peer->remote_name);
}

pr_info("topic(%s) online peers is %d\n", topic.name, ret_num);
```

### Rte_Dds_GetWriterOnlinePeers

**接口原型：**

```C
size_t Rte_Dds_GetWriterOnlinePeers(Rte_Dds_Writer r, Rte_Dds_Peers *peer, size_t n);
```

 **功能描述** ：

  查询该Writer的远端节点状态, 比如在发送数据之前，判断远端节点是否在线

**入参：**

  `Rte_Dds_Writer w`： 指定一个Writer对象

  `size_t n`： peers的数组大小

**出参：**

  `Rte_Dds_Peers *peer`： 指定一个 peer 数组用来带回每个节点的信息

```C
struct Rte_Dds_Peers {
        struct guid guid;    // 远端节点的 guid
        char *remote_name;   // 远端节点的 name
}
```

**返回值：**

1. 如果 `peer == NULL` 或者 `n = 0`，该接口会返回已经匹配远端节点的个数
2. 如果 `peer != NULL` 且 `n != 0`，则会将已经匹配的远端节点的信息填入到指定 peer 数组中去
   1. 如果实际匹配节点数 > n, 只填入 n 个远端节点信息，返回 n
   2. 如果实际匹配节点数 <= n, 会填入所有匹配节点信息，并返回所有匹配节点的数量

 **注意事项** ：

1. 返回值返回匹配的远端个数，即peer数组中有效数据个数
2. remote_name 可能为空指针。如远端下线后获取数据，使用时需注意
3. 若remote_name不为NULL，则为XML中配置（VBSLite）的node配置的key+ip，如node_1_127.0.0.1；如果是VBSPro发出的partcipant_name，按照VBSPro配置输出

**样例代码：**

```C
int peers_num = 5;
struct Rte_Dds_Peers peers[5];
Rte_Dds_Writer w = Rte_Dds_GetWriter(topic_w.name);

size_t ret_num = Rte_Dds_GetWriterOnlinePeers(w, peers, peers_num);
// ret_num不一定等于peers_num
// 用户可能需要知道当前在线的5个对端，但实际只有2个，ret_num表示实际个数
for (int i = 0; i < ret_num; i++) {
    struct Rte_Dds_Peers *peer = &peers[i];
    pr_info("guid_prefix: %d %d %d %d %d %d %d %d %d %d %d %d",
                    peer->guid.prefix.id[0], peer->guid.prefix.id[1],
                    peer->guid.prefix.id[2], peer->guid.prefix.id[3],
                    peer->guid.prefix.id[4], peer->guid.prefix.id[5],
                    peer->guid.prefix.id[6], peer->guid.prefix.id[7],
                    peer->guid.prefix.id[8], peer->guid.prefix.id[9],
                    peer->guid.prefix.id[10], peer->guid.prefix.id[11]);
    pr_info("entity_kind: %d, entity_key: %d %d %d",
                    peer->guid.eid.entity_kind, peer->guid.eid.entity_key[0],
                    peer->guid.eid.entity_key[1], peer->guid.eid.entity_key[2]);
    pr_info("remote_name: %s", (peer->remote_name == NULL)? "NULL": peer->remote_name);
}

pr_info("topic(%s) online peers is %d\n", topic.name, ret_num);
```

### Rte_Dds_RxData

**接口原型：**

```C
typedef struct sample_info        Rte_Dds_SampleInfo

Rte_Dds_ReturnType Rte_Dds_RxData(Rte_Dds_Reader r, bool take, Rte_Dds_TopicData *data, Rte_Dds_SampleInfo *src_info)
```

**功能描述：**

 从指定的一个Reader对象中读出一个sample出来

**入参** ：

  Rte_Dds_Reader r：指定一个 Reader 对象

  take：指定在history cache中读出一个sample之后，是否需要删除historycache中原始样本

* ture：要从history cache中删除原始样本

* false： 不删除 history cache中原始样本

**出参：**

  `Rte_Dds_TopicData *data`： 指定数据，初始化方式同发送接口，用户从中获取数据

  `Rte_Dds_SampleInfo *src_info`： 针对存在多个sample发送方，用于获取sample发送方的信息

* 若为NULL，则不需获取sample信息，
* 若不为空，则会带回sample的来源信息

```C
struct e2e_info {
          uint32_t e2e_status;//e2e状态，具体参考e2e设计
          uint16_t counter;//e2e count计数
};
struct sample_info {
        struct Rte_Dds_Peers src_info;
        struct e2e_info info_e2e;// e2e信息
};
```

**返回值：**

  返回值类型为 `Rte_Dds_ReturnType`

* RTE_DDS_RETCODE_OK：获取sample成功
* RTE_DDS_RETCODE_BAD_PARAMETER：参数错误
* RTE_DDS_RETCODE_ERROR：获取sample失败

**注意事项：**

* struct Rte_Dds_Peers 中的remote_name 可能为空指针。如远端下线后获取数据，使用时需注意
* 在hisroty depth设置较小时，利用Rte_Dds_RxData读取数据的频率应大于利用Rte_Dds_TxData发送数据的频率，即读比写快，避免丢失数据。建议freq(Rx)>=2freq(Tx)

**样例代码：**

  step1 和 step 2 初始化一次之后， step3可以反复操作

```C
// 1.初始化topic
Rte_Dds_TopicId topic_r = DEF_RTE_DDS_TOPIC("hybrid2", {0});

// 2.数据打包
HybridMsg2 sample2;
HybridMsg2_init(&sample2)
Rte_Dds_TopicData data_r;
Rte_Dds_PackData(&data_r, &sample2);
struct sample_info info;
Rte_Dds_Reader r = Rte_Dds_GetReader(topic_r.name);

// 3.数据读取：
if (Rte_Dds_RxData(r, TRUE, &data_r,&info) == RTE_DDS_RETCODE_OK) {
    printf("--------rx msg : sample2.msg = %s\n", sample2.msg);
}
```

### Rte_Dds_RxIndication

**接口原型：**

```C
void Rte_Dds_RxIndication(Rte_Dds_Reader r, Rte_Dds_Instance inst);
```

 **功能描述** ：

该接口是一个事件回调函数，不用手动调用。当VBSLite协议栈收到一个sample，放入到history cache中之后，就回调该Reader的该事件处理方法

**入参：**

  `Rte_Dds_Reader r`： 这个Reader history cache引入了新样本，变得可读

  `Rte_Dds_Instance inst`： 在没有使用 instance 的场景下，inst 参数则为INSTANCE_INVALID

**出参：**

无

**返回值：**

无

 **注意事项** ：

* 由用户重写void Rte_Dds_RxIndication(Rte_Dds_TopicId *topic)，reader在接收到topic相关数据后，执行用户重写的Rte_Dds_RxIndication接口
* 建议用户在此函数中使用标记或者计数来记录某topic数据待读取，而不要直接进行数据读取，避免阻塞dds 接收任务的执行，在数据量大的时候，主动使用history cache的qos来进行sample覆盖、丢弃，而避免因为接收数据不及时导致的前端报文被迫丢弃

 **样例代码** ：

```C
bool flag = false;

// 用户重写
void Rte_Dds_RxIndication(Rte_Dds_Reader r, Rte_Dds_Instance inst);
{
    const char * topic_name = Rte_Dds_Reader_Get_TopicName(r);
    if(strcmp(topic_name,"xxx")){
        flag = true;
    }
}

void Other_Control_Function(){
    Rte_Dds_TopicId topic_r = DEF_RTE_DDS_TOPIC("xxx",{0});
    HybridMsg1 sample1;
    HybridMsg1_init(&sample1);
    Rte_Dds_TopicData data_r;
    Rte_Dds_PackData(&data_r, &sample1);

    if(flag){
        // 接收数据
        if (Rte_Dds_RxData(&topic_r, TRUE, &data_r, NULL) == RTE_DDS_RETCODE_OK) {
            printf("--------rx msg : sample1.msg = %s\n", sample1.msg);
        }
        flag = false;
     }
}
```

### Rte_Dds_TxData

**接口原型：**

```C
typedef struct sequence_number            Rte_Dds_SequenceNumber

Rte_Dds_ReturnType Rte_Dds_TxData(Rte_Dds_Writer w, Rte_Dds_TopicData *data, Rte_Dds_SequenceNumber *writesn);
```

**功能描述：**

  通过指定一个Writer操作对象，来发送DDS数据

 **入参** ：

* `Rte_Dds_Writer w`： 指定一个Writer操作对象
* `Rte_Dds_TopicData data`： 指定一个待发送的Data对象

  使用宏**Rte_Dds_PackData**进行打包

```C
// 申请一个对应topic的消息体
HybridMsg1 sample1;
HybridMsg1_init(sample1)
Rte_Dds_TopicData data_w;
// 打包 data_w
Rte_Dds_PackData(&data_w, &sample1);
```

 **出参** ：

* `Rte_Dds_SequenceNumber *writesn`： 用于标记 sample 对应的序列号，用于后续通过 `Rte_Dds_Get_Sample_TxStatus`来查询该sample后续的发送状态。若无需跟踪数据样本的状态，可将 `writesn`参数置为 `NULL`

**返回值：**

  返回值类型为 `Rte_Dds_ReturnType`

* RTE_DDS_RETCODE_OK：Sample成功放入到Writer的CacheChange中
* RTE_DDS_RETCODE_BAD_PARAMETER：参数错误
* RTE_DDS_RETCODE_OUT_OF_RESOURCES：创建cachechange失败

 **注意事项** ：

* Sample发送成功或者失败的情况，暂不反馈在返回值中，暂时依然只能通过接口 `Rte_Dds_Get_Sample_TxStatus`来查询发送情况
* 若无需跟踪数据样本的状态，则将writesn参数传入NULL
* writesn如果不为NULL, 则底层返回sample的sequence_number, 用于跟踪sample的发送结果
* 当前 writesn 全局使用，可以使用特定接口 `Rte_Dds_Get_Sample_TxStatus`查询对应发送包的状态

**样例代码：**

  step1 和 step2 初始化一次之后， step3 和step4可以反复操作

```C
// 1.初始化topic

Rte_Dds_TopicId topic_w = DEF_RTE_DDS_TOPIC("hybrid1",{0});
// 2.数据打包
HybridMsg1 sample1;
HybridMsg1_init(&sample1);
Rte_Dds_TopicData data_w;
Rte_Dds_PackData(&data_w, &sample1);
Rte_Dds_Writer w = Rte_Dds_GetWriter(topic_w.name);
struct sequence_number writesn;

for(int i = 0; i<10; i++){
    // 3.修改数据
    sample1.id = 0x123;

    // 4.发送数据：case1： writensn用于查询发送包状态
    ret = Rte_Dds_TxData(w, &data_w, &writesn);
    if（ret != RTE_DDS_RETCODE_OK）{
        printf("tx failed!\n");
    }
    // 4.发送数据，case2：用户不监控发送包状态
    ret = Rte_Dds_TxData(w, &data_w, NULL);
    if（ret != RTE_DDS_RETCODE_OK）{
        printf("tx failed!\n");
    }
}
```

### Rte_Dds_Get_Sample_TxStatus

**接口原型：**

```C
typedef uint32_t            Rte_Dds_TransStatus

Rte_Dds_ReturnType Rte_Dds_Get_Sample_TxStatus(Rte_Dds_Writer w, Rte_Dds_SequenceNumber writersn, Rte_Dds_TransStatus *status);
```

**功能描述：**

  获取指定writersn 对应的数据包的状态

**入参：**

  `Rte_Dds_Writer w`： 指定一个Writer对象

  `Rte_Dds_SequenceNumber writersn`：指定一个发送后的样本序列号，用于跟踪该样本的状态

**出参：**

  `Rte_Dds_TransStatus *status`：`status`有效值有

* TRANS_CODE_INVALID(0)：表示无效
* TRANS_CODE_ALL_SUCCESS(1)： 全部发送出去且都收到了ACK
* TRANS_CODE_ALL_SUCCESS_ALL_OUT(2)： 表示全部发送出去
* TRANS_CODE_PART_FAIL(100)：不使用
* TRANS_CODE_PART_FAIL_PART_OUT(101)：表示chachechange部分未发送出去
* TRANS_CODE_PART_FAIL_HAS_BEEN_RESENT(102)：表示chachechange部分未发送出去，但重传了
* TRANS_CODE_PART_FAIL_PART_ACK：表示只收到部分ACK，还未全部收到，用户可能需要等待一会儿
* TRANS_CODE_ALL_FAIL(200)： 不使用
* TRANS_CODE_ALL_FAIL_NO_PROXY_HAS_MATCHED(201)： 全部未发出去，主题匹配了，但没有发送代理
* TRANS_CODE_ALL_FAIL_NO_PROXY_NO_MATCHED(202)：  全部未发出去，主题未匹配，且没有发送代理
* TRANS_CODE_ALL_FAIL_PROXY_INVALID(203)： 全部未发出去，代理存在但无效
* TRANS_CODE_ALL_FAIL_OTHERS(204)： 全部发送失败，其他原因
* TRANS_CODE_ALL_FAIL_NONE_ACK(205)： 全部发出去了，但一个ACK都未收到
* TRANS_CODE_NO_STATUS_CC_DELETED(300)： cachechange被删除
* TRANS_CODE_UPPER_LIMIT ： 该值放置在末尾以进行有效值检查

**返回值：**

  返回值为 `Rte_Dds_ReturnType`类型：

* RTE_DDS_RETCODE_OK：获取sample状态成功
* RTE_DDS_RETCODE_BAD_PARAMETER：参数错误
* RTE_DDS_RETCODE_ERROR：获取sample状态失败

**注意事项：**

1. 当 `Rte_Dds_SequenceNumber`无效时，状态为 *TRANS_CODE_NO_STATUS_CC_DELETED* 
2. 当 `Rte_Dds_SequenceNumber`有效时，返回样本状态主要有三类

   * 发送成功（所有对端收到）
   * 发送失败（所有对端未收到）
   * 部分失败（部分对端收到）

     发送失败的情况下需要获取失败原因比如以太网的链路故障
3. 只针对Reliability属性的，不关心best effort的
4. 受限于DDS的history、durability等QoS，若发送的数据过多，则hisrotyCache中的数据样本被删除，通过writesn查询样本的状态返回值为*TRANS_CODE_NO_STATUS_CC_DELETED*

**样例代码：**

```C
Rte_Dds_ReturnType ret;
Rte_Dds_TopicData data;
TransferStatus status;
struct sequence_number writesn;

HelloWorld sample;
HelloWorld_init(&sample);
Rte_Dds_TopicId topic_w = DEF_RTE_DDS_TOPIC("topicA",{0});
Rte_Dds_PackData(&data, &sample);
Rte_Dds_Writer w = Rte_Dds_GetWriter(topic_w.name);

// 发送数据样本，获取sn号
ret = Rte_Dds_TxData(w, &data, &writesn);
if (ret != RTE_DDS_RETCODE_OK) {
    pr_err("tx data failed!\n");
    return ret;
}
// 通过sn号查询状态信息，存储在参数status中
ret = Rte_Dds_Get_Sample_TxStatus(w, writesn, &status);
if (ret != RTE_DDS_RETCODE_OK) {
    pr_err("Rte_Dds_Get_Sample_TxStatus failed!\n");
    return ret;
} else if (status == TRANS_CODE_ALL_SUCCESS) {
    pr_info("status = %d means TRANS_CODE_ALL_SUCCESS", TRANS_CODE_ALL_SUCCESS);
} else {
    pr_warn("status = %d", status);
}
```

### Rte_Dds_Reader_OnMatch

**接口原型：**

```C
typedef struct reader_matched_status            Rte_Dds_Reader_MatchStatus

void Rte_Dds_Reader_OnMatch(Rte_Dds_Reader r, const Rte_Dds_Reader_MatchStatus *status);
```

**功能描述：**

提供DDS reader match/unmatch事件通知

**入参：**

  `Rte_Dds_Reader r` ：对应topic的Reader

  `Rte_Dds_Reader_MatchStatus *status`：保存reader匹配相关的状态信息

```C
struct reader_matched_status {
    uint16_t total_count;            // 所有匹配过的writer数量
    uint16_t total_count_change;     // 上一次listener被调用后total_count的变化
    uint16_t current_count;          // 当前匹配的writer数量
    int16_t current_count_change;    // 上一次listener被调用后current_count的变化
    struct guid last_publication_handle;//导致状态更改的最后一个writer的guid
};

typedef struct reader_matched_status            Rte_Dds_Reader_MatchStatus
```

**注意事项：**

1. 若 `status->current_count_change > 0`，则reader处于match阶段，此时current_count_change表示匹配的writer的个数
2. 若 `status->current_count_change < 0`，则reader处于unmatch阶段，此时current_count_change为负数，其绝对值表示离线的writer的个数
3. 应用通过强符号定制该接口，便于用户在match和unmatch阶段进行相应的数据处理

 **样例代码** ：

```C
// 用户重写
void Rte_Dds_Reader_OnMatch(
     Rte_Dds_Reader r,
     const Rte_Dds_Reader_MatchStatus *status)
{
    const char * topic_name = Rte_Dds_Reader_Get_TopicName(r);
    if(strcmp(topic_name,"xxx")){
        // show status
       pr_info("reader(%s) %s! current count:%d, change count:%d\n",
       topic_name, status->current_count_change > 0 ? "match" : "unmatch",
       status->current_count, status->current_count_change);

       if(status->current_count_change > 0){
           // match: do something
       }else{
           // unmatch:do something
       }
    }
    else if(strcmp(topic_name,"yyy")){
       pr_info("reader(%s) %s! current count:%d, change count:%d\n",
       topic_name, status->current_count_change > 0 ? "match" : "unmatch",
       status->current_count, status->current_count_change);
    }
}
```

### Rte_Dds_Writer_OnMatch

**接口原型：**

```C
typedef struct writer_matched_status            Rte_Dds_Writer_MatchStatus

void Rte_Dds_Writer_OnMatch(Rte_Dds_Writer w, const Rte_Dds_Writer_MatchStatus *status);
```

**功能描述：**

提供DDS writer match/unmatch事件通知

**入参：**

  `Rte_Dds_Writer w`：对应topic的writer

  `Rte_Dds_Writer_MatchStatus *status`：保存writer匹配相关的状态信息

```C
struct writer_matched_status {
    uint16_t total_count;            // 所有匹配过的reader数量
    uint16_t total_count_change;     // 上一次listener被调用后total_count的变化
    uint16_t current_count;          // 当前匹配的reader数量
    int16_t current_count_change;    // 上一次listener被调用后current_count的变化
    struct guid last_subscription_handle;//导致状态更改的最后一个reader的guid
};

typedef struct writer_matched_status            Rte_Dds_Writer_MatchStatus
```

**注意事项：**

1. 若 `status->current_count_change > 0`，则writer处于match阶段，此时current_count_change表示匹配的reader的个数
2. 若 `status->current_count_change < 0`，则writer处于unmatch阶段，此时current_count_change为负数，其绝对值表示离线的reader的个数
3. 应用通过强符号定制该接口，便于用户在match和unmatch阶段进行相应的数据处理

 **样例代码** ：

```C
// 用户重写
void Rte_Dds_Writer_OnMatch(
    Rte_Dds_Writer w,
    const Rte_Dds_Writer_MatchStatus *status)
{
    const char * topic_name = Rte_Dds_Writer_Get_TopicName(w);
    if(strcmp(topic_name,"xxx")){
       // show status
       pr_info("writer(%s) %s! current count:%d, change count:%d\n",
       topic_name, status->current_count_change > 0 ? "match" : "unmatch",
       status->current_count, status->current_count_change);

       if(status->current_count_change > 0){
           // match: do something
       }else{
           // unmatch:do something
       }
    }else if(strcmp(topic_name,"yyy")){
       pr_info("writer(%s) %s! current count:%d, change count:%d\n",
       topic_name, status->current_count_change > 0 ? "match" : "unmatch",
       status->current_count, status->current_count_change);
    }
}
```

### Rte_Dds_Reader_Get_TopicName

**接口原型：**

```C
const char *Rte_Dds_Reader_Get_TopicName(Rte_Dds_Reader r);
```

**功能描述：**

返回Reader的TopicName

**入参：**

  `Rte_Dds_Reader r`：reader对象

**出参：**

无

**返回值：**

  指向TopicName的指针

**用例：**

```C
Rte_Dds_Reader r;
const char *ptr = Rte_Dds_Reader_Get_TopicName(r);
printf("topic_name: %s\n", ptr);
```

### Rte_Dds_Reader_Set_Private

**接口原型：**

```C
Rte_Dds_ReturnType  Rte_Dds_Reader_Set_Private(Rte_Dds_Reader r，void *private);
```

**功能描述：**

设置Reader的成员变量private

**入参：**

  `Rte_Dds_Reader r`：reader对象

  `void *private`：用户传给reader的私有数据

**出参：**

无

**返回值：**

  返回值类型为Rte_Dds_ReturnType

* RTE_DDS_RETCODE_OK：设置成功
* RTE_DDS_RETCODE_BAD_PARAMETER：参数错误
* RTE_DDS_RETCODE_ERROR：设置失败

**用例：**

```C

DataType data;
Rte_Dds_ReturnType  ret = RTE_DDS_RETCODE_OK;
Rte_Dds_Reader r = Rte_Dds_GetReader("TopicA");
void     *private = &data;

ret = Rte_Dds_Reader_Set_Private(r， private);
if(ret != RTE_DDS_RETCODE_OK){
    pr_err("set private error");
}

```

### Rte_Dds_Reader_Get_Private

**接口原型：**

```C
void*  Rte_Dds_Reader_Get_Private(Rte_Dds_Reader r);
```

**功能描述：**

获取Reader的成员变量private

**入参：**

  `Rte_Dds_Reader r`：reader对象

**返回值：**

  void *： reader对象的私有数据private，失败返回NULL

**用例：**

```C
struct subscription_list {
    const char         *topic_name;
    Rte_Dds_TopicData   sample;
    Rte_Dds_Reader      r;
};

DataType1       sample1;
DataType2       sample2;
DataType3       sample3;
DataType4       sample4;

#define        ARRAY_SIZE(arr)                (sizeof(arr) / sizeof((arr)[0]))

struct subscription_list table[] {
    {
        .topic_name  = "Topic_1",
        .sample = {
            .data    = &sample1,
        },
    }, {
        .topic_name  = "Topic_2",
        .sample = {
            .data    = &sample2,
        },
    }, {
        .topic_name  = "Topic_3",
        .sample = {
            .data    = &sample4,
        },
    }, {
        .topic_name  = "Topic_4",
        .sample = {
            .data    = &sample4,
        },
    }
};

void init(void)
{
    int i;

    for (i=0; i<ARRAY_SIZE(table); i++) {
        table[i].r = Rte_Dds_GetReader(table[i].topic_name);
        Rte_Dds_Reader_Set_Private(table[i].r, &table[i].sample);
    }
}

// 用户重写了回调函数
Rte_Dds_RxIndication(Rte_Dds_Reader r, Rte_Dds_Instance inst)
{
    /*
     * 这里不再需要Rte_Dds_Reader_Get_TopicName获取topic name，再根据topic name找到其数据
     * 容器的位置信息
     */
    Rte_Dds_TopicData *sample;

    sample = Rte_Dds_Reader_Get_Private(r);

    Rte_Dds_RxData(r, true, sample, NULL);

    /*
     * Private 指针不仅仅可以存放数据容器，甚至存放函数指针也是可以的。比如每个topic都有一个
     * 处理方法：
     * struct info {
     *       Rte_Dds_TopicData *sample
     *       void *cb(Rte_Dds_Reader r, Rte_Dds_TopicData *sample)
     * };
     * info = Rte_Dds_Reader_Get_Private(r);
     * Rte_Dds_RxData(r, true, info.sample, NULL)
     * info.cb(r, info.sample)；
     *
     * private 提供了基于Rte_Dds_Reader和Rte_Dds_Writer扩展的可能性
     */
}
```

### Rte_Dds_Writer_Get_TopicName

**接口原型：**

```C
const char *Rte_Dds_Writer_Get_TopicName(Rte_Dds_Writer w);
```

**功能描述：**

返回Writer的TopicName

**入参：**

  `Rte_Dds_Writer w`：writer对象

**出参：**

无

**返回值：**

`const char *`：writer的TopicName

**用例：**

```C
Rte_Dds_Writer w;
const char *ptr = Rte_Dds_Writer_Get_TopicName(w);
printf("topic_name: %s\n",ptr);
```

### Rte_Dds_Writer_Set_Private

**接口原型：**

```C
Rte_Dds_ReturnType  Rte_Dds_Writer_Set_Private(Rte_Dds_Writer w，void *private);
```

**功能描述：**

设置Writer的成员变量private

**入参：**

  `Rte_Dds_Writer w`：writer对象

  `void *private`：用户传给writer的私有数据

**出参：**

无

**返回值：**

  返回值类型为Rte_Dds_ReturnType

* RTE_DDS_RETCODE_OK：设置成功
* RTE_DDS_RETCODE_BAD_PARAMETER：参数错误
* RTE_DDS_RETCODE_ERROR：设置失败

### Rte_Dds_Writer_Get_Private

**接口原型：**

```C
void*  Rte_Dds_Writer_Get_Private(Rte_Dds_Writer w);
```

**功能描述：**

获取Writer的成员变量private

**入参：**

  `Rte_Dds_Writer w`：writer对象

**返回值：**

  `void *`：writer的私有数据成员private，失败返回NULL

**用例：**

```C

// 用户重写了回调函数
void Rte_Dds_Writer_OnMatch(Rte_Dds_Writer w,
    const struct publication_matched_status *status)
{
    void *ptr = Rte_Dds_Writer_Get_Private(w);
}

```

### Rte_Dds_Ptcp_Recv_Handler

  **接口原型**

```C
Rte_Dds_ReturnType Rte_Dds_Ptcp_Recv_Handler(Rte_Dds_Participant ptcp, uint32_t recv_max_pkg);
```

  **功能描述：**

  participant接收数据的接口，每次调用后从ringbuffer获取recv_max_pkg个数据包，并放入每个reader的history

  **入参：**

  `Rte_Dds_Participant ptcp`：participant对象

  `uint32_t recv_max_pkg`：每次接收的最大收包数量

  **返回值：**

* RTE_DDS_RETCODE_BAD_PARAMETER：参数错误
* RTE_DDS_RETCODE_OK：成功

### Rte_Dds_Ptcp_Timer_Handler

  **接口原型**

```C
Rte_Dds_ReturnType Rte_Dds_Ptcp_Timer_Handler(Rte_Dds_Participant ptcp);
```

  **功能描述：**

  执行participant定时任务的接口，每次调用后会执行participant内注册的定时任务

  **入参：**

  `Rte_Dds_Participant ptcp`：participant对象

  **返回值** ：

* RTE_DDS_RETCODE_BAD_PARAMETER：参数错误
* RTE_DDS_RETCODE_OK：成功
