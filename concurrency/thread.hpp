#include <unistd.h>
#include <iostream>
#include <thread>

using namespace std;

namespace concurrency {
class thread_guard {
    thread & t_;
    public:
    explicit thread_guard(thread& t): t_(t){}
    ~thread_guard() {
        if (t_.joinable()) {
            t_.join();
        }
    }
};

class callable_func {
   public:
    void operator()() {
        for (int i = 0; i < 10; i++) {
            cout << i << endl;
            sleep(1);
        }
    }
};

void do_exec () {
    auto f = callable_func();
    thread t(f);

    // // C++'s most vexing parse, it's not work
    // thread tt(callable_func());
    thread tt{callable_func()};
    tt.join();
    t.join();
}

}  // namespace concurrency