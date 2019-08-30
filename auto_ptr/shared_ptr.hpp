// roadmap
// 1.shared_ptr
// 2.__shared_ptr
// 3.sp_count_base
// 4.sp_count_ptr
// 5.sp_count_deleter
// 6.sp_count_ptr_inplace
// **template

class deleter_int{};
class sp_count_ptr;
class sp_count_base;
typedef void (*DeleterFunc)(int*);

class shared_ptr_int {
   public:
    shared_ptr_int(decltype(nullptr), DeleterFunc=nullptr) noexcept;
    explicit shared_ptr_int(int, DeleterFunc=nullptr) noexcept;
    ~shared_ptr_int();

    shared_ptr_int(const shared_ptr_int&) noexcept;
    shared_ptr_int(shared_ptr_int&&) noexcept;

    shared_ptr_int operator=(const shared_ptr_int&) noexcept;
    shared_ptr_int operator=(shared_ptr_int&&) noexcept;
};

class __shared_ptr_int {
    int * _ptr;
    sp_count_base* _Sp_count;
    public:
    // __shared_ptr_int():_ptr(nullptr), _Sp_count(new sp_counter_ptr()) {};
    __shared_ptr_int() noexcept;
    __shared_ptr_int(int, DeleterFunc) noexcept;
    __shared_ptr_int(const __shared_ptr_int&) noexcept;
    __shared_ptr_int(__shared_ptr_int&&) noexcept;

    __shared_ptr_int operator=(const __shared_ptr_int&) noexcept;
    __shared_ptr_int operator=(__shared_ptr_int&&) noexcept;
    int operator*() noexcept;
    int operator->() noexcept;
};

__shared_ptr_int::__shared_ptr_int():_ptr(nullptr), _Sp_count(nullptr) {
}

__shared_ptr_int::__shared_ptr_int(int val, DeleterFunc del) {
    _ptr = new int(val);
    _Sp_count = new sp_count_ptr(_ptr, del);
}

class sp_count_base {
    int* _ptr;
    DeleterFunc _del;
    unsigned int _use_count;
    unsigned int _weak_count;
    public:
    sp_count_base(int*, DeleterFunc _del);
    sp_count_base(const sp_count_base&) = delete;
    sp_count_base(sp_count_base&&) = delete;
    ~sp_count_base();

    //use_count--
    void dispose();
    //weak_count--
    void destroy();

    void add_ref();
    void add_weak();

    void deleter(int*);
};

class sp_count_ptr: public sp_count_base {
    public:
    sp_count_ptr();
    sp_count_ptr(int*, DeleterFunc);
};

sp_count_ptr::sp_count_ptr():sp_count_base(nullptr, nullptr){}
sp_count_ptr::sp_count_ptr(int* _ptr, DeleterFunc _del): sp_count_base(_ptr, _del) {}

sp_count_base::sp_count_base(int* ptr, DeleterFunc del)
    : _ptr(ptr), _del(del),_use_count(1),_weak_count(0){}

// sp_count_base::sp_count_base(const sp_count_base& spb)
//     : _ptr(spb._ptr),
//       _del(spb._del),
//       _use_count(spb._use_count),
//       _weak_count(spb._weak_count) {}
    
// sp_count_base::sp_count_base(sp_count_base&&) {
    
// }

void sp_count_base::deleter(int* _ptr) {
    if (_del == nullptr) {
        delete _ptr;
    } else {
        _del(_ptr);
    }
}

void sp_count_base::dispose() {
    if (_use_count == 1) {
        _use_count = 0;
        deleter(_ptr);
        
        if (_weak_count == 0) {
            delete this;
        }
    } else {
        _use_count -= 1;
    }
}

void sp_count_base::destroy() {
    if (_weak_count == 1) {
        _weak_count = 0;

        if (_use_count == 0) {
            delete this;
        }
    } else {
        _weak_count -= 1;
    }
}

void sp_count_base::add_ref() {
    _use_count++;
}

void sp_count_base::add_weak() {
    _weak_count++;
}