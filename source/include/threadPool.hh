#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <atomic>
#include <condition_variable>
#include <cstddef>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>


class ThreadPool {
  public:
    ThreadPool(size_t threadCount);
    ~ThreadPool();
    void             enqueue(std::function<void()> task);
    void             workerThread();
    void             stopPool();
    std::atomic<int> activeTasks{0};

  private:
    std::vector<std::thread>          threads;
    std::queue<std::function<void()>> tasks;
    std::mutex                        queueMutex;
    std::condition_variable           condition;
    bool                              stop;
};

#endif