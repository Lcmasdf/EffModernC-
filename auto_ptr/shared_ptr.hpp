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
    __shared_ptr_int(int*, DeleterFunc) noexcept;
    __shared_ptr_int(const __shared_ptr_int&) noexcept;
    __shared_ptr_int(__shared_ptr_int&&) noexcept;

    __shared_ptr_int operator=(const __shared_ptr_int&) noexcept;
    __shared_ptr_int operator=(__shared_ptr_int&&) noexcept;
    int operator*() noexcept;
    int operator->() noexcept;
};

class sp_count_base {
    int* _ptr;
    DeleterFunc _del;
    unsigned int _use_count;
    unsigned int _weak_count;
    public:
    sp_count_base(int*, DeleterFunc _del);
    sp_count_base(const sp_count_base&);
    sp_count_base(sp_count_base&&);
    ~sp_count_base();

    //use_count--
    void dispose();
    //weak_count--
    void destroy();

    void add_ref();
    void add_weak();
};

class sp_count_ptr: public sp_count_base {};

sp_count_base::sp_count_base(int* ptr, DeleterFunc del)
    : _ptr(ptr), _del(del),_use_count(1),_weak_count(0){}

sp_count_base::sp_count_base(const sp_count_base& spb)
    : _ptr(spb._ptr),
      _del(spb._del),
      _use_count(spb._use_count),
      _weak_count(spb._weak_count) {}
    
sp_count_base::sp_count_base(sp_count_base&&) {
    
}