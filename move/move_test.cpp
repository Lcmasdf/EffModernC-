#include <iostream>

#include "class.hpp"

//右值的生存周期

// void test() {
//     move_A ta;
//     move_A tb(ta);
//     move_A tc(std::move(ta));
//     std::cout << "xx" << std::endl;
//     move_A td(move_A());
//     td.display();
//     std::cout << "xx" << std::endl;
// }

void test () {
    move_z t1("lichengmin");
    move_z t2("xxxxxx");
    //t2.simulate_move(t1.get_move_z());
    t2.simulate_move(&t1.get_move_z());

    t2.disp();
}