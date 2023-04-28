#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include <functional>
#include <future>
#include <queue>

/* 任务队列 */
template<typename T>
class TasksQueue {
  public:
#ifndef NDEBUG // debug information
    long tasks_s = 0;
#endif
    int Size(); // 获取任务的数量
    // 添加任务
    void enqueue (T& t) {
      std::unique_lock<std::mutex> lock (m_mutex);
#ifndef NDEBUG
      tasks_s ++;
#endif
      m_queue.emplace (t);
    }
    /* @brief 删除队列中的任务 */
    bool dequeue (T& t) {
      std::unique_lock<std::mutex> lock (m_mutex);
      if (m_queue.empty()) {
        return false;
      }
      t = std::move (m_queue.front());
      m_queue.pop();
      return true;
    }
    bool Empty(); // 判断任务是否为空
  private:
    std::mutex m_mutex; // 线程锁
    std::queue<T> m_queue; // 线程队列
};


/* 线程池，负责整个业务调度 */
class ThreadPool {
  public:
    ThreadPool(): max_thread (12), m_shutdown (false),
      m_threads (std::vector<std::thread> (max_thread)) {}
    ~ThreadPool();
    void Init (int);
    void Init ();
    void SetThreadMaxNum (int max_thread);
    void WaitForThread();
    void shutdown();
    
  public:
    /* 任务发布模板函数 */
    template <typename F, typename ...Args>
    auto Submit (F&& f, Args&& ...args) -> std::future<decltype (f (args...))> {
      std::function<decltype (f (args...))()> func = std::bind (
            std::forward<F> (f), std::forward<Args> (args)...);
      auto task_ptr =
        std::make_shared<std::packaged_task<decltype (f (args...))()>> (func);
      std::function<void()> warpper_func = [task_ptr]() {
        (*task_ptr)();
      };
      tasks_queue.enqueue (warpper_func);
      m_conditional_lock.notify_one();
      return task_ptr->get_future();
    }
    
  private:
    int max_thread; // 最大线程数量
    std::vector<std::thread> m_threads; // 记录所有线程id
    void _init_ (int); // 内部初始化函数
    bool m_shutdown;   //控制线程池关闭的变量
    std::condition_variable
    m_conditional_lock; // 线程环境锁，可以让线程处于休眠或者唤醒状态
    std::mutex m_conditional_mutex;
    TasksQueue<std::function<void ()>> tasks_queue; // 任务队列
    void BaseThreadTask (int id); // 负责调度任务
};
