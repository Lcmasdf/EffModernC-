/*#include <thread>
#include <iostream>
#include <unistd.h>

using namespace std;
int sleep_and_add(int n) {
    int ret = 0;
    for (int i = 0 ; i < n; i++) {
        sleep(i);
        ret += i;
    }
    return ret;
}

void test() {
    auto func1 = std::async(std::launch::deferred, sleep_and_add, 3);
    auto func2 = std::async(std::launch::async, sleep_and_add, 3);

    sleep(2);
    func1.get();
    func2.get();
    return ;
}
*/