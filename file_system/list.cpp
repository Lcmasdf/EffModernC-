#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#include "list.h"

using namespace std;
namespace ls {

vector<file> c11_ls(string dir) {
    if (dir.empty()) {
        cerr << "empty dir" << endl;
        return vector<file>{};
    }

    struct stat s;
    lstat(dir.c_str(), &s);
    if (!S_ISDIR(s.st_mode)) {
        cerr << dir << " not dir" << endl;
        return vector<file>{};
    }

    DIR *d;
    d = opendir(dir.c_str());

    struct dirent *filename;
    vector<file> ret;

    while ((filename = readdir(d)) != NULL) {
        if (strcmp(filename->d_name, ".") == 0 ||
            strcmp(filename->d_name, "..") == 0) {
            continue;
        }
        ret.emplace_back(filename->d_type, filename->d_name);
    }
    return ret;
}

}  // namespace ls
