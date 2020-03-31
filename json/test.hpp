#include <iostream>

#include "json11.h"


using namespace json11x;

void test () {
    auto x = Json {
        Json::object{
            {"capacity", Json(5)}
        }
    };

    std::cout << x.dump() << std::endl;
}