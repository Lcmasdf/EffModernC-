#include <memory>
#include <iostream>

struct Matrix {
    int x;
    int y;

    Matrix() : x(0), y(0) {
        std::cout << "Matrix's no param construct" << std::endl;
    }
    Matrix(int a, int b): x(a), y(b) {
        std::cout << "Matrix's param construct" << std::endl;
    }
    Matrix(Matrix&& rhs): x(std::move(rhs.x)), y(std::move(rhs.y)) {
        std::cout << "Matrix's move construct" << std::endl;
    }
    Matrix(Matrix& rhs): x(rhs.x), y(rhs.y) {
        std::cout << "Matrix's copy construct" << std::endl;
    }

    void operator+=(const Matrix& rhs) {
        x += rhs.x;
        y += rhs.y;
    }

    void operator= (const Matrix& rhs) {
        x = rhs.x;
        y = rhs.y;
    }
};

//针对这种情况,必须按值进行返回
Matrix operator+ (Matrix&& lhs, const Matrix& rhs) {
    lhs += rhs;
    return std::move(lhs);
}


// Matrix operator+ (Matrix&& lhs, const Matrix& rhs) {
//     lhs += rhs;
//     return lhs;
// }

Matrix RVO_test () {
    Matrix t(2,3);

    return t;
}

Matrix anti_RVO () {
    Matrix t(3,4);
    return std::move(t);
}


void p25_test () {
    Matrix a(1,2), b(2,3);

    std::cout << "move 1 :  " << std::endl;

    a = Matrix(3,4) + b;

    std::cout << std::endl;
    std::cout << "RVO : " << std::endl;
    auto t = RVO_test();
    std::cout << t.x << std::endl;

    std::cout << std::endl;
    std::cout << "anti RVO : " << std::endl;
    auto at = anti_RVO();


}