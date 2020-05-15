#include "concurrency_test.h"

#include <thread>
#include <iostream>
#include <exception>
#include <chrono>

#include "hierarchical_mutex.hpp"

using namespace std;


void TestConcurrency() {
    hierarchical_mutex m1(200), m2(300), m3(400), m4(500);

    try {
        m1.lock();
        hierarchical_mutex::show_hierarchy_level();
        m2.lock();
        hierarchical_mutex::show_hierarchy_level();
    } catch (std::exception& e) {
        cout << e.what() << endl;
    }
    m1.unlock();
    m2.unlock();
    hierarchical_mutex::show_hierarchy_level();

    auto t1 = [&]() {
        cout << "t1 - " << endl;
        hierarchical_mutex::show_hierarchy_level();
        m2.lock();
        cout << "t1 m2 lock" << endl;
        this_thread::sleep_for(chrono::seconds(1));
        m4.lock();
        cout << "t1 m4 lock" << endl;
        this_thread::sleep_for(chrono::seconds(1));
        m4.unlock();
        cout << "t1 m4 unlock" << endl;
        this_thread::sleep_for(chrono::seconds(1));
        m2.unlock();
        cout << "t1 m2 unlock" << endl;
    };

    auto t2 = [&]() {
        cout << "t2 - " << endl;
        hierarchical_mutex::show_hierarchy_level();
        m2.lock();
        cout << "t2 m2 lock" << endl;
        this_thread::sleep_for(chrono::seconds(1));
        m3.lock();
        cout << "t2 m3 lock" << endl;
        this_thread::sleep_for(chrono::seconds(1));
        m3.unlock();
        cout << "t2 m3 unlock" << endl;
        this_thread::sleep_for(chrono::seconds(1));
        m2.unlock();
        cout << "t2 m2 unlock" << endl;
    };

    thread th1 (t1);
    thread th2 (t2);
    th1.join();
    th2.join();
}