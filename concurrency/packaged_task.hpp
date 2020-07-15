#include <future>
#include <thread>
#include <chrono>
#include <iostream>
#include <exception>

int fib(int n) {
    if (n < 3) return 1;
    else return fib(n-1)+fib(n-2);
}

void test_packaged_task() {
    std::packaged_task<int(int)> p1(fib);
    auto f1 = p1.get_future();
    p1(10);
    std::cout << f1.get() << std::endl;
}