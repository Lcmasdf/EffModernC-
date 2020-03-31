#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "exec.h"



using namespace std;

istream& exec_8_1(istream& i) {
    string buf;
    while (i >> buf) {
        cout << buf << ends;
    }

    if (!i.good()) {
        cout << "istream bad stat" << ends;
    }

    i.clear();
    return i;
}

void exec_8_2() {
    fstream f;
    f.open("test.txt", std::ios_base::openmode::_S_in);
    vector<string> buf;
    if (f.is_open()) {
        string tmp;
        while (f >> tmp) {
            buf.push_back(std::move(tmp));
        }
    }
    cout << buf.size() << endl;

    f.close();
    buf.clear();
    f.open("test.txt", std::ios_base::openmode::_S_in);
    if (f.is_open()) {
        string tmp;
        while (getline(f, tmp)) {
            buf.push_back(std::move(tmp));
        }
    }
    cout << buf.size() << endl;
}

void exec_8_3() {
    vector<string> content;
    ifstream fin("test.txt");
    if (!fin.is_open()) {
        cout << "open failed" << endl;
        return;
    }

    string line, word;
    while (getline(fin, line)) {
        content.emplace_back(line);
    }

    for (auto& x : content) {
        istringstream strm(x);
        while (strm >> word) {
            cout << word << endl;
        }
    }
}