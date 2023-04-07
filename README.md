# NeoChat
## NeoChat Server 通信流程
> 启动流程
1. 打开mysql 类连接mysql,等待数据库操作(modules: database)
2. 初始化线程池，等待发布的任务去处理(modules: tasks)
3. 启动server, 使用I/O复用监听客户端的请求(modules: server)

> 基本通信流程
_消息类型 (modules: Message)_
1. 当客户端发起请求，server监听到有新的请求,将发布任务到线程池，等待线程池处理任务
线程池调用server模块接受请求 ,通过调用(modules: Message)消息解析模块，解析消息类型
```cpp
enum class MessageType {
  login, // 登陆
  registered, // 注册
  text, // 文本
  voice, // 语音
  call, // 电话
  videocall, // 视频电话
};
```

2. 处理客户端请求  
>> 当客户端发送下面的请求:
```
message_type: login
type: POST
user_account: +8611011
user_password: asdf

```
通过Message 模块解析得到这个消息类型为登陆类型  
则调用server模块的登陆处理函数(`ResultLoginString`)

3. `ResultLoginString` 函数将调用 database 模块查询请求的用户和密码,当查询失败，返回响应字符串
```
message_type: login
stat: 404

```
告诉客户端登陆失败

4. 如果登陆成功，返回相应字符串
```
message_type: login
stat: 200

```
5. 将 `消息处理函数的返回值发送给客户端` 任务发布给线程池处理

上面的处理流程同样适用于 (普通文本消息,注册消息,语音消息)，这些消息通过枚举消息类型执行相应的处理函数返回响应字符串发送给客户端

---
当用户发送一个复杂的消息, 文本消息和文件
客户端需要向文件服务器 `ftp server`,发起请求
```
task_id: 1
user_account: +86101
time: 10012312312311

0x00
```
上面的消息字段意思，task_id 任务编号,user_account 用户,time 发起的时间戳,0x00文件内容  
上传完成ftp服务器将返回响应:
```
task_id: 1
stat: 200
file: %2B86101_10012312312311_a.png 
```
然后向消息服务器发送消息
```
user_account: +86101
message_type: text
text: 你好 <file>%2B86101_10012312312311_a.png</file>
friends: +8200001
```
并返回响应给 `A` 客户端发送成功

服务器将消息转发给账号 +8200001 的`B`客户端,
```
user_account: +86101
message_type: text
text: 你好 <file>%2B86101_10012312312311_a.png</file>
```
当`B`客户端接收到这样这条数据，解析<file></file>字段，将向ftp 发起请求字段中的文件  

---
> 电话和视频视频电话  
`A` -> `B`  

`A` 客户端发起电话请求给cell server,

```
user_account: +86101
friends: +8200001
```
cell server 成功返回响应
```
stat: 200
connection_key: %2B86101_%2B8200001_192888102812
```
`A` 向消息服务器发起请求

```
user_account: +86101
message_type: call
friends: +8200001
cell_key: %2B86101_%2B8200001_192888102812
```
server: 转发给`B`
```
user_account: +86101
message_type: call
cell_key: %2B86101_%2B8200001_192888102812
```
`B` 接听或拒接,发送给服务器

```
user_account: +8200001
message_type: cell
cell_type: 404 | 200
friends: +86101
```
当用户拒接时，消息服务器的将通知cell server 关闭任务 `%2B86101_%2B8200001_192888102812`  
同时将下面的消息转发给 `A` 客户端
```
user_account: +86101
message_type: cell
cell_type: 404 | 200
friends: +8200001
```

## Client Plugin
### 还没想好这块，目前进度还没到这里,做了两种假设
1. 在客户端中维护一个小的消息服务器，每间隔一段时间向插件获取消息
```cpp
// 获取消息接口
list<Message> GetMessage() -> list<Message>
// 获取用户信息
User GetUserInfo(std::string user_account) -> User
// 获取当前的用户
std::string GetCurrentUser() -> std::string
// 查询消息记录
std::string GetOldMessage() -> std::string // 这个还没想好怎么设计
// 发送消息
void SendMessage(std::string messsage);
....
```
2. 客户端维护一个小的消息服务器，只负责接收消息,和发送消息,和上面类似，但是是插件向 消息服务器发送新的消息
```cpp
// 获取用户信息
User GetUserInfo(std::string user_account) -> User
// 查询消息记录
std::list<message> GetOldMessage(std::string grop_id,int number) -> std::string
// 发送消息
void SendMessage(std::string messsage);
```
## MYSQL: 数据存储表结构

