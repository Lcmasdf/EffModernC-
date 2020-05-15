#include <mutex>
#include <exception>

class bad_hierarchy : public std::exception {
    const char* what() const noexcept {
        return "bad hierarchy";
    }
};

class hierarchical_mutex {
    private:
    std::mutex internal_mutex;
    static thread_local int thread_hierarchy_level;
    int hierarchy_level;
    int prev_level;
    public:
    explicit hierarchical_mutex(int level):
        hierarchy_level(level), prev_level(0) {
    }
    ~hierarchical_mutex(){}

    static void show_hierarchy_level() {
        std::cout << "thread_hierarchy_level: " << thread_hierarchy_level << std::endl;
    }

    void lock() {
        if (thread_hierarchy_level >= hierarchy_level) {
            throw bad_hierarchy();
        }
        internal_mutex.lock();
        prev_level = thread_hierarchy_level;
        thread_hierarchy_level = hierarchy_level;
    }
    void unlock() {
        thread_hierarchy_level = prev_level;
        internal_mutex.unlock();
    }
    
    bool try_lock() {
        if (thread_hierarchy_level >= hierarchy_level) {
            throw bad_hierarchy();
        }
        if (!internal_mutex.try_lock()) {
            return false;
        }
        prev_level = thread_hierarchy_level;
        thread_hierarchy_level = hierarchy_level;
        return true;
    }
};

thread_local int hierarchical_mutex::thread_hierarchy_level = 0;