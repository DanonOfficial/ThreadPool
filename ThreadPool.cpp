#include "ThreadPool.h"
#include <iostream>
#include <thread>
#include <future>

ThreadPool::ThreadPool(size_t size) : end(false) {
    for (int i = 0; i < size; i++) {
        threads.emplace_back(
                [this, i] {
                    while (true) {

                        std::unique_lock<std::mutex> lock(this->qMutex);
                        this->isPosible.wait(lock,
                                             [this] { 
                                                 return (this->end) || !this->work.empty(); 
                                             });
                        if (this->end && this->work.empty()) {
                            return;
                        }
                        std::function<void()> work;
                        work = std::move(this->work.front());
                        this->work.pop();
                        lock.unlock();
                        work();
                    }
                }
        );
    }
}

void ThreadPool::execute(std::function<void()> const &func) {
    std::unique_lock<std::mutex> lock(this->qMutex);
    this->work.push(func);
    this->isPosible.notify_one();
}

ThreadPool::~ThreadPool() {
    end = true;
    isPosible.notify_all();
    for (auto &x: threads) {
        x.join();
    }
}
