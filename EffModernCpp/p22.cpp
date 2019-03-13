#include "p22.h"

int Test::get_vector_first() {
    if (v1.empty()) {
        throw ("v1 empty");
    }

    return v1[0];
}

void Test::vector_push_back(int src) {
    v1.push_back(src);
}

struct TestImprove::Impl{
    std::vector<int> v1;
};

TestImprove::TestImprove() : pImpl(new Impl){
}

TestImprove::~TestImprove() {
    delete pImpl;
}

void TestImprove::vector_push_back(int src) {
    pImpl->v1.push_back(src);
}

int TestImprove::get_vector_first() {
    if (pImpl->v1.empty()) {
        throw("v1 empty");
    }
    return pImpl->v1[0];
}

struct TestImprovePP::Impl {
    std::vector<int> v1;
};

TestImprovePP::TestImprovePP() : pImpl(std::unique_ptr<Impl>()) {}

TestImprovePP::~TestImprovePP() = default;

void TestImprovePP::vector_push_back(int src) {
    pImpl->v1.push_back(src);
}

