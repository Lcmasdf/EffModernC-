#include <future>
#include <thread>
#include <chrono>
#include <iostream>

template<class T>
// 万能引用的推导
void future_get(T&& f) {
    std::cout << f.get() << std::endl;
}

void future_from_async() {
    auto f1 = std::async(std::launch::deferred, []() {
        std::cout << "doning async" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(10));
        return -100;
    });

    std::cout << "sleep 2s before future get" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::cout << "now get: " << std::endl; 
    future_get(std::move(f1));
}

int slow_add(int a, int b) {
    std::cout << "sleep 2s before add" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return a+b;
}

void future_from_packaged_task() {
    std::packaged_task<int(int,int)> p(slow_add);
    auto f1 = p.get_future();
    std::async(std::launch::async, std::move(p), 1, 2);
    std::cout << f1.get() << std::endl;
}

void future_from_promise() {
    std::promise<int> p;
    auto f = p.get_future();
    p.set_value(123);
    std::cout << f.get() << std::endl;
}