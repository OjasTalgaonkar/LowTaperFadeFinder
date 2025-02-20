#include "../include/threadPool.hh"

#include <cstddef>
#include <cstdlib>
#include <functional>
#include <mutex>

ThreadPool::ThreadPool(size_t threadCount) {
    for (size_t i = 0; i < threadCount; ++i) {
        threads.emplace_back(&ThreadPool::workerThread, this);
    }
}

ThreadPool::~ThreadPool() {
    std::cout << "hello";
    stopPool();
}

std::atexit(stopPool);

void ThreadPool::stopPool() {
    stop = true;
    condition.notify_all();
    for (std::thread &worker : threads) {
        if (worker.joinable())
            worker.join();
    }
}

void ThreadPool::enqueue(std::function<void()> task) {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        tasks.push(std::move(task));
    }
    condition.notify_one();
}

void ThreadPool::workerThread() {
    while (true) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            condition.wait(lock, [this] { return stop || !tasks.empty(); });

            if (stop && tasks.empty())
                return;

            task = std::move(tasks.front());
            tasks.pop();
        }

        activeTasks++;  // Mark task as active
        task();
        activeTasks--;  // Mark task as done
    }
}
