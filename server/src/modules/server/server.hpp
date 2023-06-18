#pragma once
#include <iostream>
#include <sys/epoll.h>
#include <vector>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
#include <netinet/in.h>
#include <fcntl.h>
#include <cstdio>
#include <map>
#include <tasks/tasks.hpp>
#include "Message/MessageProcessor.hpp"
#include <user/user.hpp>
#include <unordered_map>
#include <database/database.hpp>
#include "colorcout/colorcout.hpp"
#include "./response.hpp"
#include "B-tree/btree.h"
#include <B-tree/btree_map.h>

#define MAX_EVENTS_NUMBER 1024
using nl_json = nlohmann::json;

class Server {
  public:
    Server (ThreadPool* pool): pool (pool) {
      ReConf conf (CONFIGPATH);
      dataSchema.Connect (conf);
    };
    ~Server() {};
    int Init (const char* ip, const int port);
    void EventWith (int epoll_fd, int number, int  listen_fd, epoll_event* event);
  private:
    std::string ResultMessageString (int socket);
    void SmallMessageProcess (std::string response, int sock);
    // Processing login response
    std::string ResultLoginString (const nl_json body, int socket);
    // Processing registration response
    std::string ResultRegisteredString (const nl_json body);
    // Processing text response
    std::string ResultTextString (const nl_json body, int& client_sock);
    // 用户添加好友
    std::string ResultAddFrendString (const nl_json body);
  private:
    //std::unordered_map<std::string, User> user_map; // 用户列表
    char* ip;               // ip地址
    int port;               // 端口
    struct sockaddr_in server_addr; // server socket 结构体
    std::map<std::string, User> userMap;
    ThreadPool* pool;
    DataSchema dataSchema;
    //btree::btree_map<std::string, User>
    //userMap; // 储存新的客户端id和套接字映射
};

int setnoblocking (int fd);
void add_fd (int epoll_fd, int sock_fd);
