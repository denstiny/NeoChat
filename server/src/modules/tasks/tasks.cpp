#include "./tasks.hpp"
#include "colorcout/colorcout.hpp"

/* ------------------------------ #Tasks_Queue# -------------------------------------- */


/**
   @brief 判断队列是否为空
   @tparam T
   @return
*/
template<typename T> bool TasksQueue<T>::Empty() {
  std::unique_lock<std::mutex> lock (m_mutex);
  return m_queue.empty();
}

/**
   @brief 获取任务队列大小

   @tparam T
   @return
*/
template<typename T> int TasksQueue<T>::Size() {
  std::unique_lock<std::mutex> lock (m_mutex);
  return m_queue.size();
}


/* ------------------------------ #Tasks# -------------------------------------- */

/**
   @brief set start create thread number
   @param max_thread
*/
void ThreadPool::SetThreadMaxNum (int max_thread) {
  this->max_thread = max_thread;
}

/**
   @brief 从任务队列中取出任务
*/
void ThreadPool::BaseThreadTask (int id) {
  bool dequeued;
  std::function<void()> func;
  std::unique_lock<std::mutex> lock (m_conditional_mutex);
  while (!m_shutdown) {
    if (tasks_queue.Empty()) {
      m_conditional_lock.wait (lock);
    }
    if (tasks_queue.dequeue (func)) {
#ifndef NDEBUG
      std::cout << YELLOW <<
                " 线程: " << id << "执行任务  任务进度["
                << tasks_queue.tasks_s -  tasks_queue.Size() << "/" << tasks_queue.tasks_s <<
                "]"
                << RESET
                << std::endl;
#endif
      lock.unlock();
      func();
      lock.lock();
    }
  }
}

/**
   @brief close thread pool, shutdown all thread
*/
ThreadPool::~ThreadPool() {
}

void ThreadPool::_init_ (int max_thread_num) {
  for (int i = 0; i < max_thread_num; i++) {
    m_threads.at (i) = std::thread (std::bind (
                                      &ThreadPool::BaseThreadTask, this, i));
  }
  std::cout << GREEN << "成功启动: " << max_thread_num << "个线程" << RESET
            <<
            std::endl;
}

/**
   @brief 初始化线程池
   @param max_thread_num
*/
void ThreadPool::Init (int max_thread_num) {
  max_thread = max_thread_num;
  _init_ (max_thread_num);
}
void ThreadPool::Init() {
  _init_ (max_thread);
}

/**
   @brief All threads waiting for the exit
*/
void ThreadPool::WaitForThread() {
  while (!tasks_queue.Empty());
}

/**
   @brief stop thread pool
*/
void ThreadPool::shutdown() {
  WaitForThread();
  m_shutdown = true;
  m_conditional_lock.notify_all();
  for (int i = 0; i < m_threads.size(); ++i) {
    if (m_threads.at (i).joinable()) {
      m_threads.at (i).join();
    }
  }
};
