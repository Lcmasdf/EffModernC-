#include <stack>
#include <exception>
#include <memory>
#include <mutex>

class empty_stack: public std::exception {
    const char* what() const throw() {
        return "empty stack error";
    }
};

template<typename T>
class threadsafe_stack {
    public:
    threadsafe_stack() {};
    threadsafe_stack(const threadsafe_stack<T>& other) {
        std::lock_guard<std::mutex> guard(other.m);
        s = other.s;
    }
    threadsafe_stack& operator=(const threadsafe_stack&) = delete;

    ~threadsafe_stack(){};

    bool empty() const {
        std::lock_guard<std::mutex> guard(m);
        return s.empty();
    }

    void push(T new_value) {
        std::lock_guard<std::mutex> guard(m);
        s.push(new_value);
    }

    std::shared_ptr<T> pop() {
        std::lock_guard<std::mutex> guard(m);
        if (s.empty()) {
            throw empty_stack();
        }

        std::shared_ptr<T> const res(std::make_shared<T>(s.top()));
        s.pop();
        return res;
    }

    void pop(T& value) {
        std::lock_guard<std::mutex> guard(m);
        if (s.empty()) {
            throw empty_stack();
        }

        value = s.top();
        s.top();
    }

    private:
    std::stack<T> s;
    mutable std::mutex m;
};