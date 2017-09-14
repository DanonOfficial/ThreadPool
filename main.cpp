#include <iostream>
#include <thread>
#include <mutex>
#include <list>
#include <algorithm>
#include "ThreadPool.h"

int main() {
    int const n = 5;

    ThreadPool th(n);

    for (int i = 0; i < n*2; ++i) {
        th.execute([i] {
            if (i == 0) {
                std::this_thread::sleep_for(std::chrono::seconds(5));
            }

            std::cout << i << std::endl;
        });

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }


    return 0;
}