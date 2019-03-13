#ifndef P22_H
#define P22_H

#include <vector>
#include <memory>

class Test {
    public:
    int get_vector_first();
    void vector_push_back(int);
    private:
    std::vector<int> v1;
};

class TestImprove {
    public:
    TestImprove();
    ~TestImprove();

    void vector_push_back(int);
    int get_vector_first();
    private:
    struct Impl;
    Impl *pImpl;
};

class TestImprovePP {
    public:
    TestImprovePP();
    ~TestImprovePP();

    void vector_push_back(int);

    private:
    struct Impl;
    std::unique_ptr<Impl> pImpl;
};

#endif