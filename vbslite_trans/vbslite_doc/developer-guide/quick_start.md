# VBSLite快速开始

## 1. 代码下载

### 1.1. Linux

> 推荐开发环境：Ubuntu 20.04

#### 1.1.1. 安装git-repo工具

1. 运行以下命令安装repo工具
   ```
   sudo apt install repo
   ```
2. 运行 `repo --version`，显示版本号即安装成功

   > Ubuntu通常会自带git工具，可以用 `git --version`检查，如果未安装可以通过 `sudo apt install git`命令安装

#### 1.1.2. 下载代码

1. 生成/添加ssh密钥，请按[gitee ssh密钥添加流程](https://gitee.com/help/articles/4181#article-header0)进行
2. 配置git

   ```
   git config --global user.name "替换为您的名字"
   git config --global user.email "替换为您的邮箱"
   ```
3. 切换到您存放代码的目录下，运行如下脚本下载代码

   > 提示：这里将代码放在了vbslitespace目录下
   >

   ```
   mkdir vbslitespace
   cd vbslitespace
   rm -rf ./.repo/
   repo init -u git@gitee.com:haloos/manifests.git -b master -m vbslite.xml
   repo sync
   repo start local --all
   ```

   > 关于git repo的更多使用，可以输入 `repo -h`查看
   >

### 1.2. Windows

#### 1.2.1. 安装git-repo工具

代码下载同时依赖git和git-repo，如果没有安装git请 [下载并安装](https://gitee.com/link?target=https%3A%2F%2Fgit-scm.com%2Fdownloads%2Fwin)

git的安装流程此处略过，git-repo的安装流程如下：

1. 下载 [git-repo官方压缩包](https://gitee.com/link?target=https%3A%2F%2Fgit-repo.info%2Freleases%2Fv0.7.8%2Fgit-repo-0.7.8-Windows-64.zip)，并解压
2. 将解压后的将程序重命名为repo.exe，并拷贝到系统用户的bin路径下（如C:\Users\YourName\bin，注意该路径需要添加进环境变量）
3. 按 Win + S 搜索 “环境变量” → 选择 “编辑系统环境变量”
4. 在 “用户变量” 中找到 Path → 点击 “编辑” → “新建” → 添加上述bin路径 → 保存
5. 启动 PowerShell 并运行以下命令，如果显示版本号即安装成功
   ```
   git --version # 应输出版本信息
   repo --version  # 应输出版本信息
   ```

#### 1.2.2. 下载代码

1. 生成/添加ssh密钥，请按[gitee ssh密钥添加流程](https://gitee.com/help/articles/4181#article-header0)进行
2. 配置git

   ```
   git config --global user.name "替换为您的名字"
   git config --global user.email "替换为您的邮箱"
   ```
3. 切换到您存放代码的目录下，运行如下脚本下载代码

   > 提示：这里将代码放在了vbslitespace目录下

   ```
   mkdir vbslitespace
   cd vbslitespace
   rm -rf ./.repo/
   repo init -u git@gitee.com:haloos/manifests.git -b master -m vbslite.xml
   repo sync
   repo start local --all
   ```

   > 关于git-repo的更多使用，可以输入 `repo -h`查看

## 2. 编译依赖

### 2.1. Linux平台编译工具

根据你的linux发行版本，安装make, gcc, python, pip 等工具

```C
sudo apt install make
sudo apt install gcc
sudo apt install python3
sudo apt install python3-pip
```

### 2.2. windows平台编译工具

windows平台编译需要安装msys2，可从 https://www.msys2.org/ 下载最新版本的 msys2 安装包进行安装，需在msys2环境中进行编译

* Windows 10 版本以及以上
  ```Shell
  pacman -Syu         # 更新软件源的数据库, 遇到提示一直按 Y
  pacman -S make mingw-w64-ucrt-x86_64-make
  pacman -S mingw-w64-ucrt-x86_64-diffutils
  pacman -S which
  pacman -S git
  pacman -S openssh
  pacman -S mingw-w64-ucrt-x86_64-gcc
  pacman -S mingw-w64-ucrt-x86_64-libevent
  pacman -S mingw-w64-ucrt-x86_64-python mingw-w64-ucrt-x86_64-python-pip

  pacman -S mingw-w64-ucrt-x86_64-neovim  # 可选择安装
  pacman -S mingw-w64-ucrt-x86_64-git-repo # 可选择安装
  ```
* Windows 7 版本以及以下
  ```Shell
  pacman -Syu         # 更新软件源的数据库, 遇到提示一直按 Y
  pacman -S make mingw-w64-x86_64-make
  pacman -S mingw-w64-x86_64-diffutils
  pacman -S which
  pacman -S git
  pacman -S openssh
  pacman -S mingw-w64-x86_64-gcc
  pacman -S mingw-w64-x86_64-libevent
  pacman -S mingw-w64-x86_64-python mingw-w64-x86_64-python-pip
  ```

### 2.3 编译依赖库

本项目依赖一些关键的python库和工具，请确保在开始编译之前安装以下依赖库：

```
crcmod==1.7
pcpp==1.30
Jinja2==3.1.2
antlr4-python3-runtime==4.13.0
xmltodict==0.13.0
ply==3.11
```

进入vbslitespace目录，在build/scripts目录中有requirements.txt，请使用以下命令安装

```
pip install -r build/scripts/requirements.txt
```

## 3. 开发流程

* 定义Topic数据类型
* 编写配置文件
* 编写应用代码
* 编译并运行程序

## 4. 编写第一个应用

### 4.1. 定义Topic数据类型

编写IDL文件，定义具体topic数据类型

项目编译框架会根据用户编写的IDL文件生成对应配置文件并参与编译

详情参见  [VBSLite IDL工具配置文档](./idl_config.md)

```c++
module MVBS {
        struct HelloWorld {
                long                 id;
                string<64>           msg;
        };

        struct HelloWorld1 {
                short                short_data;
                unsigned short       ushort_data;
        };

        struct HelloWorld2 {
                float                float_data;
                double               double_data;
        };

        struct HelloWorld3 {
                HelloWorld           struct_data;
                double               double_data;
        };
}
```

### 4.2.  编写配置文件

本项目通过XML文件配置相关信息，包括IDL文件配置、网络配置、发现配置、服务质量配置及参与者配置

项目编译框架会根据用户编写的XML文件生成对应配置文件并参与编译

详情参见 [VBSLite XML工具配置文档](./xml_config.md)

* IDL文件配置

```XML
<idl>HelloWorld.idl</idl>
```

* 网络配置

```XML
<network>
    <master>
        <!-- 替换成本地ip -->
        <address>127.0.0.1</address>
        <netmask>255.255.255.0</netmask>
    </master>
</network>
```

* 发现配置

```XML
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
```

* 服务质量配置

  * reader侧

```XML
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
            <depth>5</depth>
            <max_samples>5</max_samples>
            <max_instances>1</max_instances>
            <max_samples_per_instance>5</max_samples_per_instance>
        </history>
        <e2e_policy>
            <enable>false</enable>
            <e2e_p04_min_data_length>0</e2e_p04_min_data_length>
            <e2e_p04_max_data_length>4090</e2e_p04_max_data_length>
            <e2e_p04_max_delta_counter>10</e2e_p04_max_delta_counter>
        </e2e_policy>
    </reader>
</qos>
```

* writer侧

```XML
<qos>
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
            <depth>5</depth>
            <max_samples>5</max_samples>
            <max_instances>1</max_instances>
            <max_samples_per_instance>5</max_samples_per_instance>
        </history>
        <e2e_policy>
            <enable>false</enable>
            <e2e_p04_min_data_length>0</e2e_p04_min_data_length>
            <e2e_p04_max_data_length>4090</e2e_p04_max_data_length>
            <e2e_p04_max_delta_counter>10</e2e_p04_max_delta_counter>
        </e2e_policy>
    </writer>
</qos>
```

* 参与者配置
* reader侧

```xml
<participant>
    <name>app2</name>
    <domain_id>0</domain_id>
    <discovery>DPDE</discovery>
    <max_remote_participants>20</max_remote_participants>
    <reader>
        <key>r0</key>
        <topic>domain_0_topic_0Topic</topic>
        <type>MVBS::HelloWorld</type>
        <qos>reader0_qos</qos>
        <object_id>150</object_id>
        <max_remote_peers>5</max_remote_peers>
    </reader>
</participant>
```

* writer侧

```xml
<participant>
    <name>app1</name>
    <domain_id>0</domain_id>
    <discovery>DPDE</discovery>
    <max_remote_participants>20</max_remote_participants>
    <writer>
        <key>w0</key>
        <topic>domain_0_topic_0Topic</topic>
        <type>MVBS::HelloWorld</type>
        <qos>writer0_qos</qos>
        <object_id>100</object_id>
        <max_remote_peers>5</max_remote_peers>
    </writer>
</participant>
```

### 4.3. 编写应用代码

> 详情参见  [实例教程](./examples.md)   与  [VBSLite接口文档](./vbslite_api.md)

App 主要需要实现两个接口：

* app_init：用户实现的初始化函数
* app_loop：用户实现的周期任务函数

```C
static int app_loop(unsigned long timer_ms)
{
    /* 执行周期任务，如发送数据、接收数据 */
}

static Rte_Dds_Participant app_init(int argc, char *argv[])
{
    /* 调用相应API，获取配置信息、进行初始化等 */
    Rte_Dds_Participant ptcp = Rte_Dds_GetParticipant();
    Rte_Dds_Init(ptcp); //协议栈初始化
    XXX_init(); //XXX为对应的topic名字，该函数由IDL工具自动生成，为topic赋初始值
}
```

### 4.4. 编译并运行程序

* 选择编译平台

```Bash
$ source build/envsetup.sh
$ lunch xxx
# 根据不同平台选择编译选项，比如linux
```

* 编译程序

```Bash
$ mma -j8   # 全量编译
$ mm -j8   # 增量编译
$ make your_program # 单独编译特定的程序
```

* 运行程序

```Bash
$ ./yout_program # 你的程序名称
```
