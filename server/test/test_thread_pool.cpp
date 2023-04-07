#include <iostream>
#include <thread>
#include "tasks/tasks.hpp"

void echo_id (const int a) {
  //std::this_thread::sleep_for (std::chrono::milliseconds (20));
}

class TestFun {
  public:
    void test() {
      std::cout << "fun in class testFUn" << std::endl;
    }
};

int main (int argc, char* argv[]) {
  ThreadPool pool;
  pool.Init (5);
  for (int j = 1; j <= 200; ++j) {
    pool.Submit (echo_id, j);
  }
  pool.shutdown();
  return 0;
}
