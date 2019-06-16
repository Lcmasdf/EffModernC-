//由如何使用静态成员函数访问非静态成员变量得到此疑问
//当参数中有类的指针时，能够通过成员函数来访问指针所对应的实例中的私有变量

#include <iostream>

using namespace std;

class A {
    public:
    A():v(0){};
    void display(){
        cout << v << endl;
    }
    void try_to_change(A* a) {
        a->v = 100;
    }

    private:
    int v;
};

void test_pointer_in_member_func() {
    A test, tester;

    test.try_to_change(&tester);
    tester.display();
    return ;

}