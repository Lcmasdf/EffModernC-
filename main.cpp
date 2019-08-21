// #include <iostream>
// #include <limits>
// #include <cstdio>
// #include <chrono>
// #include <vector>
// #include <memory>
// #include <string.h>
// #include <iomanip>
#include "move/class.hpp"
#include <memory>
#include "concurrency/async_task.hpp"

// #include "EffModernCpp/ModernC++.h"

// int func () {
//     throw("throw a const char* error");
// }

// #include "stdlib/chrono.hpp"
// #include "coroutine/vczh.hpp"
// #include "other_test/pointer_in_member_func.hpp"

class Empty {

};

class E2 {
    Empty e1;
    int b;
    Empty e2[2];
};

int main(int argc, char* argv[]) {
    //disp_currnt_time();
    // test_continuation();
    // test_pointer_in_member_func();
    // int b = 100;
    // non_template_forward(std::move(b));
    // std::shared_ptr<bool> xxx;
    // test();
    std::cout << sizeof(E2) << std::endl;
    E2 e2;
    std::cout << sizeof(e2) << std::endl;

    return 0;
}
