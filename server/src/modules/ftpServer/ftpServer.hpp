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
#include "colorcout/colorcout.hpp"
#include <database/database.hpp>
#include <user/user.hpp>
#include <unordered_map>

class FtpServer {
    // TODO: 完善ftp server 服务器
  public:
    void Init (const char* ip, const int port);
    void EventWith (int epoll_fd, int number, int listen_fd, epoll_event* event);
  private:
    char* ip;
    int port;
};
