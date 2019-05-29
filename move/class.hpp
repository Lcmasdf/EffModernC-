#ifndef MOVE_CLASS_H
#define MOVE_CLASS_H

#include <iostream>
#include <memory>
#include <string>
#include <cstring>

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

#endif