> 用户表
```
+---------------------------+---------------------------------+------+-----+-------------------+-------------------+
| Field                     | Type                            | Null | Key | Default           | Extra             |
+---------------------------+---------------------------------+------+-----+-------------------+-------------------+
| user_account              | varchar(100)                    | NO   |     | <null>            |                   |
| user_password             | varchar(100)                    | NO   |     | <null>            |                   |
| user_name                 | varchar(100)                    | YES  |     |                   |                   |
| user_phone                | varchar(100)                    | YES  |     |                   |                   |
| sex                       | enum('male','female','neutral') | YES  |     | neutral           |                   |
| birthday                  | date                            | YES  |     | <null>            |                   |
| registration_timedatetime | datetime                        | YES  |     | CURRENT_TIMESTAMP | DEFAULT_GENERATED |
| address                   | varchar(200)                    | YES  |     |                   |                   |
+---------------------------+---------------------------------+------+-----+-------------------+-------------------+
```
> 用户关系表
```
+-----------------+--------------+------+-----+-------------------+-------------------+
| Field           | Type         | Null | Key | Default           | Extra             |
+-----------------+--------------+------+-----+-------------------+-------------------+
| user_account    | varchar(100) | NO   |     | <null>            |                   |
| friend_account  | varchar(100) | NO   |     | <null>            |                   |
| is_relationship | tinyint(1)   | YES  |     | 1                 |                   |
| bind_time       | datetime     | YES  |     | CURRENT_TIMESTAMP | DEFAULT_GENERATED |
+-----------------+--------------+------+-----+-------------------+-------------------+
```
> 组群表
```
+--------------+--------------+------+-----+-------------------+-------------------+
| Field        | Type         | Null | Key | Default           | Extra             |
+--------------+--------------+------+-----+-------------------+-------------------+
| group_id     | varchar(100) | NO   |     | <null>            |                   |
| founder      | varchar(100) | NO   |     | <null>            |                   |
| introudction | varchar(100) | YES  |     |                   |                   |
| create_time  | datetime     | YES  |     | CURRENT_TIMESTAMP | DEFAULT_GENERATED |
+--------------+--------------+------+-----+-------------------+-------------------+
```
> 组群聊天记录表
```
+-------------+--------------+------+-----+-------------------+-------------------+
| Field       | Type         | Null | Key | Default           | Extra             |
+-------------+--------------+------+-----+-------------------+-------------------+
| author      | varchar(100) | NO   |     | <null>            |                   |
| message     | varchar(200) | YES  |     | <null>            |                   |
| carrary     | text         | YES  |     | <null>            |                   |
| file        | longtext     | YES  |     | <null>            |                   |
| create_time | datetime     | YES  |     | CURRENT_TIMESTAMP | DEFAULT_GENERATED |
+-------------+--------------+------+-----+-------------------+-------------------+
```
> 组群用户表
```
+--------------+----------------------------------+------+-----+-------------------+-------------------+
| Field        | Type                             | Null | Key | Default           | Extra             |
+--------------+----------------------------------+------+-----+-------------------+-------------------+
| group_id     | varchar(100)                     | NO   |     | <null>            |                   |
| user_account | varchar(100)                     | NO   |     | <null>            |                   |
| join_tim     | datetime                         | YES  |     | CURRENT_TIMESTAMP | DEFAULT_GENERATED |
| permissions  | enum('creator','admin','member') | YES  |     | <null>            |                   |
+--------------+----------------------------------+------+-----+-------------------+-------------------+
```
> 聊天记录表
```
+-------------+--------------+------+-----+-------------------+-------------------+
| Field       | Type         | Null | Key | Default           | Extra             |
+-------------+--------------+------+-----+-------------------+-------------------+
| author      | varchar(100) | NO   |     | <null>            |                   |
| message     | varchar(200) | YES  |     | <null>            |                   |
| carrary     | text         | YES  |     | <null>            |                   |
| file        | longtext     | YES  |     | <null>            |                   |
| create_time | datetime     | YES  |     | CURRENT_TIMESTAMP | DEFAULT_GENERATED |
+-------------+--------------+------+-----+-------------------+-------------------+
```
