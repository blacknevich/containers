//
// Created by Namor Scarab on 3/5/22.
//

#include <iostream>
#include <vector>
#include <deque>
#include <stack>
#include <map>
#include "ft_vector.hpp"
#include "ft_map.hpp"
#include "ft_stack.hpp"

#define lib ft
#define con Vector
#define sta Stack
#define coma Map
//#define lib std
//#define con vector
//#define sta stack
//#define coma Map
class Test {
public:
    Test() : some_(0) {
        str_ = new char[1];
    }

    Test(int s) : some_(s) {
        str_ = new char[1];
    }

    Test(Test const & x) : some_(x.some_) {
        str_ = new char[1];
    }

    ~Test() {
        delete str_;
        this->some_ = 0;
        this->str_  = 0;
    }

    Test &operator=(Test const & x) {
        if (this == &x)
            return (*this);
        str_ = new char[1];
        this->some_ = x.some_;
        return (*this);
    }

    bool operator==(Test const & rhs) const {return(some_ == rhs.some_);}
    bool operator!=(Test const & rhs) const {return(some_ != rhs.some_);}
    bool operator<(Test const & rhs) const {return(some_ < rhs.some_);}
    bool operator<=(Test const & rhs) const {return(some_ <= rhs.some_);}
    bool operator>(Test const & rhs) const {return(some_ > rhs.some_);}
    bool operator>=(Test const & rhs) const {return(some_ >= rhs.some_);}

    int   some_;
    char* str_;

};

class Test_loud {
public:
    Test_loud() : some_(0) {
        std::cout << "Test_loud created" << std::endl;
        str_ = new char[1];
    }

    Test_loud(int s) : some_(s) {
        std::cout << "Test_loud " << this->some_ << " created" << std::endl;
        str_ = new char[1];
    }

    Test_loud(Test_loud const & x) : some_(x.some_) {
        std::cout << "Copy Test_loud " << this->some_ << " created" << std::endl;
        str_ = new char[1];
    }

    ~Test_loud() {
        delete str_;
        this->some_ = 0;
        this->str_  = 0;
        std::cout << "Test_loud deleted" << std::endl;
    }

    Test_loud &operator=(Test_loud const & x) {
        std::cout << "Test_loud operator =" << std::endl;
        if (this == &x)
            return (*this);
        str_ = new char[1];
        this->some_ = x.some_;
        return (*this);
    }

    int   some_;
    char* str_;

};

void test_announce(std::string str) {

    std::cout << std::endl;
    std::cout << "=====================";
    std::cout << str;
    std::cout << "=====================" << std::endl;
    std::cout << std::endl;
}

void action_announce(std::string str) {
    std::cout << std::endl;
    std::cout << ">>> action made: ";
    std::cout << str << std::endl;
}

void base_state_announce(std::string str) {
    std::cout << "base_state: ";
    std::cout << str << std::endl;
    std::cout << std::endl;
}

void show_vector_info(lib::con<Test> & vector) {
    std::cout << "size    : " << vector.size()     << std::endl;
    std::cout << "capacity: " << vector.capacity() << std::endl;
    std::cout << "arr     :" << std::endl;
    for (size_t i = 0; i < vector.size(); ++i) {
        if (i != 0 && i % 20 == 0)
            std::cout << std::endl;
        std::cout << vector[i].some_ << " ";
    }
    std::cout << std::endl;
}

template <class KEY, class VAL>
void print_map_info(lib::coma<int, Test> & map) {
    typename lib::coma<int, Test>::iterator it(map.begin());

    std::cout
            << "empty: " << map.empty()
            << " size: "  << map.size() << "\n"
            << "Map:" << std::endl;
    size_t i = 0;
    while (it != map.end()) {
        if (i != 0 && i % 4 == 0) {
            std::cout << "\n";
        }
        std::cout << "key: "  << (*it).first
                  << " val: " << (*it).second.some_ << " | ";
        ++i;
        ++it;
    }
    std::cout << std::endl;
    std::cout << std::endl;
}

void show_map_iterator(lib::coma<int, Test>::iterator it) {
    std::cout << "key: "  << (*it).first
              << " val: " << (*it).second.some_ << std::endl;
}

void show_etalon_vector_info(std::vector<int> & vector) {
    std::cout << "size    : " << vector.size()     << std::endl;
    std::cout << "capacity: " << vector.capacity() << std::endl;
    std::cout << "arr     :" << std::endl;
    for (size_t i = 0; i < vector.size(); ++i) {
        if (i != 0 && i % 20 == 0)
            std::cout << std::endl;
        std::cout << vector[i] << " ";
    }
    std::cout << std::endl;
}

void fill_array_with_123(lib::con<Test> & vector, size_t start) {
    for (size_t i = 0; i < vector.size(); ++i) {
        vector[i].some_ = i + start;
    }
}

void balancly_fill_map_with_range(lib::coma<int, Test> & map, int n) {
    for (int i = 0; i < n/2; ++i) {
//        std::cout << "fill with" << i << std::endl;
        map.insert(lib::pair<int, Test>(i, i));
//        std::cout << "fill with" << n - i - 1 << std::endl;
        map.insert(lib::pair<int, Test>(n - i - 1, n - i - 1));
    }

}

// Constructors ================================================================

void default_constructor() {
    test_announce("default_constructor");
    lib::con<Test> empty;

    std::cout << "empty() : " << empty.empty() << std::endl;
    show_vector_info(empty);
}

void fill_constructor() {
    test_announce("fill constructor");
    lib::con<Test> testy(42);

    std::cout << "empty() : " << testy.empty() << std::endl;
    show_vector_info(testy);
}

void fill_val_constructor() {
    test_announce("fill with val constructor");
    lib::con<Test> testy(42, 2);

    show_vector_info(testy);
}

void copy_constructor() {
    test_announce("assign_node_no_value constructor");
    lib::con<Test> base(42, 7);
    fill_array_with_123(base, 0);
    base.reserve(1000);
    show_vector_info(base);

    action_announce("Copy of get_node made");
    lib::con<Test> copy(base);
    show_vector_info(copy);
}

