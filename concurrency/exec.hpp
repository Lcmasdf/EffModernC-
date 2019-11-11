#ifndef EXEC_H
#define EXEC_H
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
using namespace std;

condition_variable cv;
mutex m;
int now;

void print_thread(int x) {
    for (;;) {
        unique_lock<mutex> l(m);
        cv.wait(l, [x]() {return now == x;});
        cout << x << endl;
        now = ( now + 1 ) % 5;
        this_thread::sleep_for(chrono::seconds(1));
        cv.notify_all();
    }
}

void exec1() {
    now = 0;

    for (int i = 0; i < 5; i++) {
        thread t(print_thread, i);
        t.detach();
    }
    this_thread::sleep_for(chrono::seconds(10));
}
#endif