#include <chrono>
#include <iostream>
#include <thread>

#define TIME_(ttt,xx) \
auto start = std::chrono::system_clock::now();\
ttt;\
auto end = std::chrono::system_clock::now();\
std::cout << xx << " cost : " << (end-start).count() << std::endl;\

int sleep() {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return 1;
}

void test_macro() {
    TIME_([](){
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }(), "sleep");
}