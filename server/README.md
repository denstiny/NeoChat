# Cpp 聊天程序服务器

## 实现任务
1. 创建一个线程池，处理客户端任务，和数据库读取(tasks)
2. 异步IO 实现高性能数据交互
4. 主线程负责客户端与客户端的数据交换
5. 用户数据保存到数据库中

## TODO
1.[x] 创建数据库
2.[x] 创建用户类
3.[x] 重新使用cmake 放弃xmake
4.[ ] 处理用户发送的信息
```cpp
class User {
  int sock_fd;
  std::string user_account;
  std::string user_password;
  std::string user_phone;
  std::map<std::string,User> user_m;
};
```
3. 数据库
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
