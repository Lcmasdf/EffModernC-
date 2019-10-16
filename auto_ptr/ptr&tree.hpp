#include <vector>
#include <memory>
#include <iostream>

class link_list {
   public:
struct node {
    node(int val) : val(val), next(nullptr){};
    ~node(){
        std::cout << "node destruct, val " << val << std::endl;
    };
    std::unique_ptr<node> next;
    int val;
};
    link_list();
    ~link_list();

    void insert_tail(int val);
    bool find(int val);
    bool delete_first(int val);

   private:
    std::unique_ptr<node> root;
};

link_list::link_list(): root(nullptr){}
link_list::~link_list(){}

void link_list::insert_tail(int val) {
    //raw pointers shouldn't be avoided as long as they don't _own_ anything

    auto ref = &root;
    while (*ref != nullptr) {
        ref = &((*ref)->next);
    }
    (*ref).reset(new node(val));
}

bool link_list::find(int val) {
    auto ref = &root;
    while (*ref != nullptr) {
        if ((*ref)->val == val) {
            return true;
        }
        ref = &((*ref)->next);
    }
    return false;
}

bool link_list::delete_first(int val) {
    if (root == nullptr) {
        return false;
    }

    if (root->val == val) {
        root.reset(nullptr);
        return true;
    }

    auto ref = &root;
    while ((*ref)->next != nullptr) {
        if ((*ref)->next->val == val) {
            (*ref)->next.reset(nullptr);
            return true;
        }
        ref = &((*ref)->next);
    }

    return false;
}