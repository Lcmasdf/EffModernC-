#include <iostream>
#include <mutex>

void print_msg() {
    std::cout << "xxxx" << std::endl;
}

void call_once() {
    std::once_flag flg;
    std::call_once(flg, print_msg);
    std::call_once(flg, print_msg);
    std::call_once(flg, print_msg);
}