#include <type_traits>

template<typename T>
T&& my_forward(typename std::remove_reference<T>::type& param) {
    return static_cast<T&&>(param);
}

template<typename T>
void func(T&& param) {

    //T&& 能够接受左值作为参数，也能够接受右值作为参数
    //当param由左值进行初始化，我们希望按照左值对param进行调用
    //当param由右值进行初始化，我们希望按照右值对param进行调用

    //所有函数的参数均为左值（右值引用本身也是一个左值）
    //当能够确定param由左值初始化时，param 当成T&使用
    //当能够确定param由右值初始化时，param 当成T&&使用。 static_cast<T&&>(param);

    //C++ 内部通过引用折叠的方式实现这个功能，由以下两部组成

    // 1. T类型推导 ： 当param由左值进行初始化时T被推导为 T&； 当param由右值进行初始化时，T被推导为T&&
    // 2. 引用折叠： T& && 被折叠成为T&； T &&被折叠成为T&&

    //从而使得std::forward能够实现完美转发

    return;
}