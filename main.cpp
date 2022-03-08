#include <iostream>
#include <vector>
#include <time.h>
#include <ctime>
#include <sys/time.h>

#include "ft_vector.hpp"

#define mylib   ft::Vector
#define clalib  std::vector

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define RESET   "\x1b[0m"

int multi = 10000000;

volatile static time_t my_time;
volatile static time_t std_time;
volatile static time_t start;

void show_test_result(time_t my, time_t standard) {
    if (my >= 20 * standard)
    {
        std::cout << BLUE << "ft_vector time: " << RED << std::to_string(my) << "ms" << RESET << " | ";
        std::cout << BLUE << "std_vector time: " << RESET << std::to_string(standard) << "ms"<< " | ";
        if (my == 0 || standard == 0)
            std::cout << BLUE << "ratio: " << RED << 0 << RESET << std::endl;
        else
            std::cout << BLUE << "ratio: " << RED << static_cast<float>(my) / standard << RESET << std::endl;
    }
    else if (my < standard)
    {
        std::cout << BLUE << "ft_vector time: " << GREEN << std::to_string(my) << "ms" << RESET << " | ";
        std::cout << BLUE << "std_vector time: " << RESET << std::to_string(standard) << "ms"<< " | ";
        if (my == 0 || standard == 0)
            std::cout << BLUE << "ratio: " << GREEN << 0 << RESET << std::endl;
        else
            std::cout << BLUE << "ratio: " << GREEN << static_cast<float>(my) / standard << RESET << std::endl;
    }
    else
    {
        std::cout << BLUE << "ft_vector time: " << YELLOW << std::to_string(my) << "ms" << RESET << " | ";
        std::cout << BLUE << "std_vector time: " << RESET << std::to_string(standard) << "ms"<< " | ";
        if (my == 0 || standard == 0)
            std::cout << BLUE << "ratio: " << YELLOW << 0 << RESET << std::endl;
        else
            std::cout << BLUE << "ratio: " << YELLOW << static_cast<float>(my) / standard << RESET << std::endl;
    }
    std::cout << std::endl;
}

time_t timer() {
    struct timeval begin = {};
    gettimeofday(&begin, nullptr);
    time_t msecs_time = (begin.tv_sec * 1000) + (begin.tv_usec / 1000);
    return msecs_time;
}

void test_announce (std::string str) {
    std::cout << BLUE << "                        " << MAGENTA << str << RESET << std::endl;
}

void constructor() {
    test_announce("fill construction");
    start = timer();
    mylib<int>     test_vector(multi, 7);
    my_time  = timer() - start;

    start = timer();
    clalib<int>     test_vector2(multi, 7);
    std_time  = timer() - start;

    show_test_result(my_time, std_time);

    test_announce("range construction");
    start = timer();
    mylib<int>     test_vector3(test_vector.begin(), test_vector.end());
    my_time  = timer() - start;

    start = timer();
    clalib<int>     test_vector4(test_vector.begin(), test_vector.end());
    std_time  = timer() - start;

    show_test_result(my_time, std_time);
}

void resize() {
    mylib<int>     test_vector;
    clalib<int>    test_vector2;

    test_announce("resize");
    start = timer();
    test_vector.resize(multi, 7);
    my_time  = timer() - start;

    start = timer();
    test_vector2.resize(multi, 7);
    std_time  = timer() - start;

    show_test_result(my_time, std_time);
}

void reserve() {

    mylib<int>     test_vector;
    clalib<int>    test_vector2;

    test_announce("reserve");
    start = timer();
    test_vector.reserve(multi *5);
    my_time  = timer() - start;

    start = timer();
    test_vector2.reserve(multi*5);
    std_time  = timer() - start;

    show_test_result(my_time, std_time);
}

void assign() {
    mylib<int>     test_vector(multi / 10, 4);
    clalib<int>    test_vector2(multi / 10, 4);
    mylib<int>     test_vector3(multi / 10, 4);
    clalib<int>    test_vector4(multi / 10, 4);

    test_announce("assign fill");
    start = timer();
    test_vector.assign(multi, 7);
    my_time  = timer() - start;

    start = timer();
    test_vector2.assign(multi, 7);
    std_time  = timer() - start;

    show_test_result(my_time, std_time);

    test_announce("assign range");
    start = timer();
    test_vector3.assign(test_vector.begin(), test_vector.end());
    my_time  = timer() - start;

    start = timer();
    test_vector4.assign(test_vector2.begin(), test_vector2.end());
    std_time  = timer() - start;

    show_test_result(my_time, std_time);
}

