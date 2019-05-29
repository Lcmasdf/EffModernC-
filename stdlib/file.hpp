#include <unistd.h>
#include <iostream>

#include <sys/types.h>
#include <sys/stat.h>

bool test_file() {
    if (0 == access("./CMakeFiles", F_OK)) {
        std::cout << "CMakeFiles exist" << std::endl;
    }

    if (0 == mkdir("./Test", S_IRWXU|S_IRWXG|S_IRWXO)) {
        std::cout << "create file success" << std::endl;
    }
}