void resize_test() {
    test_announce("resize");
    base_state_announce("42 vector filled with range");
    lib::con<Test> testy(42);
    fill_array_with_123(testy, 0);
    show_vector_info(testy);
    lib::con<Test> very_small(testy);
    lib::con<Test> small(testy);
    lib::con<Test> big(testy);

    action_announce("resize from 42 to 21 made with val 7");
    big.resize(21, 7);
    show_vector_info(big);

    action_announce("resize from 42 to 63 made with val 7");
    small.resize(63, 7);
    show_vector_info(small);

    action_announce("resize from 63 to 0 made with val 7");
    small.resize(0, 7);
    show_vector_info(small);

    action_announce("resize from 42 to 100 made with val 7");
    very_small.resize(100, 7);
    show_vector_info(very_small);

    very_small.resize(42, 7);
    action_announce("resize from 42 to 102 made with val 7 where capacity is 100");
    very_small.resize(102, 7);
    show_vector_info(very_small);

    action_announce("resize to more then max size");
    try {
        testy.resize(testy.max_size() + 10);

    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    show_vector_info(testy);
}

void reserve_test() {
    test_announce("reserve_test");
    base_state_announce("42 vector filled with range and empty container");
    lib::con<Test> testy(42);
    fill_array_with_123(testy, 0);
    lib::con<Test> empty;

    action_announce("reserve 0 to both containers");
    testy.reserve(0);
    empty.reserve(0);
    show_vector_info(testy);
    show_vector_info(empty);

    action_announce("reserve 42 to both containers");
    testy.reserve(42);
    empty.reserve(42);
    show_vector_info(testy);
    show_vector_info(empty);

    action_announce("reserve 63 to 42 container");
    testy.reserve(63);
    show_vector_info(testy);

    action_announce("reserve 150 to above container");
    testy.reserve(150);
    show_vector_info(testy);

    action_announce("reserve more then max size to above");
    try {
        testy.reserve(testy.max_size() + 10);

    } catch(std::exception & e) {
        std::cout << e.what() << std::endl;
    }
    show_vector_info(testy);
}

void construction_tests() {
    default_constructor();
    fill_constructor();
    fill_val_constructor();
    copy_constructor();
    resize_test();
    reserve_test();
}

// =============================================================================

// Operator '=' ================================================================

void operator_assignment() {
    test_announce("assignment operator test");

    base_state_announce("42 vector filled with range and empty container");
    lib::con<Test> testy(42);
    fill_array_with_123(testy, 0);
    show_vector_info(testy);

    action_announce("are_values_equal get_node to empty container");
    lib::con<Test> empty;
    lib::con<Test> copy(testy);
    testy = empty;
    show_vector_info(testy);

    action_announce("are_values_equal empty to fool");
    testy = copy;
    show_vector_info(testy);
}

// =============================================================================

// Iterators ===================================================================

void iterator_test() {
    test_announce("iterator_test");
    base_state_announce("42 vector filled with range and empty container");
    lib::con<Test> testy(42);
    fill_array_with_123(testy, 0);
    show_vector_info(testy);

    action_announce("dereferencing following iterators");
    lib::con<Test>::iterator show_begin = testy.begin();
    std::cout << "begin: " << (*show_begin).some_      << std::endl;
    lib::con<Test>::iterator show_end = testy.end();
    std::cout << "end - 1: " << (*(show_end - 1)).some_  << std::endl;
    lib::con<Test>::reverse_iterator show_rev_begin = testy.rbegin();
    std::cout << "rbegin: " << (*show_rev_begin).some_     << std::endl;
    lib::con<Test>::reverse_iterator show_rev_end = testy.rend();
    std::cout << "rend - 1: " << (*(show_rev_end - 1)).some_ << std::endl;

    action_announce("same but vector is const and full of 7s now");
    lib::con<const Test> const_testy(42, 7);

    lib::con<Test>::const_iterator show_const_begin = const_testy.begin();
    std::cout << "begin: " << (*show_const_begin).some_      << std::endl;
    lib::con<Test>::const_iterator show_const_end = const_testy.end();
    std::cout << "end - 1: " << (*(show_const_end - 1)).some_  << std::endl;
    lib::con<Test>::const_reverse_iterator show_rev_const_begin = const_testy.rbegin();
    std::cout << "rbegin: " << (*show_rev_const_begin).some_     << std::endl;
    lib::con<Test>::const_reverse_iterator show_rev_const_end = const_testy.rend();
    std::cout << "rend - 1: " << (*(show_rev_const_end - 1)).some_ << std::endl;

    action_announce("iterator arithmetics end and begin if full");
    std::cout << "difference: " << (show_end - show_begin) << std::endl;
    std::cout << "show_begin + 1: " << (show_begin + 1)->some_ << std::endl;
    std::cout << "1 + show_begin: " << (1 + show_begin)->some_ << std::endl;
    std::cout << "++show_begin: " << (++show_begin)->some_ << std::endl;
    std::cout << "--show_begin: " << (--show_begin)->some_ << std::endl;
}

// =============================================================================

// Element access ==============================================================

void element_access_test() {
    test_announce("element access test");
    base_state_announce("42 vector filled with range and empty container");
    lib::con<Test> testy(42);
    fill_array_with_123(testy, 0);
    show_vector_info(testy);

    base_state_announce("empty vector");
    lib::con<Test> empty;
    show_vector_info(empty);

    action_announce("at with exceeding range parameter");
    try {
        std::cout << testy.at(1042).some_ << std::endl;

    } catch(std::exception & e) {
        std::cout << e.what() << std::endl;
    }

    action_announce("taking address for empty and value for full");
    empty.front(); //good if compiles
    std::cout << "Front full: " << testy.front().some_ << std::endl;

    empty.back(); //good if compiles
    std::cout << "Back full: " << testy.back().some_ << std::endl;
}

// =============================================================================

// Modifiers ===================================================================

void assign_range_test() {
    test_announce("are_values_equal range test");
    base_state_announce("42 vector filled with range");
    lib::con<Test> testy(42);
    fill_array_with_123(testy, 0);
    show_vector_info(testy);

    base_state_announce("empty vector");
    lib::con<Test> empty;
    show_vector_info(empty);

    base_state_announce("empty vector with 100 capacity");
    lib::con<Test> empty_cap;
    empty_cap.reserve(1000);
    show_vector_info(empty_cap);

    base_state_announce("10 vector filled with range");
    lib::con<Test> small_testy(10);
    fill_array_with_123(small_testy, 10);

    test_announce("are_values_equal range test");

    action_announce("are_values_equal full with range from empty");
    lib::con<Test> copy(testy);
    copy.assign(empty.begin(), empty.end());
    show_vector_info(copy);

    action_announce("are_values_equal empty with range from full with arithmetics");
    empty.assign(testy.begin() + 5, testy.end() - 5);
    show_vector_info(empty);
    show_vector_info(testy);

    action_announce("are_values_equal to full 42 from small vector");
    testy.assign(small_testy.begin(), small_testy.end());
    show_vector_info(testy);
    show_vector_info(small_testy);

    action_announce("are_values_equal to big capacity empty from above");
    empty_cap.assign(small_testy.begin(), small_testy.end());
    show_vector_info(empty_cap);

    test_announce("are_values_equal range test");

    action_announce("are_values_equal to full vector with range from itself");
    show_vector_info(testy);
    testy.assign(testy.begin(), testy.end());
    show_vector_info(testy);

    action_announce("are_values_equal to vector above with range from itself + arithmetics");
    show_vector_info(testy);
    testy.assign(testy.begin() + 3, testy.end() - 3);
    show_vector_info(testy);

    test_announce("are_values_equal range test");

    action_announce("try to are_values_equal from incorrect range from itself");
    try {
        testy.assign(testy.begin() + 10, testy.begin());
    } catch(std::exception & e) {
        std::cout << e.what() << std::endl;
    }
    show_vector_info(testy);

    action_announce("try to are_values_equal from above max size iterator from itself");
    try {
        small_testy.assign(small_testy.begin(), (small_testy.begin() + small_testy.max_size()));
    } catch(std::exception & e) {
        std::cout << e.what() << std::endl;
    }
    show_vector_info(small_testy);
}

void assign_fill_test() {
    test_announce("are_values_equal fill test");
    base_state_announce("42 vector filled with range");
    lib::con<Test> testy(42);
    fill_array_with_123(testy, 0);
    show_vector_info(testy);

    base_state_announce("empty vector");
    lib::con<Test> empty;
    show_vector_info(empty);

    base_state_announce("empty vector with 100 capacity");
    lib::con<Test> empty_cap;
    empty_cap.reserve(1000);
    show_vector_info(empty_cap);

    test_announce("are_values_equal fill test");

    action_announce("are_values_equal to empty with 42 sevens");
    empty.assign(42, 7);
    show_vector_info(empty);

    action_announce("are_values_equal to full with 42 sevens");
    testy.assign(42, 7);
    show_vector_info(testy);

    action_announce("are_values_equal to big capacity empty with 42 sevens");
    empty_cap.assign(42, 7);
    show_vector_info(empty_cap);

    action_announce("are_values_equal to above with 0 sevens");
    empty_cap.assign(0, 7);
    show_vector_info(empty_cap);
}

void push_back_test() {
    test_announce("push back test");
    base_state_announce("42 vector filled with range");
    lib::con<Test> testy(42);
    fill_array_with_123(testy, 0);
    show_vector_info(testy);

    base_state_announce("empty vector");
    lib::con<Test> empty;
    show_vector_info(empty);

    base_state_announce("empty vector with 100 capacity");
    lib::con<Test> empty_cap;
    empty_cap.reserve(1000);
    show_vector_info(empty_cap);

    test_announce("push back test");

    action_announce("push back seven to empty");
    empty.push_back(7);
    show_vector_info(empty);

    action_announce("push back a val from the end of itself to full");
    testy.push_back(testy[41]);
    show_vector_info(testy);

    action_announce("push back a seven to big cap empty");
    empty_cap.push_back(7);
    show_vector_info(empty_cap);
}

void small_stuff_test() {
    test_announce("pop back test");
    base_state_announce("42 vector filled with range");
    lib::con<Test> testy(42);
    fill_array_with_123(testy, 0);
    show_vector_info(testy);

    base_state_announce("empty vector");
    lib::con<Test> empty;
    show_vector_info(empty);

    base_state_announce("10 vector filled with range");
    lib::con<Test> small_testy(10);
    fill_array_with_123(small_testy, 10);
    show_vector_info(small_testy);

    test_announce("pop back test");

    action_announce("ten times pop back from full");
    for (size_t i = 0; i < 10; ++i) {
        testy.pop_back();
    }
    show_vector_info(testy);

    test_announce("small stuff test");

    action_announce("return size of above - size() test");
    std::cout << testy.size() << std::endl;

    action_announce("return size of above - max_size() test");
    std::cout << testy.max_size() << std::endl;

    action_announce("see whether n_val_ return is not null and compiles - n_val_() test");
    if (testy.data())
        std::cout << "successfully compiled" << std::endl;

    test_announce("swap test");

    action_announce("swap full and small");
    testy.swap(small_testy);
    show_vector_info(testy);
    show_vector_info(small_testy);

    action_announce("swap again with std swap(x, y)");
    std::swap(testy, small_testy);
    show_vector_info(testy);
    show_vector_info(small_testy);
}

void insert_val_test() {

    test_announce("insert value test");
    base_state_announce("42 vector filled with range");
    lib::con<Test> testy(42);
    fill_array_with_123(testy, 0);
    show_vector_info(testy);

    base_state_announce("empty vector");
    lib::con<Test> empty;
    show_vector_info(empty);

    base_state_announce("empty vector with 100 capacity");
    lib::con<Test> empty_cap;
    empty_cap.reserve(1000);
    show_vector_info(empty_cap);

    test_announce("insert value test");

    action_announce("insert a seven to begin of full");
    testy.insert(testy.begin(), 7);
    show_vector_info(testy);

    action_announce("insert a seven to end of above");
    testy.insert(testy.end(), 7);
    show_vector_info(testy);

    action_announce("insert a seven to begin of big cap empty");
    empty_cap.insert(empty_cap.end(), 7);
    show_vector_info(empty_cap);

    test_announce("insert value test");

    action_announce("insert numbers to begin of empty");
    empty.insert(empty.begin(), 7);
    empty.insert(empty.begin(), 42);
    show_vector_info(empty);

    action_announce("insert to begin of above a value from begin of itself");
    empty.insert(empty.begin(), empty[0]);
    show_vector_info(empty);

    action_announce("insert to end of above a value from end of itself");
    empty.insert(empty.end(), empty[empty.size() - 1]);
    show_vector_info(empty);

    action_announce("insert to begin of above a value from end of itself");
    empty.insert(empty.begin(), empty[empty.size() - 1]);
    show_vector_info(empty);

    action_announce("insert to end of above a value from begin of itself");
    empty.insert(empty.end(), empty[0]);
    show_vector_info(empty);
}

void insert_fill_test() {
    test_announce("insert fill test");
    base_state_announce("42 vector filled with range");
    lib::con<Test> testy(42);
    fill_array_with_123(testy, 0);
    show_vector_info(testy);

    base_state_announce("empty vector");
    lib::con<Test> empty;
    show_vector_info(empty);

    base_state_announce("empty vector with 100 capacity");
    lib::con<Test> empty_cap;
    empty_cap.reserve(1000);
    show_vector_info(empty_cap);

    test_announce("insert fill test");

    action_announce("insert five sevens to begin of full");
    testy.insert(testy.begin(), 5, 7);
    show_vector_info(testy);

    action_announce("insert five sevens to end of full");
    testy.insert(testy.end(), 5, 7);
    show_vector_info(testy);

    action_announce("insert five sevens to begin of big cap empty");
    empty_cap.insert(empty_cap.begin(), 5, 7);
    show_vector_info(empty_cap);

    test_announce("insert fill test");

    action_announce("insert numbers to begin of empty");
    empty.insert(empty.begin(), 7);
    empty.insert(empty.begin(), 42);
    show_vector_info(empty);

    action_announce("insert to begin of above 5 times value from begin of itself");
    empty.insert(empty.begin(), 5,  empty[0]);
    show_vector_info(empty);

    action_announce("insert to end of above 5 times value from end of itself");
    empty.insert(empty.end(), 5,  empty[empty.size() - 1]);
    show_vector_info(empty);

    action_announce("insert to begin of above 5 times value from end of itself");
    empty.insert(empty.begin(), 5,  empty[empty.size() - 1]);
    show_vector_info(empty);

    action_announce("insert to end of above 5 times value from begin of itself");
    empty.insert(empty.end(), 5,  empty[0]);
    show_vector_info(empty);
}

void insert_range_test() {

    test_announce("insert range test");
    base_state_announce("42 vector filled with range");
    lib::con<Test> testy(42);
    fill_array_with_123(testy, 0);
    show_vector_info(testy);

    base_state_announce("empty vector");
    lib::con<Test> empty;
    show_vector_info(empty);

    base_state_announce("empty vector with 100 capacity");
    lib::con<Test> empty_cap;
    empty_cap.reserve(1000);
    show_vector_info(empty_cap);

    base_state_announce("10 vector filled with range");
    lib::con<Test> small_testy(10);
    fill_array_with_123(small_testy, 10);

    test_announce("insert range test");

    action_announce("insert to end of empty with range from full and arithmetics");
    empty.insert(empty.end(), testy.begin() + 5, testy.end() - 5);
    show_vector_info(empty);
    show_vector_info(testy);

    action_announce("insert to end of above with range from other");
    testy.insert(testy.end(), small_testy.begin(), small_testy.end());
    show_vector_info(testy);

    action_announce("insert to begin of big cap empty with range from other");
    empty_cap.insert(empty_cap.begin(), small_testy.begin(), small_testy.end());
    show_vector_info(empty_cap);

    test_announce("insert range test");

    action_announce("insert to begin of small with range from itself");
    small_testy.insert(small_testy.begin(), small_testy.begin(), small_testy.end());
    show_vector_info(small_testy);

    action_announce("insert to end of above with range from itself");
    small_testy.insert(small_testy.end(), small_testy.begin(), small_testy.end());
    show_vector_info(small_testy);

    action_announce("insert to end of above with range from itself and arithmetics");
    small_testy.insert(small_testy.end(), small_testy.begin() + 3, small_testy.end() - 3);
    show_vector_info(small_testy);

    action_announce("try to insert to above from incorrect range from itself");
    try {
        small_testy.insert(small_testy.begin(), small_testy.begin() + 5, small_testy.begin());
    } catch(std::exception & e) {
        std::cout << e.what() << std::endl;
    }
    show_vector_info(small_testy);

    action_announce("try to insert to above from incorrect max size iterator from itself");
    try {
        small_testy.insert(small_testy.begin(), small_testy.begin(), (small_testy.begin() + small_testy.max_size()));
    } catch(std::exception & e) {
        std::cout << e.what() << std::endl;
    }
    show_vector_info(small_testy);
}

void erase_test() {
    test_announce("erase test");
    base_state_announce("42 vector filled with range");
    lib::con<Test> testy(42);
    fill_array_with_123(testy, 0);
    show_vector_info(testy);

    base_state_announce("empty vector");
    lib::con<Test> empty;
    show_vector_info(empty);

    test_announce("erase test");

    action_announce("erase the beginning from 42 full vector");
    std::cout << "return value: " << testy.erase(testy.begin())->some_ << std::endl;
    show_vector_info(testy);

    action_announce("erase the end from above");
    if (testy.erase(testy.end() - 1) == testy.end())
        std::cout << "return value is end"<< std::endl;
    show_vector_info(testy);

    action_announce("erase from the 10th element of above");
    std::cout << "return value: " << testy.erase(testy.begin() + 10)->some_ << std::endl;
    show_vector_info(testy);

    test_announce("erase range test (not correct range is ub)");

    action_announce("erase range from above and arithmetics");
    std::cout << "return value: " << testy.erase(testy.begin() + 5, testy.end() - 5)->some_ << std::endl;
    show_vector_info(testy);

    action_announce("erase full range from above");
    if (testy.erase(testy.begin(), testy.end()) == testy.end())
        std::cout << "return value is end"<< std::endl;
    show_vector_info(testy);
}

void clear_test() {
    test_announce("clear test");
    base_state_announce("42 vector filled with range");
    lib::con<Test> testy(42);
    fill_array_with_123(testy, 0);
    show_vector_info(testy);

    base_state_announce("empty vector");
    lib::con<Test> empty;
    show_vector_info(empty);

    base_state_announce("empty vector with 100 capacity");
    lib::con<Test> empty_cap;
    empty_cap.reserve(1000);
    show_vector_info(empty_cap);

    base_state_announce("10 vector filled with range and 100 capacity");
    lib::con<Test> small_testy(10);
    small_testy.reserve(1000);
    fill_array_with_123(small_testy, 10);

    test_announce("clear test");

    action_announce("clear empty");
    empty.clear();
    show_vector_info(empty);

    action_announce("clear big cap empty");
    empty_cap.clear();
    show_vector_info(empty_cap);

    action_announce("clear full");
    testy.clear();
    show_vector_info(testy);

    action_announce("clear big cap full");
    small_testy.clear();
    show_vector_info(small_testy);
}

void relational_operators() {
    test_announce("relational operators test");
    base_state_announce("42 vector filled with sevens");
    lib::con<int> testy(42, 7);

    base_state_announce("empty vector");
    lib::con<int> empty;

    base_state_announce("empty vector with 100 capacity");
    lib::con<int> empty_cap;
    empty_cap.reserve(1000);

    base_state_announce("10 vector filled with sevens and 100 capacity");
    lib::con<int> small_testy(10, 7);
    small_testy.reserve(1000);

    test_announce("relational operators test");

    action_announce("are each of 4 vectors equal to themselves");
    std::cout << (empty     == empty)     << std::endl;
    std::cout << (empty_cap == empty_cap) << std::endl;
    std::cout << (testy     == testy)     << std::endl;
    std::cout << (small_testy == small_testy) << std::endl;

    action_announce("are each of 4 vectors unequal to themselves");
    std::cout << (empty     != empty)     << std::endl;
    std::cout << (empty_cap != empty_cap) << std::endl;
    std::cout << (testy     != testy)     << std::endl;
    std::cout << (small_testy != small_testy) << std::endl;

    action_announce("test >");
    std::cout << "empty > empty cap: " << (empty     > empty_cap)     << std::endl;
    std::cout << "empty_cap > empty: " << (empty_cap > empty) << std::endl;
    std::cout << "testy > testy_cap: "<< (testy     > small_testy)     << std::endl;
    std::cout << "testy_cap > testy: " << (small_testy > testy) << std::endl;

    action_announce("test <");
    std::cout << "empty < empty cap: " << (empty     < empty_cap)     << std::endl;
    std::cout << "empty_cap < empty: " << (empty_cap < empty) << std::endl;
    std::cout << "testy < testy_cap: " << (testy     < small_testy)     << std::endl;
    std::cout << "testy_cap < testy: " << (small_testy < testy) << std::endl;

    action_announce("test >=");
    std::cout << "empty >= empty cap: " << (empty     >= empty_cap)     << std::endl;
    std::cout << "empty_cap >= empty: " << (empty_cap >= empty) << std::endl;
    std::cout << "testy >= testy_cap: " << (testy     >= small_testy)     << std::endl;
    std::cout << "testy_cap >= testy: " << (small_testy >= testy) << std::endl;

    action_announce("test <=");
    std::cout << "empty <= empty cap: " << (empty     <= empty_cap)     << std::endl;
    std::cout << "empty_cap <= empty: " << (empty_cap <= empty) << std::endl;
    std::cout << "testy <= testy_cap: " << (testy     <= small_testy)     << std::endl;
    std::cout << "testy_cap <= testy: " << (small_testy <= testy) << std::endl;
}

void const_iterators() {
    test_announce("const iterators test");
    base_state_announce("42 vector filled with range");
    lib::con<int> testy;
    for (int i = 0; i < 42; ++i) {
        testy.push_back(i);
    }

    base_state_announce("42 const vector filled with range and iterator");
    lib::con<const int>                 const_testy(testy.begin(), testy.end());
    lib::con<const int>::const_iterator const_it = const_testy.begin();

    while (const_it != const_testy.end()) {
        std::cout << *const_it << " ";
        ++const_it;
    }
    --const_it;
    std::cout << std::endl;

    action_announce("compare end it with begin it");
    lib::con<const int>::const_iterator const_it_begin(const_testy.begin());
    std::cout << "comparison > : " << (const_it > const_it_begin) << std::endl;
    std::cout << "comparison >= : " << (const_it >= const_it_begin) << std::endl;
    std::cout << "comparison < : " << (const_it < const_it_begin) << std::endl;
    std::cout << "comparison <= : " << (const_it <= const_it_begin) << std::endl;
    std::cout << "comparison == : " << (const_it == const_it_begin) << std::endl;
    std::cout << "difference: " << (const_it - const_it_begin) << std::endl;
    std::cout << "it_begin + 1: " << *(const_it_begin + 1) << std::endl;
    std::cout << "1 + it_begin: " << *(1 + const_it_begin) << std::endl;
    std::cout << "++it_begin: " << *(++const_it_begin) << std::endl;
    std::cout << "--it_begin: " << *(--const_it_begin) << std::endl;

    action_announce("test const reverse iterator from non const vector");
    lib::con<int>::const_iterator abominashion(testy.begin());
    while (abominashion != testy.end()) {
        std::cout << *abominashion << " ";
        ++abominashion;
    }
    std::cout << std::endl;
}

void reverse_iterators() {
    test_announce("reverse iterators test");
    base_state_announce("42 vector filled with range");
    lib::con<int> testy;
    for (int i = 0; i < 42; ++i) {
        testy.push_back(i);
    }

    base_state_announce("42 const vector filled with range and reverse iterator");
    lib::con<const int>                 const_testy(testy.begin(), testy.end());
    lib::con<const int>::const_reverse_iterator const_it = const_testy.rbegin();

    while (const_it != const_testy.rend()) {
        std::cout << *const_it << " ";
        ++const_it;
    }
    --const_it;
    std::cout << std::endl;

    action_announce("compare end it with begin it but now reverse");
    lib::con<const int>::const_reverse_iterator const_it_begin(const_testy.rbegin());
    std::cout << "comparison > : " << (const_it > const_it_begin) << std::endl;
    std::cout << "comparison >= : " << (const_it >= const_it_begin) << std::endl;
    std::cout << "comparison < : " << (const_it < const_it_begin) << std::endl;
    std::cout << "comparison <= : " << (const_it <= const_it_begin) << std::endl;
    std::cout << "comparison == : " << (const_it == const_it_begin) << std::endl;
    std::cout << "difference: " << (const_it - const_it_begin) << std::endl;
    std::cout << "it_begin + 1: " << *(const_it_begin + 1) << std::endl;
    std::cout << "1 + it_begin: " << *(1 + const_it_begin) << std::endl;
    std::cout << "++it_begin: " << *(++const_it_begin) << std::endl;
    std::cout << "--it_begin: " << *(--const_it_begin) << std::endl;

    action_announce("test const iterator from non const vector");
    lib::con<int>::const_reverse_iterator abominashion(testy.rbegin());
    while (abominashion != testy.rend()) {
        std::cout << *abominashion << " ";
        ++abominashion;
    }
}

void vector_relational_operators() {
    test_announce("vector relational operators test");

    base_state_announce("two vectors: big and small");
    lib::con<int> big;
    for (int i = 0; i < 42; ++i) {
        big.push_back(i);
    }
    for (size_t i = 0; i < big.size(); ++i) {
        std::cout << big[i] << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;

    lib::con<int> small;
    for (size_t i = 0; i < small.size(); ++i) {
        small.push_back(i);
    }
    for (size_t i = 0; i < big.size(); ++i) {
        std::cout << big[i] << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;

    test_announce("vector relational operators test");

    action_announce("test comparison between vectors,  first is big, second is small");
    std::cout << "test operator > : " << (big >  small) << std::endl;
    std::cout << "test operator >= : " << (big >= small) << std::endl;
    std::cout << "test operator < : " << (big <  small) << std::endl;
    std::cout << "test operator <= : " << (big <= small) << std::endl;
    std::cout << "test operator == : " << (big == small) << std::endl;
    std::cout << "test operator != : " << (big != small) << std::endl;
}

void const_vs_non_const_it() {
    test_announce("const and non const iterators comparison");
    base_state_announce("two vectors and two end iterators: bigger non const and smaller const");
    lib::con<int> non;
    for (size_t i = 0; i < 42; ++i) {
        non.push_back(2);
    }
    for (size_t i = 0; i < 42; ++i) {
        std::cout << non[i] << "  ";
    }
    std::cout << std::endl;
    std::cout << std::endl;

    lib::con<int> small;
    for (size_t i = 0; i < 10; ++i) {
        small.push_back(2);
    }
    for (size_t i = 0; i < 10; ++i) {
        std::cout << small[i] << "  ";
    }
    std::cout << std::endl;

    lib::con<int>::iterator       nonconst_it(non.end() - 1);
    lib::con<int>::const_iterator const_it(small.end() - 1);

    test_announce("const and non const iterators comparison");

    action_announce("test comparison between vectors, first is big non const, second is small const");
    if (nonconst_it >  const_it || nonconst_it <= const_it)
        if (nonconst_it >= const_it || nonconst_it <  const_it)
            if (nonconst_it == const_it || nonconst_it != const_it)
                std::cout << "successfully compiled " << std::endl;

    action_announce("now same thing but reverse iterators end rbegin");
    lib::con<int>::reverse_iterator       nonconst_rev = non.rbegin();
    lib::con<int>::const_reverse_iterator const_rev = small.rbegin();

    if ((const_rev >  nonconst_rev) || (const_rev <= nonconst_rev))
        if ((const_rev <  nonconst_rev) || (const_rev >= nonconst_rev))
            if ((const_rev == nonconst_rev) || (const_rev != nonconst_rev))
                std::cout << "successfully compiled " << std::endl;
}

void stack_test() {
//    test_announce("stack test");
//    base_state_announce("deq vector with 10 range, my Vector with 42 range, stacks based on it");
//    std::deque<int> deq(10, 7);
//    for (size_t i = 0; i < 10; ++i) {
//        deq.push_back(i);
//    }
//
//    lib::con<int> testy(42, 42);
//    for (size_t i = 0; i < 42; ++i) {
//        testy.push_back(i);
//    }
//
//    test_announce("stack test");
//
//    action_announce("stack initialization with deque and top - pop cycle");
//    lib::sta<int, std::deque<int> > deq_stack(deq);
//    for (size_t i = 0; i < 10; ++i) {
//        std::cout << deq_stack.top() << " ";
//        deq_stack.pop();
//    }
//    std::cout << std::endl;
//    std::cout << std::endl;
//
//    action_announce("stack initialization with vector and top - pop cycle");
//    lib::sta<int> vec_stack(testy);
//    for (size_t i = 0; i < 42; ++i) {
//        std::cout << vec_stack.top() << " ";
//        vec_stack.pop();
//    }
//
//    action_announce("empty on empty container and then with push");
//    lib::con<int> empty;
//    lib::sta<int> empty_stack(empty);
//    if (empty_stack.empty())
//        std::cout << "Initialize empty." << std::endl;
//    action_announce("push back to empty stack and check");
//    empty_stack.push(1);
//    if (!empty_stack.empty())
//        std::cout << "is not empty" << std::endl;
}

void map_construction_test() {
    test_announce("Map construction test");
    action_announce("default constructed Map");
    lib::coma<int, Test> testy;
    balancly_fill_map_with_range(testy, 10);
    print_map_info<int, Test>(testy);

    action_announce("assign_node_no_value constructed Map");
    lib::coma<int, Test> copy(testy);
    print_map_info<int, Test>(copy);

    action_announce("range constructed Map from 1 to 9");
    lib::coma<int, Test> range(++testy.begin(), --testy.end());
    print_map_info<int, Test>(range);

}

void map_iterator_test () {
    test_announce("Map iterator test");
    base_state_announce("Map with 10 range");
    lib::coma<int, Test> testy;
    lib::coma<const int, const Test> const_testy;
    balancly_fill_map_with_range(testy, 10);
    print_map_info<int, Test>(testy);

    action_announce("create begin and --end iterators, show them");
    lib::coma<int, Test>::iterator it(testy.begin());
    lib::coma<int, Test>::iterator end(testy.end());
    --end;
    show_map_iterator(it);
    show_map_iterator(end);
    action_announce("++begin and show via *");
    ++it;
    show_map_iterator(it);
    std::cout << "show via -> : " << it->first << std::endl;

    action_announce("comparison of iterators equal and unequal to themselves");
    if (it == it)
        std::cout << "it == it" << std::endl;
    if (!(it != it))
        std::cout << "!(it != it)" << std::endl;

    test_announce("Map const iterator test");

    action_announce("take begin const from non const and show it");
    lib::coma<const int, const Test>::const_iterator abominashion(const_testy.begin());
    std::cout << "show key via -> : " << abominashion->first << std::endl;
    std::cout << "show value via * : " << (*abominashion).second.some_ << std::endl;

    action_announce("arithmetics and comparison but now const");
    ++abominashion;
    std::cout << "show key after ++ : " << abominashion->first << std::endl;
    --abominashion;
    std::cout << "show key after -- : " << abominashion->first << std::endl;
    if (abominashion == abominashion)
        std::cout << "const == const" << std::endl;
    if (!(abominashion != abominashion))
        std::cout << "!(const != const)" << std::endl;

    test_announce("Map reverse iterator test");

    action_announce("create reverse begin and reverse --end iterators, show them");
    lib::coma<int, Test>::reverse_iterator reverse_it(testy.rbegin());
    lib::coma<int, Test>::reverse_iterator reverse_end(testy.rend());
    --reverse_end;
    std::cout << "show begin key via -> : " << reverse_it->first << std::endl;
    std::cout << "show begin value via * : " << (*reverse_it).second.some_ << std::endl;
    std::cout << "show end key via -> : " << reverse_end->first << std::endl;
    std::cout << "show end value via * : " << (*reverse_end).second.some_ << std::endl;
    action_announce("reverse ++begin and show");
    ++reverse_it;
    std::cout << "show key via -> : " << reverse_it->first << std::endl;
    std::cout << "show value via * : " << (*reverse_it).second.some_ << std::endl;

    action_announce("comparison of reverse iterators equal and unequal to themselves");
    if (reverse_it == reverse_it)
        std::cout << "reverse_it == reverse_it" << std::endl;
    if (!(reverse_it != reverse_it))
        std::cout << "!(reverse_it != reverse_it)" << std::endl;

    test_announce("Map const reverse iterator test");

    action_announce("take const reverse from non const reverse and show it");
    lib::coma<int, Test>::const_reverse_iterator reverse_abominashion(testy.rbegin());
    std::cout << "show key via -> : " << reverse_abominashion->first << std::endl;
    std::cout << "show value via * : " << (*reverse_abominashion).second.some_ << std::endl;

    action_announce("arithmetics and comparison but now const reverse");
    ++reverse_abominashion;
    std::cout << "show key after ++ : " << reverse_abominashion->first << std::endl;
    --reverse_abominashion;
    std::cout << "show key after -- : " << reverse_abominashion->first << std::endl;
    if (reverse_abominashion == reverse_abominashion)
        std::cout << "reverse_const == reverse_const" << std::endl;
    if (!(reverse_abominashion != reverse_abominashion))
        std::cout << "!(reverse_const != reverse_const)" << std::endl;
}

void map_small_stuff_test() {
    test_announce("Map small stuff test");
    base_state_announce("Map with 10 range");
    lib::coma<int, Test> testy;
    balancly_fill_map_with_range(testy, 10);
    print_map_info<int, Test>(testy);

    base_state_announce("Map with 15 range");
    lib::coma<int, Test> small_testy;
    balancly_fill_map_with_range(small_testy, 15);
    print_map_info<int, Test>(small_testy);

    action_announce("swap full and big");
    testy.swap(small_testy);
    print_map_info<int, Test>(testy);
    print_map_info<int, Test>(small_testy);

    action_announce("swap again with std swap(x, y)");
    std::swap(testy, small_testy);
    print_map_info<int, Test>(testy);
    print_map_info<int, Test>(small_testy);

    action_announce("compare keys with key compare from full");
    std::cout << "is 1 less then 2 bool: " << testy.key_comp()(1, 2) << std::endl;

    action_announce("compare values with value compare from full");
    lib::coma<int, Test>::value_compare  comp = testy.value_comp();
    std::cout << "is pair(1, test(1)) less then pair(1, test(1))  bool: " <<
    comp(lib::pair<int, Test>(1, Test(1)), lib::pair<int, Test>(1, Test(1))) << std::endl;

    test_announce("Map small stuff test");

    action_announce("max size");
    std::cout << "max size: " << testy.max_size() << std::endl;

    action_announce("[] operator test with existing element");
    std::cout << "return from [2]: " << testy[2].some_ << std::endl;
    print_map_info<int, Test>(testy);

    action_announce("[] operator test with not existing element");
    std::cout << "return from [102]: " << testy[102].some_ << std::endl;
    print_map_info<int, Test>(testy);

    action_announce("at with existing element");
    std::cout << "return from at 2: " << testy.at(2).some_ << std::endl;

    action_announce("at with not existing element");
    try {
        testy.at(1000);

    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    print_map_info<int, Test>(testy);
}

void map_insert_test() {
    test_announce("Map insert test");
    base_state_announce("Map with 10 range");
    lib::coma<int, Test> testy;
    balancly_fill_map_with_range(testy, 10);
    print_map_info<int, Test>(testy);

    base_state_announce("Map with 15 range");
    lib::coma<int, Test> small_testy;
    balancly_fill_map_with_range(small_testy, 15);
    print_map_info<int, Test>(small_testy);

    base_state_announce("empty Map");
    lib::coma<int, Test> empty;
    lib::coma<int, Test> empty2;
    print_map_info<int, Test>(empty);

    lib::pair<lib::coma<int, Test>::iterator, bool> tmp;
    action_announce("insert 42 val to empty");
    tmp = empty.insert(lib::pair<int, Test>(42, 42));
    print_map_info<int, Test>(empty);
    std::cout << "return iterator key: " << tmp.first->first << std::endl;
    std::cout << "return iterator value: " << tmp.first->second.some_ << std::endl;
    std::cout << "return bool: " << tmp.second << std::endl;

    action_announce("insert existing 7 val to full");
    tmp = testy.insert(lib::pair<int, Test>(7, 7));
    print_map_info<int, Test>(testy);
    std::cout << "return iterator key: " << tmp.first->first << std::endl;
    std::cout << "return iterator value: " << tmp.first->second.some_ << std::endl;
    std::cout << "return bool: " << tmp.second << std::endl;

    action_announce("insert non existing 42 val to full");
    tmp = testy.insert(lib::pair<int, Test>(42, 42));
    print_map_info<int, Test>(testy);
    std::cout << "return iterator key: " << tmp.first->first << std::endl;
    std::cout << "return iterator value: " << tmp.first->second.some_ << std::endl;
    std::cout << "return bool: " << tmp.second << std::endl;

    action_announce("insert range from bigger (15) to above");
    testy.insert(small_testy.begin(), small_testy.end());
    print_map_info<int, Test>(testy);

    action_announce("insert existing 42 with right_ position to above");
    std::cout << "return: " << testy.insert(--testy.end(), lib::pair<int, Test>(42, 42))->first <<std::endl;
    print_map_info<int, Test>(testy);

    action_announce("insert not existing 21 with wrong position to above");
    std::cout << "return: " << testy.insert(--testy.end(), lib::pair<int, Test>(21, 21))->first <<std::endl;
    print_map_info<int, Test>(testy);

    action_announce("insert not existing 43 with right_ position to above");
    std::cout << "return: " << testy.insert(--testy.end(), lib::pair<int, Test>(43, 43))->first <<std::endl;
    print_map_info<int, Test>(testy);

    action_announce("insert 42 with position to empty");
    std::cout << "return: " << empty2.insert(empty2.begin(), lib::pair<int, Test>(42, 42))->first <<std::endl;
    print_map_info<int, Test>(empty2);
}

void map_erase_test() {
    test_announce("Map erase test");
    base_state_announce("Map with 10 range");
    lib::coma<int, Test> testy;
    balancly_fill_map_with_range(testy, 10);
    print_map_info<int, Test>(testy);

    base_state_announce("Map with 15 range");
    lib::coma<int, Test> small_testy;
    balancly_fill_map_with_range(small_testy, 15);
    print_map_info<int, Test>(small_testy);

    base_state_announce("empty Map");
    lib::coma<int, Test> empty;
    print_map_info<int, Test>(empty);

    action_announce("erase ++begin from full 10");
    testy.erase(++testy.begin());
    print_map_info<int, Test>(testy);

    action_announce("erase not existing 2 key from above");
    testy.erase(2);
    print_map_info<int, Test>(testy);

    test_announce("Map erase test");

    action_announce("erase existing 7 key from above");
    testy.erase(7);
    print_map_info<int, Test>(testy);

    action_announce("erase range from ++begin to --end from above");
    testy.erase(++testy.begin(), --testy.end());
    print_map_info<int, Test>(testy);

    action_announce("erase full range from empty");
    empty.erase(empty.begin(), empty.end());
    print_map_info<int, Test>(empty);

    action_announce("erase full range from full 15");
    small_testy.erase(small_testy.begin(), small_testy.end());
    print_map_info<int, Test>(small_testy);
}

void map_operations_test() {

    test_announce("Map operations test");
    base_state_announce("Map with 10 range");
    lib::coma<int, Test> testy;
    balancly_fill_map_with_range(testy, 10);
    print_map_info<int, Test>(testy);

    base_state_announce("empty Map");
    lib::coma<int, Test> empty;
    print_map_info<int, Test>(empty);

    lib::coma<int, Test>::iterator it;
    lib::coma<int, Test>::const_iterator const_it;

    action_announce("find key 5 in 10 map and show iterator and next after it");
    it = testy.find(5);
    show_map_iterator(it);
    show_map_iterator(++it);

    action_announce("same but now const");
    const_it = testy.find(5);
    std::cout << "iterator key: " << const_it->first << std::endl;
    std::cout << "++iterator key: " << (++const_it)->first << std::endl;

    action_announce("find not existing key 42 in 10 map and show --it from its return");
    it = testy.find(42);
    show_map_iterator(--it);

    action_announce("find existing key 5 in 10 map and show the return");
    std::cout << testy.count(5) << std::endl;

    action_announce("find not existing key 42 in 10 map and show the return");
    std::cout << testy.count(42) << std::endl;

    action_announce("show lower and upper bound and equal range iterators for existing 5 key");
    std::cout << "lower bound: ";
    show_map_iterator(testy.lower_bound(5));
    std::cout << "upper bound: ";
    show_map_iterator(testy.upper_bound(5));
    std::cout << "equal range: ";
    std::cout << "lower bound: ";
    show_map_iterator(testy.equal_range(5).first);
    std::cout << "upper bound: ";
    show_map_iterator(testy.equal_range(5).second);

    action_announce("same but now const");
    const_it = testy.lower_bound(5);
    std::cout << "lower bound: ";
    std::cout << "iterator key: " << const_it->first << std::endl;
    const_it = testy.upper_bound(5);
    std::cout << "upper bound: ";
    std::cout << "iterator key: " << const_it->first << std::endl;
    std::cout << "equal range: ";
    std::cout << "lower bound: ";
    const_it = testy.equal_range(5).first;
    std::cout << "iterator key: " << const_it->first << std::endl;
    std::cout << "upper bound: ";
    const_it = testy.equal_range(5).second;
    std::cout << "iterator key: " << const_it->first << std::endl;

    action_announce("show lower and upper bound and equal range --iterators for not existing 42 key");
    std::cout << "lower bound: ";
    show_map_iterator(--testy.lower_bound(42));
    std::cout << "upper bound: ";
    show_map_iterator(--testy.upper_bound(42));
    std::cout << "equal range: ";
    std::cout << "lower bound: ";
    show_map_iterator(--testy.equal_range(42).first);
    std::cout << "upper bound: ";
    show_map_iterator(--testy.equal_range(42).second);
}

void map_relational_operators() {
    test_announce("map relational operators test");

    base_state_announce("Map with 10 range");
    lib::coma<int, Test> testy;
    balancly_fill_map_with_range(testy, 10);
    print_map_info<int, Test>(testy);

    base_state_announce("Map with 15 range (testy big)");
    lib::coma<int, Test> small_testy;
    balancly_fill_map_with_range(small_testy, 15);
    print_map_info<int, Test>(small_testy);

    base_state_announce("empty Map");
    lib::coma<int, Test> empty;
    print_map_info<int, Test>(empty);


    test_announce("relational operators test");

    action_announce("are each of 3 vectors equal to themselves");
    std::cout << (empty     == empty)     << std::endl;
    std::cout << (testy     == testy)     << std::endl;
    std::cout << (small_testy == small_testy) << std::endl;

    action_announce("are each of 3 vectors unequal to themselves");
    std::cout << (empty     != empty)     << std::endl;
    std::cout << (testy     != testy)     << std::endl;
    std::cout << (small_testy != small_testy) << std::endl;

    action_announce("test >");
    std::cout << "empty > empty cap: " << (empty > empty) << std::endl;
    std::cout << "testy > testy_big: "<< (testy     > small_testy)     << std::endl;
    std::cout << "testy_big > testy: " << (small_testy > testy) << std::endl;

    action_announce("test <");
    std::cout << "empty < empty: " << (empty < empty) << std::endl;
    std::cout << "testy < testy_big: " << (testy     < small_testy)     << std::endl;
    std::cout << "testy_big < testy: " << (small_testy < testy) << std::endl;

    action_announce("test >=");
    std::cout << "empty >= empty: " << (empty >=empty) << std::endl;
    std::cout << "testy >= testy_big: " << (testy     >= small_testy)     << std::endl;
    std::cout << "testy_big >= testy: " << (small_testy >= testy) << std::endl;

    action_announce("test <=");
    std::cout << "empty <= empty: " << (empty <=empty) << std::endl;
    std::cout << "testy <= testy_big: " << (testy     <= small_testy)     << std::endl;
    std::cout << "testy_big <= testy: " << (small_testy <= testy) << std::endl;

}

// =============================================================================

int main(void)
{
// ==============================vector==========================================
    construction_tests();
    operator_assignment();
    iterator_test();
    element_access_test();
    assign_range_test();
    assign_fill_test();
    push_back_test();
    small_stuff_test();
    insert_val_test();
    insert_fill_test();
    insert_range_test();
    erase_test();
    clear_test();
    relational_operators();

    const_iterators();
    reverse_iterators();
    vector_relational_operators();
    const_vs_non_const_it();
// =================================stack=======================================
//    stack_test();
// =================================map=========================================
    test_announce("Map tests");

    map_construction_test();
    map_iterator_test();
    map_small_stuff_test();
    map_insert_test();
    map_erase_test();
    map_operations_test();
    map_relational_operators();
    return 0;
}