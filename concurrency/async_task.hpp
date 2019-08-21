/*#include <thread>
#include <iostream>
#include <future>
#include <windows.h>
int sleep_and_add(int n) {
    int ret = 0;
    for (int i = 0 ; i < n; i++) {
        Sleep(i);
        ret += i;
    }
    return ret;
}

void test() {
    auto func1 = std::async(std::launch::async, sleep_and_add, 3);
    auto func2 = std::async(std::launch::async, sleep_and_add, 3);

    Sleep(2);
    func1.get();
    func2.get();
    return ;
}*/