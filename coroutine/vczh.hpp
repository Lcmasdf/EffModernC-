/*
这个项目通过浮现vczh在知乎上的文章来了解，corotine的原理 
*/

#include <vector>
#include <iostream>

using namespace std;

/*
step 1:  make a simple coutinuation
*/

// int fuck(const vector<int>& nums) {
//     int sum = 0;
//     for (auto x : nums) {
//         //interupt here
//         sum += x;
//     }
//     return sum;
// }

// int fuck_expand(const vector<int>& nums) {
//     int sum = 0;
//     auto iter = nums.begin();
//     while (iter != nums.end()) {
//         //interupt here
//         sum += *iter;
//         ++iter;
//     }
//     return sum;
// }

// int fuck_expand_continues(const vector<int>& nums) {
//     // part1
//     int sum = 0;
//     auto iter = nums.begin();
//     if (iter != nums.end()) {
//         // part2
//     } else {
//         return sum;
//     }

//     // part2
//     sum += *iter;
//     ++iter;
//     if (iter != nums.end()) {
//         // part2
//     } else {
//         return sum;
//     }
// }

// /*
// step 2: add a constrain to make more general continuation
// */
// /*shit callable*/ int shit(int x, int sum) {
//     //interupt here
//     return x + sum;
// }

// /*shit callable*/ int fuck(const vector<int>& nums) {
//     int sum = 0;
//     auto iter = nums.begin();
//     while (iter != nums.end()) {
//         sum = /*shit call*/shit(*iter, sum);
//         ++iter;
//     }
//     return sum;
// }

// class IShitCallableBase {
//     virtual bool shit_call() = 0;
// };

template<typename T>
class IShitCallableBase {
    public:
    virtual T get() = 0;
    virtual bool shit_call() = 0;
};

class IShitCallable_shit: public IShitCallableBase<int> {
    public:
    IShitCallable_shit(){};
    IShitCallable_shit(int x, int sum): x(x), sum(sum), state(0){};
    int get() {
        return ret;
    }
    bool shit_call() {
        switch(state) {
            case 0:
                state = 1;
                return false;
                break;
            case 1:
                state = 2;
                ret = x + sum;
                return true;
                break;
            default:
                // throw shit_call err
                return false;
                break;
        }
    }
    private:
    int x;
    int sum;;
    int ret;
    int state;
};


//头脑风暴，将fuck展开，形成continuation
class IShitCallable_fuck: public IShitCallableBase<int> {
    public:
    IShitCallable_fuck(const vector<int>& nums): nums(nums){};
    int get() {
        return sum;
    }
    bool shit_call() {
        switch(status) {
            case 0:
                sum = 0;
                iter = nums.begin();

                while (iter != nums.end()) {
                    sc = IShitCallable_shit(sum, *iter);
                    if (!sc.shit_call()) {
                        status = 1;
                        return false;
                    }
                }
                return true;
            case 1:
                if (!sc.shit_call()) {
                    return false;
                } else {
                    sum = sc.get();
                    while (++iter != nums.end()) {
                        sc = IShitCallable_shit(sum, *iter);
                        if (!sc.shit_call()) {
                            status = 1;
                            return false;
                        }
                        sum = sc.get();
                    }
                    return true;
                }
        }
    }

    private:
    vector<int> nums;
    int sum;    
    int status = 0;
    decltype(nums.begin())iter;
    IShitCallable_shit sc;
};

//使用更统一的方法构建fuck的continuation
class IShitCallable_fuck_improve: public IShitCallableBase<int> {
    public:
    IShitCallable_fuck_improve(const vector<int>& nums): nums(nums){};
    int get() {
        return sum;
    }
    bool shit_call() {
    }

    private:
    vector<int> nums;
    int sum;    
    int status = 0;
    decltype(nums.begin())iter;
    IShitCallable_shit sc;
};

void test_continuation() {
    vector<int> input = {1,2,3,4,5};
    IShitCallable_fuck fuc(input);
    while (!fuc.shit_call()) {
        std::cout << "shit_call" << std::endl;
    }

    std::cout << fuc.get() << std::endl;
}