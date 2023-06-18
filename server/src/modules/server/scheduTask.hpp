#include <iostream>
#include <mutex>
#include <thread>

// 任务调度
class scheduTask {
  public:
    scheduTask();
    void addScheduTask (int sock);
    void getScheduTask (std::string username);
    ~scheduTask();
  private:
    std::mutex lock;
};
