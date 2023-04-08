/**
  @author      : aero (2254228017@qq.com)
  @file        : test_tcpserver
  @created     : 星期二 3月 28, 2023 21:05:51 CST
  @github      : https://github.com/denstiny
  @blog        : https://denstiny.github.io
*/

#include <iostream>
#include "tasks/tasks.hpp"
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
#include <gtest/gtest.h>
using namespace std;
const char buf[] = "hello world\n\0";
const char ip[] = "127.0.0.1";
const int port = 6667;

class Tst_Tcp: public testing::Test
{

};
void test_server() {
  this_thread::sleep_for (std::chrono::milliseconds (200));
  struct sockaddr_in address;
  bzero (&address, sizeof (address));
  address.sin_port = htons (port);
  inet_pton (AF_INET, ip, &address.sin_addr.s_addr);
  int sock_fd = socket (AF_INET, SOCK_STREAM, 0);
  address.sin_family = AF_INET;
  int ret = connect (sock_fd, (sockaddr*)&address, sizeof (address));
  if (ret == 0) {
    send (sock_fd, buf, strlen (buf) + 1, 0);
    close (sock_fd);
  }
}

TEST_F(Tst_Tcp, TcpTest)
{
  ThreadPool pool;
  pool.Init (10);
  for (int i = 0; i < 1000; i++) {
    pool.Submit (test_server);
  }
}
