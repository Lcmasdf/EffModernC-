#include <cstdio>
#include <type_traits>
#include <string>
#include <utility>
#include <iostream>

template<typename T>
typename std::remove_reference<T>::type&&
move (T&& param) {
    using ReturnType = typename std::remove_reference<T>::type&&;
    return static_cast<ReturnType>(param);
}

struct P23 {
    P23() : s("test"), k(1) {};
    P23(const P23& rhs) : s(rhs.s), k(rhs.k) {}
    P23(P23&& rhs) noexcept : s(std::move(rhs.s)), k(rhs.k) {
        std::cout << "P23's move construction" << std::endl;
    }

    std::string s;
    int k;
};

P23 f () {
    return P23();
}

