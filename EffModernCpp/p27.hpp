#include <type_traits>
#include <iostream>


class B {
    public:
    operator bool() {
        return false;
    }
};

//implement of is_integral

struct my_false_type {
    
};

template<typename T> 
struct _my_is_integral_helper : public std::false_type {};

template<>
struct _my_is_integral_helper<int> : public std::true_type {};

template<typename T>
struct my_is_integral: public _my_is_integral_helper<T> {};


void p27_test() {
    B b;
    if (b == false) {
        std::cout << "bool(B) ok" << std::endl;
    }

    if (my_is_integral<int>()) {
        std::cout << "my_is_integral works well" << std::endl;
    }
}