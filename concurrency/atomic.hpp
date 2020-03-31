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