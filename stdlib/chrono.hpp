#include <iomanip>
#include <chrono>
#include <iostream>
#include <ctime>
#include <thread>

using namespace std::chrono;

void disp_currnt_time() {
    auto current = std::chrono::system_clock::now();

    std::cout << current.time_since_epoch().count() << std::endl;

    std::cout << std::chrono::system_clock::to_time_t(current) << std::endl;

    auto tmp = std::chrono::system_clock::to_time_t(current);

    std::cout << std::localtime(&tmp) << std::endl;

    //g++4.9 still don't support std::put_time
    //std::cout << std::put_time(std::localtime(&tmp),"") << std::endl;;

    auto end = std::chrono::system_clock::now();

    std::cout << "nanosecond cost : " << (end - current).count() << std::endl;
    std::cout << "microseconds cost : " << std::chrono::duration_cast<std::chrono::microseconds>(end-current).count() << std::endl;
}

void disp_timespan() {
    auto begin = steady_clock::now();

    std::this_thread::sleep_for(seconds(2));
}