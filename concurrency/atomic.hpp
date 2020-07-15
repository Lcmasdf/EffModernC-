#include <iostream>
#include <atomic>
#include <thread>
#include <sstream>
#include <vector>
#include <chrono>

std::atomic_flag lock_stream = ATOMIC_FLAG_INIT;
std::stringstream stream;
std::atomic_int cnt(1);

void append(int n) {
    for (int i = 0; i < 10; i++) {
        while (lock_stream.test_and_set()){
        };
        stream << "Output from thread " << n << '\n';
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
        lock_stream.clear();
    }
}

struct Node {
    int val;
    Node* next;
};

std::atomic<Node*> list_head(nullptr);

void list_append(int val) {
    Node* node = new Node{val, nullptr};
    while (!list_head.compare_exchange_weak(node->next, node));
}

void test() {
    std::vector<std::thread> ts;
    for (int i = 0; i < 10; i++) {
        ts.emplace_back(append, i);
    }

    for (auto& x: ts) {
        x.join();
    }
    std::cout << stream.str() << std::endl;

    auto append = [](int v) {
        for (int i = 0; i < 10; i++) {
            list_append(cnt.fetch_add(1));
        }
    };

    std::vector<std::thread> td;
    for (int i = 0; i < 10; i++) {
        td.emplace_back(append, i);
    }

    for (auto& x: td) {
        x.join();
    }


    Node* it;

    while (it = list_head) {
        list_head = list_head.load()->next;
        std::cout << it->val << std::endl;
        delete it;
    }
}

void test_atomic_pointer_arithmetic() {
    class Foo{};
    Foo some_array[5];
    std::atomic<Foo*> p(some_array);
    auto p1 =(  p += 2 );
    if (p1 != &(some_array[2])) {
        std::cout << "error1" << std::endl;
    }

    auto p2 = p.fetch_add(1);
    if (p2 != p1) {
        std::cout << "error2" << std::endl;
    }
}

void test_none_atomic_add() {
    int v = 1;
    std::vector<std::thread> vts;
    for (int i = 0; i < 10; i++) {
        vts.emplace_back([&]() {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            for (int i = 0; i < 100; i++) {
                v += 1;
            }
        });
    }
    for (auto& it : vts) {
        it.join();
    }

    std::cout << v << std::endl;
}

void test_atomic_add() {
    std::atomic_int v(1);
    std::vector<std::thread> vts;
    for (int i = 0; i < 10; i++) {
        vts.emplace_back([&]() {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            for (int i = 0; i < 100; i++) {
                v += 1;
            }
        });
    }
    for (auto& it : vts) {
        it.join();
    }

    std::cout << v.load() << std::endl;
}

void test_atomic_flag() {
    //最简单的标准原子类型
    //atomic_flag 必须用ATOMIC_FLAG_INIT来初始化
    std::atomic_flag f = ATOMIC_FLAG_INIT;

    //atomic_flag只能干三件事情，destory， clear， test_and_set
    if (!f.test_and_set()) {
        std::cout << "f used to be false and set to true" << std::endl;
    }

    if (f.test_and_set()) {
        std::cout << "f used to be true and set to true" << std::endl;
    }

    f.clear();

    //atomic_flag只能干三件事情，destory， clear， test_and_set
    if (!f.test_and_set()) {
        std::cout << "f used to be false and set to true" << std::endl;
    }
}