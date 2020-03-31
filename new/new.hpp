#include <iostream>
#include <string>

class nnnnnew {
    public:
    nnnnnew() {
        std::cout << "constructor of nnnnnew" << std::endl;
    }
    void* operator new(size_t size, std::string str) {
        std::cout << "self define operator new" << std::endl;
        return ::operator new(size);
    }
};

void nnnnnew_test() {
    nnnnnew* p = new("12345") nnnnnew;
    delete p;
}