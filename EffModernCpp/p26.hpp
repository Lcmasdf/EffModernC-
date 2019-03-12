#include <set>
#include <iostream>

class Person {
   public:
    Person() : age(0) {}

    Person(int age): age(age) {}

    Person(const Person& rhs): age(rhs.age) {
        std::cout << "copy construction of Person" << std::endl;
    }

   private:
   int age;
};


class SpecialPerson :public Person {
    public:
    SpecialPerson() : salary(0), Person(1) {}
    SpecialPerson(const SpecialPerson& rhs): Person(rhs) {
        std::cout << "copy construction of SpecialPerson" << std::endl;
    }

    private:
    int salary;
};

std::multiset<std::string> names;

void print_and_add(const std::string& rhs) {
    std::cout << rhs << std::endl;
    names.emplace(rhs);
}

template<typename T>
void print_and_add_improve(T&& rhs) {
    std::cout << rhs << std::endl;
    names.emplace(std::forward<T>(rhs));
}


void p26_test () {
    SpecialPerson sp;

    SpecialPerson sp1(sp);

    std::string ruby("Ruby");
    print_and_add(ruby);
    print_and_add_improve(std::move(ruby));
}