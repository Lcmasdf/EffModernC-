# 左值，右值

在C++11之后，值分为左值，纯右值，将亡值


## TODO list
* 在C++11之前，能否实现类似右值移动的功能？在实现的过程中有否某些困难。

移动，右值移动，浅拷贝，深拷贝

C++11之前，非const引用是无法绑定右值上。

    void simulate_move(move_z& z);

    void simulate_move(ret_move_z());//这个方法的目的在于接受一个右值，将其中的数据move掉。

深，浅拷贝 --> 移动
移动 ！= 右值移动

## 思考，右值移动的适用场景

可以被优化的是不具名的临时对象，这些对象往往在发挥了作用之后就被析构掉了
C++11中把这些对象重新利用起来

返回值优化，是move存在的重要意义



返回指针似乎更高效
什么时候需要返回对象？
返回指针不符合谁申请，谁释放的原则；在函数嵌套调用的时候会造成巨大的心智负担；

RVO优化
右值移动是一种不用担心释放，心智负担小的，提高返回值利用率的方法

高效的返回  --->   

移动 -> 右值移动

std::move将移动操作归一到右值移动上
将左值转换成右值引用，然后对其进行移动。对于此种情况程序员要自己确保不再对其中的内容进行操作

对于基础类型，右值引用退化成引用
对于类以及结构体，通过添加移动构造函数配合std::move来将左值强转成右值应用，从而实现移动


右值引用的应用：
移动构造函数，operator=的重载
接受右值引用参数的函数，例如c++11之后的stl容器中的方法

std::move
只做型别转换，将一个值转换为右值
std::move的核心是static_cast 将参数型别强制转化为右值引用
参数为T&&的万能应用

引用折叠
引用折叠，对于T&&类型的模板参数，T的推导规则
如果传递的实参是左值，T的推到就是左值引用；如果传递的实参是右值，那么T的推导是个非引用型别


对于形如
    template< typename T >
    void func (T&&)

类型的方法