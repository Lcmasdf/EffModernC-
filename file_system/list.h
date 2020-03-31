#ifndef LIST_H
#define LIST_H

#include <vector>
#include <string>

namespace ls {
struct file {
    // 8  file ; 4 dir
    file (char t, const std::string fn) {
        type = t;
        filename = fn;
    }
    char type;
    std::string filename;
};

std::vector<file> c11_ls(std::string dir);
}  // namespace ls
#endif