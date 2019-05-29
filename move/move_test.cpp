#include <iostream>

#include "class.hpp"

//右值的生存周期

void test() {
    move_A ta;
    move_A tb(ta);
    move_A tc(std::move(ta));
    std::cout << "xx" << std::endl;
    move_A td(move_A());
    td.display();
    std::cout << "xx" << std::endl;
}