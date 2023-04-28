#pragma once

class CallServer {
  public:
    void Init (const char* ip, const int port);
    void WaitEventFun (int listen_fd, int epool_fd);
  private:
    int port;
    char* prot;
};
