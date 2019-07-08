#include <tuple>
#include <iostream>

//unique_ptr with int

class a_deleter {
    public:
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

    //TODO:为什么nullptr不好使
    // unique_ptr_int(nullptr) noexcept {
    // }

    unique_ptr_int(int* p, a_deleter del = a_deleter())
        : impl(p, std::move(del)) {}

    unique_ptr_int(const unique_ptr_int&) = delete;
    unique_ptr_int& operator=(const unique_ptr_int&) = delete;

    unique_ptr_int(unique_ptr_int&& p) noexcept {
      // std::get return a reference of
      std::get<0>(impl) = p.release();
      std::get<1>(impl) = std::move(p.get_deleter());
    }

    unique_ptr_int& operator=(unique_ptr_int&& p) noexcept {
        std::get<0>(impl) = p.release();
        std::get<1>(impl) = std::move(p.get_deleter());
    }

    void reset(int* p) noexcept {
        // get_deleter()(std::get<0>(impl));
        auto tmp = std::get<0>(impl);
        get_deleter()(tmp);

        tmp = p;
    }

    int* release() {
        auto tmp = get();
        get_deleter()(tmp);
        return tmp;
    }

    //TODO:swap?

    int* get() {
        return std::get<0>(impl);
    }

    a_deleter& get_deleter() {
        return std::get<1>(impl);
    }

    explicit operator bool() {
        return get() == nullptr? false: true;
    }

    //TODO:deference
    // int operator*() {
    //     return *get();
    // }

    // int* operator->() const noexcept {
    //     return get();
    // }
};