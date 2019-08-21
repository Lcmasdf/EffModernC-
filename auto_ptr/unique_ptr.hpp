#include <tuple>
#include <iostream>

//unique_ptr with int

class a_deleter {
    public:
    constexpr a_deleter() noexcept = default;
    void operator()(int *p) {
        if (p) {
            delete p;
        }
        std::cout << "default deleter" << std::endl; 
    }
};

class unique_ptr_int {
    int* release() {
        int* tmp = std::get<0>(impl);
        get_deleter()(tmp);
        return tmp;
    };
    a_deleter& get_deleter();
    std::tuple<int*, a_deleter> impl;

    public:
    unique_ptr_int() noexcept {
    }

    //nullptr 不是类型，需要使用decltype(nullptr)
    unique_ptr_int(decltype(nullptr)) noexcept {
    }

    unique_ptr_int(int* p, a_deleter del = a_deleter())
        : impl(p, std::move(del)) {}

    unique_ptr_int(const unique_ptr_int&) = delete;
    ~unique_ptr_int() {
        get_deleter()(get());
        std::get<0>(impl) = nullptr;
    }
    unique_ptr_int& operator=(const unique_ptr_int&) = delete;

    unique_ptr_int(unique_ptr_int&& p) noexcept {
      // std::get return a reference of
      std::get<0>(impl) = p.release();
      std::get<1>(impl) = std::move(p.get_deleter());
    }

    //operator实现有误
    // unique_ptr_int& operator=(unique_ptr_int&& p) noexcept {
    //     std::get<0>(impl) = p.release();
    //     std::get<1>(impl) = std::move(p.get_deleter());
    // }

    unique_ptr_int& operator=(unique_ptr_int&& p) noexcept {
        reset(p.release());
        get_deleter() = std::move(p.get_deleter());
        return *this;
    }

    unique_ptr_int& operator=(nullptr_t) noexcept {
        reset();
        return *this;
    }

    //stl 的reset方法增加了默认值nullptr
    //stl 的reset方法使用了swap
    void reset(int* p = nullptr) noexcept {
        std::swap(std::get<0>(impl), p);
        //deleter 内部实现是assert not nullptr，所以要在这里判断
        if (p != nullptr) {
            get_deleter()(p);
        }
    }

    //release并不会释管理的内存
    int* release() {
        auto tmp = get();
        // get_deleter()(tmp);
        std::get<0>(impl) = nullptr;
        return tmp;
    }

    int* get() {
        return std::get<0>(impl);
    }

    a_deleter& get_deleter() {
        return std::get<1>(impl);
    }

    explicit operator bool() {
        return get() == nullptr? false: true;
    }

    int& operator*() {
        return *get();
    }

    int* operator->() noexcept {
        return get();
    }
};