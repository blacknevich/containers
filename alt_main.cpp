#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <ctime>
#include <sys/time.h>

#include "ft_vector.hpp"
#include "ft_stack.hpp"
#include "ft_map.hpp"

#define mylib   ft::Vector
#define clalib  std::vector
#define mylibst   ft::Stack
#define clalibst  std::stack
#define mymap   ft::Map
#define clamap  std::map

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define RESET   "\x1b[0m"

int multi = 10000000;
int map_multi = 100000;

volatile static time_t my_time;
volatile static time_t std_time;
volatile static time_t start;

void show_test_result(time_t my, time_t standard) {
    if (my >= 20 * standard)
    {
        std::cout << BLUE << "ft time: " << RED << std::to_string(my) << "ms" << RESET << " | ";
        std::cout << BLUE << "std time: " << RESET << std::to_string(standard) << "ms"<< " | ";
        if (my == 0 || standard == 0)
            std::cout << BLUE << "ratio: " << RED << 0 << RESET << std::endl;
        else
            std::cout << BLUE << "ratio: " << RED << static_cast<float>(my) / standard << RESET << std::endl;
    }
    else if (my < standard)
    {
        std::cout << BLUE << "ft time: " << GREEN << std::to_string(my) << "ms" << RESET << " | ";
        std::cout << BLUE << "std time: " << RESET << std::to_string(standard) << "ms"<< " | ";
        if (my == 0 || standard == 0)
            std::cout << BLUE << "ratio: " << GREEN << 0 << RESET << std::endl;
        else
            std::cout << BLUE << "ratio: " << GREEN << static_cast<float>(my) / standard << RESET << std::endl;
    }
    else
    {
        std::cout << BLUE << "ft time: " << YELLOW << std::to_string(my) << "ms" << RESET << " | ";
        std::cout << BLUE << "std time: " << RESET << std::to_string(standard) << "ms"<< " | ";
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

void balancly_fill_map_with_range(mymap<int, int> & map, int n) {
    for (int i = 0; i < n / 2; ++i) {
        map.insert(ft::pair<int, int>(i, i));
        map.insert(ft::pair<int, int>(n - i - 1, n - i - 1));
    }
}

void std_balancly_fill_map_with_range(clamap<int, int> & map, int n) {
    for (int i = 0; i < n / 2; ++i) {
        map.insert(std::pair<int, int>(i, i));
        map.insert(std::pair<int, int>(n - i - 1, n - i - 1));
    }
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

void assign() {
    mylib<int>     test_vector(multi / 2, 4);
    clalib<int>    test_vector2(multi / 2, 4);
    mylib<int>     test_vector3(multi / 2, 4);
    clalib<int>    test_vector4(multi / 2, 4);

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

    mylib<int>     test_vector(multi, 4);
    clalib<int>    test_vector2(multi, 4);
    mylib<int>     test_vector3(multi, 4);
    clalib<int>    test_vector4(multi, 4);

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

void stack() {
    mylibst<int>     test_vector;
    clalibst<int>    test_vector2;

    test_announce("stack push");
    start = timer();
    for(int i = 0; i < multi; ++i)
        test_vector.push(7);
    my_time  = timer() - start;

    start = timer();
    for(int i = 0; i < multi; ++i)
        test_vector2.push(7);
    std_time  = timer() - start;

    show_test_result(my_time, std_time);

    test_announce("stack pop");
    start = timer();
    for(int i = 0; i < multi; ++i)
        test_vector.pop();
    my_time  = timer() - start;

    start = timer();
    for(int i = 0; i < multi; ++i)
        test_vector2.pop();
    std_time  = timer() - start;

    show_test_result(my_time, std_time);
}

void map_constructor() {
    test_announce("range map construction");
    mymap<int, int>     base_map;
    balancly_fill_map_with_range(base_map, map_multi);
    clamap<int, int>    base_std_map;
    std_balancly_fill_map_with_range(base_std_map, map_multi);

    start = timer();
    mymap<int, int>     test_vector(base_map.begin(), base_map.end());
    my_time  = timer() - start;

    start = timer();
    clamap<int, int>     test_vector2(base_std_map.begin(), base_std_map.end());
    std_time  = timer() - start;

    show_test_result(my_time, std_time);

    test_announce("range map erase");

    start = timer();
    base_map.erase(base_map.begin(), base_map.end());
    my_time  = timer() - start;

    start = timer();
    base_std_map.erase(base_std_map.begin(), base_std_map.end());
    std_time  = timer() - start;

    show_test_result(my_time, std_time);
}

    int main(void)
{
    constructor();
    resize();
    assign();
    push_back();
    insert();
    stack();
    map_constructor();
}
