#include <iostream>
#include <memory>

class Investment {
    public:
    virtual void print() = 0;
    virtual ~Investment() {};
};

class Stock : public Investment {
    void print() override {
        std::cout << "Stock" << std::endl;
    }
};

class Bond : public Investment {
    void print() override {
        std::cout << "Bond" << std::endl;
    }
};

auto delInvmt = [](Investment* pInvestment) {
    pInvestment->print();
    delete pInvestment;
};

std::unique_ptr<Investment, decltype(delInvmt)> makeInvestment (std::string type) {
    std::unique_ptr<Investment, decltype(delInvmt)> pInv(nullptr, delInvmt);
    if ("Stock" == type) {
        pInv.reset(new Stock());
    } else if ("Bond" == type) {
        pInv.reset(new Bond());
    }

    return pInv;
};