void push_back() {
    mylib<int>     test_vector;
    clalib<int>    test_vector2;

    test_announce("push back");
    start = timer();
    for(int i = 0; i < multi; ++i)
        test_vector.push_back(7);
    my_time  = timer() - start;

    start = timer();
    for(int i = 0; i < multi; ++i)
        test_vector2.push_back(7);
    std_time  = timer() - start;

    show_test_result(my_time, std_time);

    test_announce("erase");
    start = timer();
    test_vector.erase(test_vector.begin(), test_vector.end());
    my_time  = timer() - start;

    start = timer();
    test_vector2.erase(test_vector2.begin(), test_vector2.end());
    std_time  = timer() - start;

    show_test_result(my_time, std_time);
}

void insert() {

    mylib<int>     test_vector(multi / 10, 4);
    clalib<int>    test_vector2(multi / 10, 4);
    mylib<int>     test_vector3(multi / 10, 4);
    clalib<int>    test_vector4(multi / 10, 4);

    test_announce("insert fill");
    start = timer();
    test_vector.insert(test_vector.begin(), multi, 7);
    my_time  = timer() - start;

    start = timer();
    test_vector2.insert(test_vector2.begin(), multi, 7);
    std_time  = timer() - start;

    show_test_result(my_time, std_time);

    test_announce("insert range");
    start = timer();
    test_vector3.insert(test_vector3.begin(), test_vector.begin(), test_vector.end());
    my_time  = timer() - start;

    start = timer();
    test_vector4.insert(test_vector4.begin(), test_vector2.begin(), test_vector2.end());
    std_time  = timer() - start;

    show_test_result(my_time, std_time);
}

void blabla_test() {

}

#define lib ft
#define con Vector
class Test {
public:
    Test() : some_(0) {
//         std::cout << "Test created" << std::endl;
        this->str_ = (char*)malloc(10);
    }

    Test(int s) : some_(s) {
//         std::cout << "Test " << this->some_ << " created" << std::endl;
//        this->str_ = (char*)malloc(10);
        str_ = new char[1];
    }

    Test(Test const & x) : some_(x.some_) {
//         std::cout << "Copy Test " << this->some_ << " created" << std::endl;
//        this->str_ = (char*)malloc(10);
        str_ = new char[1];
    }

    ~Test() {
//        if (this->str_ != 0)
        delete str_;
//            free(this->str_);
        this->some_ = 0;
        this->str_  = 0;
//         std::cout << "Test deleted" << std::endl;
    }

    Test &operator=(Test const & x) {
//         std::cout << "Test operator =" << std::endl;
        if (this == &x)
            return (*this);
//        this->str_ = (char*)malloc(10);
        str_ = new char[1];
        this->some_ = x.some_;
        return (*this);
    }

    int   some_;
    char* str_;

};

class Test_loud {
public:
    Test_loud() : some_(0) {
        std::cout << "Test_loud created" << std::endl;
//        this->str_ = (char*)malloc(10);
        str_ = new char[1];
    }

    Test_loud(int s) : some_(s) {
        std::cout << "Test_loud " << this->some_ << " created" << std::endl;
//        this->str_ = (char*)malloc(10);
        str_ = new char[1];
    }

    Test_loud(Test_loud const & x) : some_(x.some_) {
        std::cout << "Copy Test_loud " << this->some_ << " created" << std::endl;
//        this->str_ = (char*)malloc(10);
        str_ = new char[1];
    }

    ~Test_loud() {
//        if (this->str_ != 0)
        delete str_;
//            free(this->str_);
        this->some_ = 0;
        this->str_  = 0;
        std::cout << "Test_loud deleted" << std::endl;
    }

    Test_loud &operator=(Test_loud const & x) {
        std::cout << "Test_loud operator =" << std::endl;
        if (this == &x)
            return (*this);
//        this->str_ = (char*)malloc(10);
        str_ = new char[1];
        this->some_ = x.some_;
        return (*this);
    }

    int   some_;
    char* str_;

};

