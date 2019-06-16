#ifndef MOVE_CLASS_H
#define MOVE_CLASS_H

#include <iostream>
#include <memory>
#include <string>
#include <cstring>
#include <type_traits>

class move_z {
    private:
    char* pdata;
    size_t length;
    size_t capacity;

    public:
    move_z() {
        std::cout << "move_z default construction" << std::endl;
        pdata = new char[100];
        memset(pdata, 0, 100);
        memcpy(pdata, "move_z construction", strlen("move_z construction"));
        length = strlen("move_z construction");
        capacity = 100;
    }

    ~move_z() {
        if (nullptr != pdata) {
            delete[] pdata;
        }
    }

    move_z(const move_z& src) {
        std::cout << "move_z default construction" << std::endl;
        pdata = new char[src.capacity];
        capacity = src.capacity;
        length = src.length;    
    }

    move_z (const char* src) {
        std::cout << "move_z construction with a param" << std::endl;
        pdata = new char[strlen(src)];
        memcpy(pdata, src, strlen(src));
        capacity = strlen(src);
        length = capacity;
    }

    move_z get_move_z() { //这里会有RVO的优化
        move_z ttt;
        return ttt;
    }

    move_z* get_move_z_ptr() {
        move_z* pz = new move_z();
        return pz;
    }

    void disp() {
        std::cout << pdata << std::endl;
    }

    void simulate_move(move_z& xx) {
        std::cout << "move_z simulate_move use reference" << std::endl;
        if (pdata != nullptr) {
            delete[] pdata;
        }
        pdata = xx.pdata;
        length = xx.length;
        capacity = xx.capacity;
        xx.pdata = nullptr;
    }

    void simulate_move(move_z* xx) {
        std::cout << "move_z simulate_move use pointer" << std::endl;
        if (pdata != nullptr) {
            delete[] pdata;
        }
        pdata = xx->pdata;
        length = xx->length;
        capacity = xx->capacity;
        memcpy(pdata, xx->pdata, capacity);
    }

    // void simulate_move(const move_z& xx) {
    //     std::cout << "move_z simulate_move use const reference" << std::endl;
    //     xx.disp();
    // }
};

class move_A {
    private:
    char* pdata;
    size_t length;

    public:
    move_A() {
        std::cout << "default construction" << std::endl;
        pdata = new char[11];
        memset(pdata, 0, 11);
        memcpy(pdata, "lichengmin", 10);
        length = 11;
    }
    ~move_A() {
        std::cout << "default destruction" << std::endl;
        if (nullptr != pdata) {
            delete[] pdata;
        }
    }
    move_A(const char* str) {
        std::cout << "construction with const char*" << std::endl;
    }
    move_A (const move_A& rhs) {
        std::cout << "copy construction" << std::endl;
        pdata = new char[rhs.length];
        memcpy(pdata, rhs.pdata, rhs.length);
        length = rhs.length;
    }
    move_A (move_A&& rhs) {
        std::cout << "move construction" << std::endl;
        pdata = rhs.pdata;
        length = rhs.length;
        rhs.pdata = nullptr;
        rhs.length = 0;
    }

    move_A& operator= (const move_A& rhs) {
        if (nullptr != pdata) {
            delete[] pdata;
        }
        pdata = new char[rhs.length];
        length = rhs.length;
        memcpy(pdata, rhs.pdata, rhs.length);

        return *this;
    }

    move_A& operator= (move_A&& rhs) {
        if (nullptr != pdata) {
            delete[] pdata;
        }

        pdata = rhs.pdata;
        rhs.pdata = nullptr;
        rhs.length = 0;
    }

    void display() {
        std::cout << pdata << std::endl;
    }

};

void test();

//std::move的实现

template<typename T>
typename remove_reference<T>::type&&
my_move (T&& param) {
    using ReturnType = typename remove_reference<T>::type&&;

    return static_cast<ReturnType>(param);
}

#endif