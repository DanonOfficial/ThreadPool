//
// Created by danonofficial on 10.09.17.
//

#ifndef THREADS_THREADPOOL_H
#define THREADS_THREADPOOL_H


#include <functional>
#include <atomic>
#include <queue>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>

class ThreadPool {
public:
    explicit ThreadPool(size_t);

    ~ThreadPool();

    void execute(std::function<void()> const &func);

private:
    std::atomic_bool end;
    std::vector<std::thread> threads;
    std::condition_variable isPosible;
    std::queue<std::function<void()>> work;
    std::mutex qMutex;
};


#endif //THREADS_THREADPOOL_H