void action_announce(std::string str) {

    std::cout << std::endl;
    std::cout << "=====================";
    std::cout << str;
    std::cout << "=====================" << std::endl;
    std::cout << std::endl;
}
void swap_test() {

    int _ratio = 1;
    lib::con<int> my(42);

    action_announce("base");
    my.assign(1100 * _ratio, 11);
    lib::con<int> tmp(500 * _ratio, 5), tmp2(1000 * _ratio, 10), tmp3(1500 * _ratio, 15), tmp4(3000 * _ratio, 30);
    std::cout << "Size: " << my.size() << std::endl;
    std::cout <<  "Capacity: " << my.capacity() << std::endl;
    std::cout <<  "[2]: " << my[2] << std::endl;
    long *adr1 = reinterpret_cast<long *>(&my);
    long *adr2 = reinterpret_cast<long *>(&tmp);
    action_announce("switch my and 1st - now 1st, my,  2 3 4");
    my.swap(tmp);
    if (reinterpret_cast<long *>(&my) == adr1 && reinterpret_cast<long *>(&tmp) == adr2)
        std::cout <<  "success" << std::endl;
    std::cout <<  "[2]: " << my[2] << std::endl;
    std::cout << "Size: " << my.size() << std::endl;
    std::cout <<  "Capacity: " << my.capacity() << std::endl;
    action_announce("switch cur and 3rd - now 3rd my 2 1 4");
    my.swap(tmp3);
    std::cout <<  "[2]: " << my[2] << std::endl;
    std::cout << "Size: " << my.size() << std::endl;
    std::cout <<  "Capacity: " << my.capacity() << std::endl;
    action_announce("switch cur and 2nd - now 2 my 3 1 4");
    std::swap(my, tmp2);
    std::cout <<  "[2]: " << my[2] << std::endl;
    std::cout << "Size: " << my.size() << std::endl;
    std::cout <<  "Capacity: " << my.capacity() << std::endl;
    action_announce("switch cur and 4th - now 4 my 3 1 2");
    std::swap(my, tmp4);
    std::cout <<  "[2]: " << my[2] << std::endl;
    std::cout << "Size: " << my.size() << std::endl;
    std::cout <<  "Capacity: " << my.capacity() << std::endl;

    action_announce("etalon");
    std::vector<int> etalon(42);
    etalon.assign(1100 * _ratio, 11);
    std::vector<int> tmpr(500 * _ratio, 5), tmpr2(1000 * _ratio, 10), tmpr3(1500 * _ratio, 15), tmpr4(3000 * _ratio, 30);
    std::cout << "Size: " << etalon.size() << std::endl;
    std::cout <<  "Capacity: " << etalon.capacity() << std::endl;
    std::cout <<  "[2]: " << etalon[2] << std::endl;
    long *adrr1 = reinterpret_cast<long *>(&etalon);
    long *adrr2 = reinterpret_cast<long *>(&tmpr);
    action_announce("switch my and 1st - now 1st, my,  2 3 4");
    etalon.swap(tmpr); //switch my and 1st - now 1st, my,  2 3 4
    if (reinterpret_cast<long *>(&etalon) == adrr1 && reinterpret_cast<long *>(&tmpr) == adrr2)
        std::cout <<  "success" << std::endl;
    std::cout <<  "[2]: " << etalon[2] << std::endl;
    std::cout << "Size: " << etalon.size() << std::endl;
    std::cout <<  "Capacity: " << etalon.capacity() << std::endl;
    action_announce("switch cur and 3rd - now 3rd my 2 1 4");
    etalon.swap(tmpr3); // switch cur and 3rd - now 3rd my 2 1 4
    std::cout <<  "[2]: " << etalon[2] << std::endl;
    std::cout << "Size: " << etalon.size() << std::endl;
    std::cout <<  "Capacity: " << etalon.capacity() << std::endl;
    action_announce("switch cur and 2nd - now 2 my 3 1 4");
    std::swap(etalon, tmpr2); //switch cur and 2nd - now 2 my 3 1 4
    std::cout <<  "[2]: " << etalon[2] << std::endl;
    std::cout << "Size: " << etalon.size() << std::endl;
    std::cout <<  "Capacity: " << etalon.capacity() << std::endl;
    action_announce("switch cur and 4th - now 4 my 3 1 2");
    std::swap(etalon, tmpr4); //switch cur and 4th - now 4 my 3 1 2
    std::cout <<  "[2]: " << etalon[2] << std::endl;
    std::cout << "Size: " << etalon.size() << std::endl;
    std::cout <<  "Capacity: " << etalon.capacity() << std::endl;
}
int main(void)
{
//    constructor();
//    resize();
//    reserve();
//    assign();
//    push_back();
//    insert();
    swap_test();
}
