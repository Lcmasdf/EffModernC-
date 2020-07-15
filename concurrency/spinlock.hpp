#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>

class spinlock {
    private:
    std::atomic_flag f;
    public:
    spinlock():f(ATOMIC_FLAG_INIT) {}

    void lock() {
        while(f.test_and_set());
    }

    void unlock() {
        f.clear();
    }
};

void test_spinlock() {
    spinlock slk;

    auto f1 = [&]() {
        slk.lock();
        slk.lock();

        std::cout << "slk lock twice" << std::endl;
    };

    auto f2 = [&]() {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "slk unlock" << std::endl;
        slk.unlock();
    };

    std::thread t1(f1);
    std::thread t2(f2);
    t1.join();
    t2.join();
}