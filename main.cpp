#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
// #include "std_IO/exec.h"
// #include "move/class.hpp"
#include <string>

// #include "file_system/list.h"
// #include "auto_ptr/ptr&tree.hpp"
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
// #include "concurrency/atomic.hpp"
#include "other_test/kestrel_frame_copy/frame.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    object o1(1);
    object o2 = create_object();
    cout << o2.get_num() << endl;
    object o3 = o2;
    return 0;
}