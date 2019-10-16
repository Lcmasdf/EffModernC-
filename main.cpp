#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
#include "auto_ptr/ptr&tree.hpp"
// #include <limits>
// #include <cstdio>
// #include <vector>
// #include <memory>
// #include <string.h>
// #include <iomanip>
// #include "move/class.hpp"
// #include <memory>
// #include "concurrency/async_task.hpp"
// #include "EffModernCpp/ModernC++.h"
// #include "concurrency/thread.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    link_list l;
    l.insert_tail(1);
    l.insert_tail(2);
    l.insert_tail(3);
    l.insert_tail(4);
    l.delete_first(2);
    return 0;
}
