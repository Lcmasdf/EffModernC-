#include <iostream>
#include <thread>
#include <future>
#include <condition_variable>
#include <mutex>
#include <chrono>
#include <memory>

std::mutex mtx;
std::condition_variable cv;
int x;

void loop_output(int n, int m);

void test_loop_output() {
    x = 100;
    auto t1 = std::make_unique<std::thread>(loop_output, 0, 3);
    auto t2 = std::make_unique<std::thread>(loop_output, 1, 3);
    auto t3 = std::make_unique<std::thread>(loop_output, 2, 3);

    x = 1;
    cv.notify_all();
    t1->join();
    t2->join();
    t3->join();
}

void loop_output(int n, int m) {
    while(true) {
        std::unique_lock<std::mutex> lk(mtx);
        cv.wait(lk, [&]() {
            return x == n;
        });
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << n << std::endl;
        x = (n+1)%m;
        cv.notify_all();
    }
}


