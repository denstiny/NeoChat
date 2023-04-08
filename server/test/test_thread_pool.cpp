
#include "tasks/tasks.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <thread>
void echo_id (const int a) {
  //std::this_thread::sleep_for (std::chrono::milliseconds (20));
}
class Tst_ThreadPool: public testing::Test
{

};
class TestFun {
  public:
    void test() {
      std::cout << "fun in class testFUn" << std::endl;
    }
};

TEST_F(Tst_ThreadPool, ThreadPoolTest) {
  ThreadPool pool;
  pool.Init (5);
  for (int j = 1; j <= 200; ++j) {
    pool.Submit (echo_id, j);
  }
  pool.shutdown();
}
