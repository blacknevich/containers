#include <iostream>
#include <vector>
#include <cstddef> // size_t , ?ptrdiff_t
#include <limits> // ?numeric_limit=
#include "ft_vector.hpp"

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
        this->str_ = (char*)malloc(10);
    }

    Test(Test const & x) : some_(x.some_) {
//         std::cout << "Copy Test " << this->some_ << " created" << std::endl;
        this->str_ = (char*)malloc(10);
    }

    ~Test() {
        if (this->str_ != 0)
            free(this->str_);
        this->some_ = 0;
        this->str_  = 0;
//         std::cout << "Test deleted" << std::endl;
    }

    Test &operator=(Test const & x) {
//         std::cout << "Test operator =" << std::endl;
        if (this == &x)
            return (*this);
        this->str_ = (char*)malloc(10);
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
        this->str_ = (char*)malloc(10);
    }

    Test_loud(int s) : some_(s) {
         std::cout << "Test_loud " << this->some_ << " created" << std::endl;
        this->str_ = (char*)malloc(10);
    }

    Test_loud(Test_loud const & x) : some_(x.some_) {
         std::cout << "Copy Test_loud " << this->some_ << " created" << std::endl;
        this->str_ = (char*)malloc(10);
    }

    ~Test_loud() {
        if (this->str_ != 0)
            free(this->str_);
        this->some_ = 0;
        this->str_  = 0;
         std::cout << "Test_loud deleted" << std::endl;
    }

    Test_loud &operator=(Test_loud const & x) {
         std::cout << "Test_loud operator =" << std::endl;
        if (this == &x)
            return (*this);
        this->str_ = (char*)malloc(10);
        this->some_ = x.some_;
        return (*this);
    }

    int   some_;
    char* str_;

};

//vnstr
// Constructors ================================================================

    void ft_defoult_constructor() {
        std::cout << "\ndefoult_constructor\n" << std::endl;
        lib::con<Test> useless;

        std::cout << "empty() : " << useless.empty()    << std::endl;
        std::cout << "size    : " << useless.size()     << std::endl;
        std::cout << "capacity: " << useless.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < useless.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << useless[i].some_ << " ";
        }
        std::cout << std::endl;
    }

    void ft_n_constructor() {
        std::cout << "\nn_constructor\n" << std::endl;
        Test tmp(42);
        std::cout << "my" << std::endl;
        lib::con<Test> useless(3, tmp);
        std::cout << "etalon" << std::endl;
        std::vector<Test> etalon_useless(3, tmp);
        for (size_t i = 0; i < useless.size(); ++i) {
            useless[i].some_ = i;
        }

        std::cout << "empty() : " << useless.empty()    << std::endl;
        std::cout << "size    : " << useless.size()     << std::endl;
        std::cout << "capacity: " << useless.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < useless.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << useless[i].some_ << " ";
        }
        std::cout << std::endl;
    }

    void ft_n_val_constructor() {
        std::cout << "\nn_val_constructor\n" << std::endl;
        lib::con<Test> useless(3, 2);

        std::cout << "size    : " << useless.size()     << std::endl;
        std::cout << "capacity: " << useless.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < useless.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << useless[i].some_ << " ";
        }
        std::cout << std::endl;

    }

    void ft_copy_constructor() {
        std::cout << "\ncopy_constructor\n" << std::endl;
        lib::con<Test> base(1, 12);
        for (size_t i = 0; i < base.size(); ++i) {
            //base[i].some_ = i;
            std::cout << base[i].some_ << std::endl;
        }

        lib::con<Test> copy(base);

        std::cout << "size    : " << copy.size()     << std::endl;
        std::cout << "capacity: " << copy.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < copy.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << copy[i].some_ << " ";
        }
        std::cout << std::endl;

        std::vector<Test> base_etalon(1, 12);
        for (size_t i = 0; i < base_etalon.size(); ++i) {
            //base_etalon[i].some_ = i;
            std::cout << base_etalon[i].some_ << std::endl;
        }

        std::vector<Test> copy_etalon(base_etalon);

        std::cout << "size    : " << copy_etalon.size()     << std::endl;
        std::cout << "capacity: " << copy_etalon.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < copy_etalon.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << copy_etalon[i].some_ << " ";
        }
        std::cout << std::endl;
    }

    void ft_resize_test() {
        std::cout << "\nresize_test\n" << std::endl;
        std::vector<Test> etalon(128);
        std::cout << "etalon size: " << etalon.size() << std::endl;
        etalon.resize(256, 7);
        for (size_t i = 0; i < etalon.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << etalon[i].some_ << " ";
        }

        std::cout << std::endl;
        lib::con<Test> mouse(128);
        std::cout << "mouse size: " << mouse.size() << std::endl;
        for (size_t i = 0; i < mouse.size(); ++i) {
            mouse[i].some_ = i;
        }
        for (size_t i = 0; i < etalon.size(); ++i) {
            etalon[i].some_ = i;
        }
        lib::con<Test> big_empty(mouse);
        lib::con<Test> small_mouse(mouse);
        lib::con<Test> big_mouse(mouse);

        std::cout << "size    : " << mouse.size()     << std::endl;
        std::cout << "capacity: " << mouse.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < mouse.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << mouse[i].some_ << " ";
        }
        std::cout << std::endl;
        std::cout << (*mouse.begin()).some_      << std::endl;
        std::cout << (*etalon.begin()).some_      << std::endl;
        std::cout << (*(mouse.end() - 1)).some_  << std::endl;
        std::cout << (*(etalon.end() - 1)).some_  << std::endl;
        std::cout << (*mouse.rbegin()).some_     << std::endl;
        std::cout << (*etalon.rbegin()).some_     << std::endl;
        std::cout << std::endl;
        std::cout << (*(mouse.rend() - 1 )).some_ << std::endl;
        std::cout << (*(etalon.rend() - 1)).some_ << std::endl;

        big_empty.resize(64, 7);
        std::cout << "size    : " << big_empty.size()     << std::endl;
        std::cout << "capacity: " << big_empty.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < big_empty.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << big_empty[i].some_ << " ";
        }
        std::cout << std::endl;

        small_mouse.resize(64, 7);
        std::cout << "size    : " << small_mouse.size()     << std::endl;
        std::cout << "capacity: " << small_mouse.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < small_mouse.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << small_mouse[i].some_ << " ";
        }
        std::cout << std::endl;

        small_mouse.resize(1, 7);
        std::cout << "size    : " << small_mouse.size()     << std::endl;
        std::cout << "capacity: " << small_mouse.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < small_mouse.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << small_mouse[i].some_ << " ";
        }
        std::cout << std::endl;

        small_mouse.resize(0, 7);
        std::cout << "size    : " << small_mouse.size()     << std::endl;
        std::cout << "capacity: " << small_mouse.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < small_mouse.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << small_mouse[i].some_ << " ";
        }
        std::cout << std::endl;

        big_mouse.resize(256, 7);
        std::cout << "size    : " << big_mouse.size()     << std::endl;
        std::cout << "capacity: " << big_mouse.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < big_mouse.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << big_mouse[i].some_ << " ";
        }
        std::cout << std::endl;

        try {
            big_mouse.resize(big_mouse.max_size() + 10);

        } catch(std::exception & e) {
            std::cout << e.what() << std::endl;
        }

        std::cout << "size    : " << big_mouse.size()     << std::endl;
        std::cout << "capacity: " << big_mouse.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < big_mouse.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << big_mouse[i].some_ << " ";
        }
        std::cout << std::endl;
    }

    void ft_reserve_test() {
        std::cout << "\nreserve_test\n" << std::endl;
        lib::con<Test> mouse(128);
        lib::con<Test> empty;
        for (size_t i = 0; i < mouse.size(); ++i) {
            mouse[i].some_ = i;
        }

//        std::cout << "size    : " << mouse.size()     << std::endl;
//        std::cout << "capacity: " << mouse.capacity() << std::endl;
//        std::cout << "arr     :" << std::endl;
//        for (size_t i = 0; i < mouse.size(); ++i) {
//            if (i != 0 && i % 32 == 0)
//                std::cout << std::endl;
//            std::cout << mouse[i].some_ << " ";
//        }
//        std::cout << std::endl;
//
//        std::cout << "size    : " << empty.size()     << std::endl;
//        std::cout << "capacity: " << empty.capacity() << std::endl;
//        std::cout << "arr     :" << std::endl;
//        for (size_t i = 0; i < empty.size(); ++i) {
//            if (i != 0 && i % 32 == 0)
//                std::cout << std::endl;
//            std::cout << empty[i].some_ << " ";
//        }
//        std::cout << std::endl;
//
//        mouse.reserve(0);
//        empty.reserve(0);
//
//        std::cout << "size    : " << mouse.size()     << std::endl;
//        std::cout << "capacity: " << mouse.capacity() << std::endl;
//        std::cout << "arr     :" << std::endl;
//        for (size_t i = 0; i < mouse.size(); ++i) {
//            if (i != 0 && i % 32 == 0)
//                std::cout << std::endl;
//            std::cout << mouse[i].some_ << " ";
//        }
//        std::cout << std::endl;
//
//        std::cout << "size    : " << empty.size()     << std::endl;
//        std::cout << "capacity: " << empty.capacity() << std::endl;
//        std::cout << "arr     :" << std::endl;
//        for (size_t i = 0; i < empty.size(); ++i) {
//            if (i != 0 && i % 32 == 0)
//                std::cout << std::endl;
//            std::cout << empty[i].some_ << " ";
//        }
//        std::cout << std::endl;
//
//        mouse.reserve(42);
//        empty.reserve(42);
//
//        std::cout << "size    : " << mouse.size()     << std::endl;
//        std::cout << "capacity: " << mouse.capacity() << std::endl;
//        std::cout << "arr     :" << std::endl;
//        for (size_t i = 0; i < mouse.size(); ++i) {
//            if (i != 0 && i % 32 == 0)
//                std::cout << std::endl;
//            std::cout << mouse[i].some_ << " ";
//        }
//        std::cout << std::endl;

//        std::cout << "size    : " << empty.size()     << std::endl;
//        std::cout << "capacity: " << empty.capacity() << std::endl;
//        std::cout << "arr     :" << std::endl;
//        for (size_t i = 0; i < empty.size(); ++i) {
//            if (i != 0 && i % 32 == 0)
//                std::cout << std::endl;
//            std::cout << empty[i].some_ << " ";
//        }
//        std::cout << std::endl;

//        mouse.reserve(256);

        std::cout << "size    : " << mouse.size()     << std::endl;
        std::cout << "capacity: " << mouse.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < mouse.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << mouse[i].some_ << " ";
        }
        std::cout << std::endl;

        try {
            mouse.reserve(mouse.max_size() + 10);

        } catch(std::exception & e) {
            std::cout << e.what() << std::endl;
        }

        std::cout << "size    : " << mouse.size()     << std::endl;
        std::cout << "capacity: " << mouse.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < mouse.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << mouse[i].some_ << " ";
        }
        std::cout << std::endl;

        std::cout << "size    : " << empty.size()     << std::endl;
        std::cout << "capacity: " << empty.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < empty.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << empty[i].some_ << " ";
        }
        std::cout << std::endl;


    }

    void ft_constructors_capacity_test() {
//        ft_defoult_constructor();
//        ft_n_constructor();
//        ft_n_val_constructor();
//        ft_copy_constructor();
//        ft_resize_test();
//        ft_reserve_test();
    }

// =============================================================================

// Operator '=' ================================================================

void ft_operator_const_assignment() {
    std::cout << "\noperator_constr_assignment\n" << std::endl;

    lib::con<Test_loud> base(2, 2);
    for (size_t i = 0; i < base.size(); ++i) {
        base[i].some_ = i;
    }
    lib::con<Test_loud> base_less(1, 1);
    std::cout << "==assign''" << std::endl;
    base_less = base;
    std::cout << "size    : " << base_less.size()     << std::endl;
    std::cout << "capacity: " << base_less.capacity() << std::endl;
    std::cout << "arr     :" << std::endl;
    for (size_t i = 0; i < base_less.size(); ++i) {
        if (i != 0 && i % 32 == 0)
            std::cout << std::endl;
        std::cout << base_less[i].some_ << " ";
    }
    std::cout << std::endl;

    std::cout << "============etalon'''''''''" << std::endl;
    std::vector<Test_loud> base_etalon(2, 2);
    for (size_t i = 0; i < base_etalon.size(); ++i) {
        base_etalon[i].some_ = i;
    }
    std::vector<Test_loud> base_etalon_less(1, 1);
    std::cout << "==assign''" << std::endl;
    base_etalon_less = base_etalon;
    std::cout << "size    : " << base_etalon_less.size()     << std::endl;
    std::cout << "capacity: " << base_etalon_less.capacity() << std::endl;
    std::cout << "arr     :" << std::endl;
    for (size_t i = 0; i < base_etalon_less.size(); ++i) {
        if (i != 0 && i % 32 == 0)
            std::cout << std::endl;
        std::cout << base_etalon_less[i].some_ << " ";
    }
    std::cout << std::endl;
}

void ft_operator_assignment() {
    std::cout << "\noperator_assignment\n" << std::endl;

        lib::con<Test> base(128);
        for (size_t i = 0; i < base.size(); ++i) {
            base[i].some_ = i;
        }

        lib::con<Test> copy;
        copy = base;

        std::cout << "size    : " << copy.size()     << std::endl;
        std::cout << "capacity: " << copy.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < copy.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << copy[i].some_ << " ";
        }
        std::cout << std::endl;

        base.resize(192, 7);
        copy.reserve(266);
        copy = base;

        std::cout << "size    : " << copy.size()     << std::endl;
        std::cout << "capacity: " << copy.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < copy.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << copy[i].some_ << " ";
        }
        std::cout << std::endl;
    }

// =============================================================================

// Iterators ===================================================================

    void ft_iterator_test() {
        std::cout << "\niterator_test\n" << std::endl;
        lib::con<Test> mouse(128);
        for (size_t i = 0; i < mouse.size(); ++i) {
            mouse[i].some_ = i;
        }

        std::cout << "size    : " << mouse.size()     << std::endl;
        std::cout << "capacity: " << mouse.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < mouse.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << mouse[i].some_ << " ";
        }
        std::cout << std::endl;
        std::cout << (*mouse.begin()).some_      << std::endl;
        std::cout << (*(mouse.end() - 1)).some_  << std::endl;
        std::cout << (*mouse.rbegin()).some_     << std::endl;
        std::cout << (*(mouse.rend() - 1)).some_ << std::endl;
    }

// =============================================================================

// Element access ==============================================================

    void ft_el_access_test() {
        std::cout << "\nel_access_test\n" << std::endl;
        lib::con<Test> one(1, 2);
        lib::con<Test> mouse(128);
        for (size_t i = 0; i < mouse.size(); ++i) {
            mouse[i].some_ = i;
        }

        std::cout << "size    : " << mouse.size()     << std::endl;
        std::cout << "capacity: " << mouse.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < mouse.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << mouse.at(i).some_ << " ";
        }
        std::cout << std::endl;

        try {
            std::cout << mouse.at(1042).some_ << std::endl;

        } catch(std::exception & e) {
            std::cout << e.what() << std::endl;
        }

        std::cout << one.front().some_   << std::endl;
        std::cout << mouse.front().some_ << std::endl;

        std::cout << one.back().some_   << std::endl;
        std::cout << mouse.back().some_ << std::endl;
    }

// =============================================================================

// Modifiers ===================================================================

    void ft_assign_iter_iter_leaks_test() {
        std::cout << "\nassign_iter_iter\n" << std::endl;
        lib::con<Test> mouse(128);
        lib::con<Test> empty;
        lib::con<Test> empty2;
        empty2.reserve(1023);
        for (size_t i = 0; i < mouse.size(); ++i) {
            mouse[i].some_ = i;
        }
        lib::con<Test> fat_mouse(344);
        for (size_t i = 0; i < fat_mouse.size(); ++i) {
            fat_mouse[i].some_ = i + 1000;
        }

        lib::con<Test> small_mouse(5);
        for (size_t i = 0; i < small_mouse.size(); ++i) {
            small_mouse[i].some_ = i + 500;
        }

        empty.assign(mouse.begin() + 5, mouse.end() - 5);

        std::cout << "size    : " << empty.size()     << std::endl;
        std::cout << "capacity: " << empty.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < empty.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << empty.at(i).some_ << " ";
        }
        std::cout << std::endl;

        std::cout << "size    : " << mouse.size()     << std::endl;
        std::cout << "capacity: " << mouse.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < mouse.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << mouse.at(i).some_ << " ";
        }
        std::cout << std::endl;

        mouse.assign(fat_mouse.begin(), fat_mouse.end());

        std::cout << "size    : " << mouse.size()     << std::endl;
        std::cout << "capacity: " << mouse.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < mouse.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << mouse.at(i).some_ << " ";
        }
        std::cout << std::endl;

        empty2.assign(small_mouse.begin(), small_mouse.end());

        std::cout << "size    : " << empty2.size()     << std::endl;
        std::cout << "capacity: " << empty2.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < empty2.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << empty2.at(i).some_ << " ";
        }
        std::cout << std::endl;
    }

    void ft_assign_iter_iter_1280b_leaks_test() {
        std::cout << "\nassign_iter_iter_1280_leaks\n" << std::endl;
        lib::con<Test> mouse(32);
        std::vector<Test> mouse_etalon(32);
        for (size_t i = 0; i < mouse.size(); ++i) {
            mouse_etalon[i].some_ = i;
        }
        for (size_t i = 0; i < mouse.size(); ++i) {
            mouse[i].some_ = i;
        }
        lib::con<Test> fat_mouse(344);
        for (size_t i = 0; i < fat_mouse.size(); ++i) {
            fat_mouse[i].some_ = i + 1000;
        }

        std::cout << "size    : " << mouse.size()     << std::endl;
        std::cout << "capacity: " << mouse.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < mouse.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << mouse.at(i).some_ << " ";
        }
        std::cout << std::endl;

//        mouse.insert(mouse.begin(), mouse.begin() + 5, mouse.end() -5);
        mouse.assign(mouse.begin() + 10, mouse.end() - 10);

        std::cout << "size    : " << mouse.size()     << std::endl;
        std::cout << "capacity: " << mouse.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < mouse.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << mouse.at(i).some_ << " ";
        }
        std::cout << std::endl;

        //mouse_etalon.insert(mouse_etalon.begin(), mouse_etalon.begin() + 5, mouse_etalon.end() - 5);
        mouse_etalon.assign(mouse_etalon.begin() + 10, mouse_etalon.end() - 10);

        std::cout << "size    : " << mouse_etalon.size()     << std::endl;
        std::cout << "capacity: " << mouse_etalon.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < mouse_etalon.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << mouse_etalon.at(i).some_ << " ";
        }
        std::cout << std::endl;

//        mouse.assign(mouse.begin() + 5, mouse.end() - 5);
//
//        std::cout << "size    : " << mouse.size()     << std::endl;
//        std::cout << "capacity: " << mouse.capacity() << std::endl;
//        std::cout << "arr     :" << std::endl;
//        for (size_t i = 0; i < mouse.size(); ++i) {
//            if (i != 0 && i % 32 == 0)
//                std::cout << std::endl;
//            std::cout << mouse.at(i).some_ << " ";
//        }
//        std::cout << std::endl;
//
//        mouse.assign(fat_mouse.begin(), fat_mouse.end());
//
//        std::cout << "size    : " << mouse.size()     << std::endl;
//        std::cout << "capacity: " << mouse.capacity() << std::endl;
//        std::cout << "arr     :" << std::endl;
//        for (size_t i = 0; i < mouse.size(); ++i) {
//            if (i != 0 && i % 32 == 0)
//                std::cout << std::endl;
//            std::cout << mouse.at(i).some_ << " ";
//        }
//        std::cout << std::endl;
//
//        mouse.assign(fat_mouse.begin(), fat_mouse.begin() + 10);
//
//        std::cout << "size    : " << mouse.size()     << std::endl;
//        std::cout << "capacity: " << mouse.capacity() << std::endl;
//        std::cout << "arr     :" << std::endl;
//        for (size_t i = 0; i < mouse.size(); ++i) {
//            if (i != 0 && i % 32 == 0)
//                std::cout << std::endl;
//            std::cout << mouse.at(i).some_ << " ";
//        }
//        std::cout << std::endl;
//
//        try {
//            mouse.assign(fat_mouse.begin() + 10, fat_mouse.begin());
//        } catch(std::exception & e) {
//            std::cout << e.what() << std::endl;
//        }
//
//        std::cout << "size    : " << mouse.size()     << std::endl;
//        std::cout << "capacity: " << mouse.capacity() << std::endl;
//        std::cout << "arr     :" << std::endl;
//        for (size_t i = 0; i < mouse.size(); ++i) {
//            if (i != 0 && i % 32 == 0)
//                std::cout << std::endl;
//            std::cout << mouse.at(i).some_ << " ";
//        }
//        std::cout << std::endl;
//
//        try {
//            mouse.assign(fat_mouse.begin(), (fat_mouse.begin() + fat_mouse.max_size()));
//        } catch(std::exception & e) {
//            std::cout << e.what() << std::endl;
//        }
//
//        std::cout << "size    : " << mouse.size()     << std::endl;
//        std::cout << "capacity: " << mouse.capacity() << std::endl;
//        std::cout << "arr     :" << std::endl;
//        for (size_t i = 0; i < mouse.size(); ++i) {
//            if (i != 0 && i % 32 == 0)
//                std::cout << std::endl;
//            std::cout << mouse.at(i).some_ << " ";
//        }
//        std::cout << std::endl;
//
    }

    void ft_assign_n_val_test() {
        std::cout << "\nassign_n_val\n" << std::endl;
//        std::vector<Test> mouse_etalon(16);
//        std::vector<Test> empty_etalon;
//        empty_etalon.assign(64, 7);
//        std::cout << "size    : " << empty_etalon.size()     << std::endl;
//        std::cout << "capacity: " << empty_etalon.capacity() << std::endl;
//        std::cout << "arr     :" << std::endl;
//        for (size_t i = 0; i < empty_etalon.size(); ++i) {
//            if (i != 0 && i % 32 == 0)
//                std::cout << std::endl;
//            std::cout << empty_etalon.at(i).some_ << " ";
//        }

        std::cout << std::endl;
        lib::con<Test> mouse(128);
        lib::con<Test> empty;
        lib::con<Test> empty2;
        empty2.reserve(1023);
        for (size_t i = 0; i < mouse.size(); ++i) {
            mouse[i].some_ = i;
        }

//        empty.assign(empty.begin(), empty.end());
//
//        empty.assign(mouse.begin(), mouse.end());
//
//        std::cout << "size    : " << empty.size()     << std::endl;
//        std::cout << "capacity: " << empty.capacity() << std::endl;
//        std::cout << "arr     :" << std::endl;
//        for (size_t i = 0; i < empty.size(); ++i) {
//            if (i != 0 && i % 32 == 0)
//                std::cout << std::endl;
//            std::cout << empty.at(i).some_ << " ";
//        }
//        std::cout << std::endl;
//        mouse.assign(64, 7);
//
//        std::cout << "size    : " << mouse.size()     << std::endl;
//        std::cout << "capacity: " << mouse.capacity() << std::endl;
//        std::cout << "arr     :" << std::endl;
//        for (size_t i = 0; i < mouse.size(); ++i) {
//            if (i != 0 && i % 32 == 0)
//                std::cout << std::endl;
//            std::cout << mouse.at(i).some_ << " ";
//        }
//        std::cout << std::endl;
//
//        std::cout << "size    : " << mouse.size()     << std::endl;
//        std::cout << "capacity: " << mouse.capacity() << std::endl;
//        std::cout << "arr     :" << std::endl;
//        for (size_t i = 0; i < mouse.size(); ++i) {
//            if (i != 0 && i % 32 == 0)
//                std::cout << std::endl;
//            std::cout << mouse.at(i).some_ << " ";
//        }
//        std::cout << std::endl;
//
//        mouse.assign(1024, 7);
//
//        std::cout << "size    : " << mouse.size()     << std::endl;
//        std::cout << "capacity: " << mouse.capacity() << std::endl;
//        std::cout << "arr     :" << std::endl;
//        for (size_t i = 0; i < mouse.size(); ++i) {
//            if (i != 0 && i % 32 == 0)
//                std::cout << std::endl;
//            std::cout << mouse.at(i).some_ << " ";
//        }
//        std::cout << std::endl;

        empty2.assign(812, 7);

        std::cout << "size    : " << empty2.size()     << std::endl;
        std::cout << "capacity: " << empty2.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < empty2.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << empty2.at(i).some_ << " ";
        }
        std::cout << std::endl;

    }

    void ft_push_back_test() {
        std::cout << "\npush_back\n" << std::endl;
        lib::con<Test> mouse(128);
        lib::con<Test> empty;
        lib::con<Test> empty2;
        empty2.reserve(1023);
        for (size_t i = 0; i < mouse.size(); ++i) {
            mouse[i].some_ = i;
        }

        empty.push_back(7);

        std::cout << "size    : " << empty.size()     << std::endl;
        std::cout << "capacity: " << empty.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < empty.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << empty.at(i).some_ << " ";
        }
        std::cout << std::endl;

        mouse.push_back(mouse[127]);

        std::cout << "size    : " << mouse.size()     << std::endl;
        std::cout << "capacity: " << mouse.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < mouse.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << mouse.at(i).some_ << " ";
        }
        std::cout << std::endl;

        empty2.push_back(mouse[127]);

        std::cout << "size    : " << empty2.size()     << std::endl;
        std::cout << "capacity: " << empty2.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < empty2.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << empty2.at(i).some_ << " ";
        }
        std::cout << std::endl;

    }

    void ft_pop_back_test() {
        std::cout << "\npop_back\n" << std::endl;
        lib::con<Test> mouse(128);
        lib::con<Test> empty;
        lib::con<Test> empty2;
        empty2.reserve(1023);
        for (size_t i = 0; i < mouse.size(); ++i) {
            mouse[i].some_ = i;
        }

        for (size_t i = 0; i < 10; ++i) {
            mouse.pop_back();
        }

        std::cout << "size    : " << mouse.size()     << std::endl;
        std::cout << "capacity: " << mouse.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < mouse.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << mouse.at(i).some_ << " ";
        }
        std::cout << std::endl;
    }

    void ft_insert_iter_val_test() {
        std::cout << "\ninsert_iter_val\n" << std::endl;
        lib::con<Test> mouse(128);
        lib::con<Test> fat_mouse(1023);
        lib::con<Test> small_mouse(11);
        lib::con<Test> empty;
        lib::con<Test> empty2;
        lib::con<Test> big_empty;
        big_empty.reserve(2023);
        for (size_t i = 0; i < mouse.size(); ++i) {
            mouse[i].some_ = i;
        }

        mouse.insert(mouse.begin(), 100);

        std::cout << "size    : " << mouse.size()     << std::endl;
        std::cout << "capacity: " << mouse.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < mouse.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << mouse.at(i).some_ << " ";
        }
        std::cout << std::endl;

        mouse.insert(mouse.end(), 100);

        std::cout << "size    : " << mouse.size()     << std::endl;
        std::cout << "capacity: " << mouse.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < mouse.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << mouse.at(i).some_ << " ";
        }
        std::cout << std::endl;

        big_empty.insert(big_empty.begin(), 88);

        std::cout << "size    : " << big_empty.size()     << std::endl;
        std::cout << "capacity: " << big_empty.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < big_empty.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << big_empty.at(i).some_ << " ";
        }
        std::cout << std::endl;

        empty.insert(empty.begin(), 9);
        empty.insert(empty.begin(), 7);

        std::cout << "size    : " << empty.size()     << std::endl;
        std::cout << "capacity: " << empty.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < empty.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << empty.at(i).some_ << " ";
        }
        std::cout << std::endl;

        empty.insert(empty.begin(), empty[0]);

        std::cout << "size    : " << empty.size()     << std::endl;
        std::cout << "capacity: " << empty.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < empty.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << empty.at(i).some_ << " ";
        }
        std::cout << std::endl;

        empty2.push_back(1);
        empty2.insert(empty2.begin(), empty2[0]);

        std::cout << "size    : " << empty2.size()     << std::endl;
        std::cout << "capacity: " << empty2.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < empty2.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << empty2.at(i).some_ << " ";
        }
        std::cout << std::endl;
    }
    void ft_insert_iter_n_val_test() {
        std::cout << "\ninsert_iter_n_val\n" << std::endl;
        lib::con<Test> mouse(128);
        lib::con<Test> fat_mouse(1023);
        lib::con<Test> small_mouse(11);
        lib::con<Test> empty;
        lib::con<Test> empty2;
        lib::con<Test> big_empty;
        big_empty.reserve(2023);
        for (size_t i = 0; i < mouse.size(); ++i) {
            mouse[i].some_ = i;
        }

        mouse.insert(mouse.begin(), 20, 100);

        std::cout << "size    : " << mouse.size()     << std::endl;
        std::cout << "capacity: " << mouse.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < mouse.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << mouse.at(i).some_ << " ";
        }
        std::cout << std::endl;

        mouse.insert(mouse.end(), 15, 100);

        std::cout << "size    : " << mouse.size()     << std::endl;
        std::cout << "capacity: " << mouse.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < mouse.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << mouse.at(i).some_ << " ";
        }
        std::cout << std::endl;

        big_empty.insert(big_empty.begin(), 19, 88);

        std::cout << "size    : " << big_empty.size()     << std::endl;
        std::cout << "capacity: " << big_empty.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < big_empty.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << big_empty.at(i).some_ << " ";
        }
        std::cout << std::endl;

        empty.insert(empty.begin(), 3, 9);
        empty.insert(empty.begin(), 4, 7);

        std::cout << "size    : " << empty.size()     << std::endl;
        std::cout << "capacity: " << empty.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < empty.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << empty.at(i).some_ << " ";
        }
        std::cout << std::endl;

        empty.insert(empty.begin(), 26, empty[0]);

        std::cout << "size    : " << empty.size()     << std::endl;
        std::cout << "capacity: " << empty.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < empty.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << empty.at(i).some_ << " ";
        }
        std::cout << std::endl;

        empty2.push_back(1);
        empty2.insert(empty2.begin(), 19, empty2[0]);

        std::cout << "size    : " << empty2.size()     << std::endl;
        std::cout << "capacity: " << empty2.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < empty2.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << empty2.at(i).some_ << " ";
        }
        std::cout << std::endl;
    }

    void ft_insert_iter_iter_iter_test() {
        std::cout << "\niter_iter_iter\n" << std::endl;
        lib::con<Test> mouse(128);
        lib::con<Test> empty;
        lib::con<Test> empty2;
        empty2.reserve(1023);
        for (size_t i = 0; i < mouse.size(); ++i) {
            mouse[i].some_ = i;
        }
        lib::con<Test> fat_mouse(344);
        for (size_t i = 0; i < fat_mouse.size(); ++i) {
            fat_mouse[i].some_ = i + 1000;
        }

        lib::con<Test> small_mouse(5);
        for (size_t i = 0; i < small_mouse.size(); ++i) {
            small_mouse[i].some_ = i + 500;
        }

        empty.insert(empty.begin(), mouse.begin() + 5, mouse.end() - 5);

        std::cout << "size    : " << empty.size()     << std::endl;
        std::cout << "capacity: " << empty.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < empty.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << empty.at(i).some_ << " ";
        }
        std::cout << std::endl;

        std::cout << "size    : " << mouse.size()     << std::endl;
        std::cout << "capacity: " << mouse.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < mouse.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << mouse.at(i).some_ << " ";
        }
        std::cout << std::endl;

        mouse.insert(mouse.end(), fat_mouse.begin(), fat_mouse.end());

        std::cout << "size    : " << mouse.size()     << std::endl;
        std::cout << "capacity: " << mouse.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < mouse.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << mouse.at(i).some_ << " ";
        }
        std::cout << std::endl;

        empty2.insert(empty2.begin(), small_mouse.begin(), small_mouse.end());

        std::cout << "size    : " << empty2.size()     << std::endl;
        std::cout << "capacity: " << empty2.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < empty2.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << empty2.at(i).some_ << " ";
        }
        std::cout << std::endl;
    }

    void ft_insert_iter_iter_iter_8390_leaks_test() {
        std::cout << "\nassign_iter_iter_1280_leaks\n" << std::endl;
        lib::con<Test> mouse(128);
        for (size_t i = 0; i < mouse.size(); ++i) {
            mouse[i].some_ = i;
        }
        lib::con<Test> fat_mouse(344);
        for (size_t i = 0; i < fat_mouse.size(); ++i) {
            fat_mouse[i].some_ = i + 1000;
        }

        std::cout << "size    : " << mouse.size()     << std::endl;
        std::cout << "capacity: " << mouse.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < mouse.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << mouse.at(i).some_ << " ";
        }
        std::cout << std::endl;

        mouse.insert(mouse.begin() + 10, mouse.begin(), mouse.end());

        std::cout << "size    : " << mouse.size()     << std::endl;
        std::cout << "capacity: " << mouse.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < mouse.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << mouse.at(i).some_ << " ";
        }
        std::cout << std::endl;

        mouse.insert(mouse.end(), mouse.begin() + 5, mouse.end() - 5);

        std::cout << "size    : " << mouse.size()     << std::endl;
        std::cout << "capacity: " << mouse.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < mouse.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << mouse.at(i).some_ << " ";
        }
        std::cout << std::endl;

        mouse.insert(mouse.begin(), fat_mouse.begin(), fat_mouse.end());

        std::cout << "size    : " << mouse.size()     << std::endl;
        std::cout << "capacity: " << mouse.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < mouse.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << mouse.at(i).some_ << " ";
        }
        std::cout << std::endl;

        mouse.insert(mouse.begin() + 7, fat_mouse.begin(), fat_mouse.begin() + 10);

        std::cout << "size    : " << mouse.size()     << std::endl;
        std::cout << "capacity: " << mouse.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < mouse.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << mouse.at(i).some_ << " ";
        }
        std::cout << std::endl;

        try {
            mouse.insert(mouse.begin(), fat_mouse.begin() + 10, fat_mouse.begin());
        } catch(std::exception & e) {
            std::cout << e.what() << std::endl;
        }

        std::cout << "size    : " << mouse.size()     << std::endl;
        std::cout << "capacity: " << mouse.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < mouse.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << mouse.at(i).some_ << " ";
        }
        std::cout << std::endl;

        try {
            mouse.insert(mouse.begin(), fat_mouse.begin(), (fat_mouse.begin() + fat_mouse.max_size()));
        } catch(std::exception & e) {
            std::cout << e.what() << std::endl;
        }

        std::cout << "size    : " << mouse.size()     << std::endl;
        std::cout << "capacity: " << mouse.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < mouse.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << mouse.at(i).some_ << " ";
        }
        std::cout << std::endl;

    }

    void ft_erase_2540_leaks_test() {
        std::cout << "erase_2540_leaks_test" << std::endl;
        lib::con<Test> mouse(129);
        for (size_t i = 0; i < mouse.size(); ++i) {
            mouse[i].some_ = i;
        }
        lib::con<Test> big_mouse(1023);
        for (size_t i = 0; i < big_mouse.size(); ++i) {
            big_mouse[i].some_ = i + 1000;
        }

        std::cout << mouse.erase(mouse.begin())->some_ << std::endl;

        std::cout << "size    : " << mouse.size()     << std::endl;
        std::cout << "capacity: " << mouse.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < mouse.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << mouse.at(i).some_ << " ";
        }
        std::cout << std::endl;

        mouse.erase(mouse.end() - 1);

        std::cout << "size    : " << mouse.size()     << std::endl;
        std::cout << "capacity: " << mouse.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < mouse.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << mouse.at(i).some_ << " ";
        }
        std::cout << std::endl;

        mouse.erase(mouse.begin() + 100);

        std::cout << "size    : " << mouse.size()     << std::endl;
        std::cout << "capacity: " << mouse.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < mouse.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << mouse.at(i).some_ << " ";
        }
        std::cout << std::endl;

        big_mouse.erase(big_mouse.begin() + 100, big_mouse.end() - 100);

        std::cout << "size    : " << big_mouse.size()     << std::endl;
        std::cout << "capacity: " << big_mouse.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < big_mouse.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << big_mouse.at(i).some_ << " ";
        }
        std::cout << std::endl;

        big_mouse.erase(big_mouse.begin(), big_mouse.end());

        std::cout << "size    : " << big_mouse.size()     << std::endl;
        std::cout << "capacity: " << big_mouse.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < big_mouse.size(); ++i) {
            // if (i != 0 && i % 32 == 0)
            std::cout << big_mouse.at(i).some_ << " ";
        }
        std::cout << std::endl;
    }

    void ft_swap_test() {
        std::cout << "swap_test" << std::endl;
        lib::con<Test> mouse(129);
        for (size_t i = 0; i < mouse.size(); ++i) {
            mouse[i].some_ = i;
        }
        lib::con<Test> big_mouse(1023);
        for (size_t i = 0; i < big_mouse.size(); ++i) {
            big_mouse[i].some_ = i + 1000;
        }

        big_mouse.swap(mouse);

        std::cout << "size    : " << mouse.size()     << std::endl;
        std::cout << "capacity: " << mouse.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < mouse.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << mouse.at(i).some_ << " ";
        }
        std::cout << std::endl;

        std::cout << "size    : " << big_mouse.size()     << std::endl;
        std::cout << "capacity: " << big_mouse.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < big_mouse.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << big_mouse.at(i).some_ << " ";
        }
        std::cout << std::endl;

        mouse.swap(big_mouse);

        std::cout << "size    : " << mouse.size()     << std::endl;
        std::cout << "capacity: " << mouse.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < mouse.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << mouse.at(i).some_ << " ";
        }
        std::cout << std::endl;

        std::cout << "size    : " << big_mouse.size()     << std::endl;
        std::cout << "capacity: " << big_mouse.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < big_mouse.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << big_mouse.at(i).some_ << " ";
        }
        std::cout << std::endl;
    }

    void ft_clear_test() {
        std::cout << "clear_test" << std::endl;
        lib::con<Test> empty;
        lib::con<Test> big_empty;
        lib::con<Test> mouse(129);
        for (size_t i = 0; i < mouse.size(); ++i) {
            mouse[i].some_ = i;
        }
        lib::con<Test> big_mouse(1023);
        for (size_t i = 0; i < big_mouse.size(); ++i) {
            big_mouse[i].some_ = i + 1000;
        }
        big_empty.reserve(190);

        std::cout << "size    : " << empty.size()     << std::endl;
        std::cout << "capacity: " << empty.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < empty.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << empty.at(i).some_ << " ";
        }
        std::cout << std::endl;

        std::cout << "size    : " << big_empty.size()     << std::endl;
        std::cout << "capacity: " << big_empty.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < big_empty.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << big_empty.at(i).some_ << " ";
        }
        std::cout << std::endl;

        std::cout << "size    : " << mouse.size()     << std::endl;
        std::cout << "capacity: " << mouse.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < mouse.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << mouse.at(i).some_ << " ";
        }
        std::cout << std::endl;

        std::cout << "size    : " << big_mouse.size()     << std::endl;
        std::cout << "capacity: " << big_mouse.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < big_mouse.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << big_mouse.at(i).some_ << " ";
        }
        std::cout << std::endl;

        empty.clear();
        big_empty.clear();
        mouse.clear();
        big_mouse.clear();

        std::cout << "size    : " << empty.size()     << std::endl;
        std::cout << "capacity: " << empty.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < empty.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << empty.at(i).some_ << " ";
        }
        std::cout << std::endl;

        std::cout << "size    : " << big_empty.size()     << std::endl;
        std::cout << "capacity: " << big_empty.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < big_empty.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << big_empty.at(i).some_ << " ";
        }
        std::cout << std::endl;

        std::cout << "size    : " << mouse.size()     << std::endl;
        std::cout << "capacity: " << mouse.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < mouse.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << mouse.at(i).some_ << " ";
        }
        std::cout << std::endl;

        std::cout << "size    : " << big_mouse.size()     << std::endl;
        std::cout << "capacity: " << big_mouse.capacity() << std::endl;
        std::cout << "arr     :" << std::endl;
        for (size_t i = 0; i < big_mouse.size(); ++i) {
            if (i != 0 && i % 32 == 0)
                std::cout << std::endl;
            std::cout << big_mouse.at(i).some_ << " ";
        }
        std::cout << std::endl;
    }

    void ft_relational_operators() {
        std::cout << "relational_operators" << std::endl;
        lib::con<int> empty;
        lib::con<int> big_empty;
        lib::con<int> mouse(129);
        for (size_t i = 0; i < mouse.size(); ++i) {
            mouse[i] = i;
        }
        lib::con<int> big_mouse(1023);
        for (size_t i = 0; i < big_mouse.size(); ++i) {
            big_mouse[i] = i + 1000;
        }
        big_empty.reserve(190);
        std::cout << (empty     == empty)     << std::endl;
        std::cout << (big_empty == big_empty) << std::endl;
        std::cout << (mouse     == mouse)     << std::endl;
        std::cout << (big_mouse == big_mouse) << std::endl;

        std::cout << (empty     != empty)     << std::endl;
        std::cout << (big_empty != big_empty) << std::endl;
        std::cout << (mouse     != mouse)     << std::endl;
        std::cout << (big_mouse != big_mouse) << std::endl;

        std::cout << (empty     > big_empty)     << std::endl;
        std::cout << (big_empty > empty) << std::endl;
        std::cout << (mouse     > big_mouse)     << std::endl;
        std::cout << (big_mouse > mouse) << std::endl;

        std::cout << (empty     < big_empty)     << std::endl;
        std::cout << (big_empty < empty) << std::endl;
        std::cout << (mouse     < big_mouse)     << std::endl;
        std::cout << (big_mouse < mouse) << std::endl;

        std::cout << (empty     >= big_empty)     << std::endl;
        std::cout << (big_empty >= empty) << std::endl;
        std::cout << (mouse     >= big_mouse)     << std::endl;
        std::cout << (big_mouse >= mouse) << std::endl;

        std::cout << (empty     <= big_empty)     << std::endl;
        std::cout << (big_empty <= empty) << std::endl;
        std::cout << (mouse     <= big_mouse)     << std::endl;
        std::cout << (big_mouse <= mouse) << std::endl;
    }

    void const_iterators() {
        std::cout << "const_iterators" << std::endl;
        lib::con<int> src;
        for (int i = 0; i < 20; ++i) {
            src.push_back(i);
        }
        lib::con<const int> def(src.begin(), src.end());

        lib::con<const int>::const_iterator cit(def.begin());

        while (cit != def.end()) {
            std::cout << *cit << " ";
            ++cit;
        }
        std::cout << std::endl;
//	*cit = 6; // DOES NOT COMPILE

        --cit;
        lib::con<const int>::const_iterator cit2(def.begin());
        std::cout << (cit > cit2) << std::endl;
        std::cout << (cit >= cit2) << std::endl;
        std::cout << (cit < cit2) << std::endl;
        std::cout << (cit <= cit2) << std::endl;
        std::cout << (cit == cit2) << std::endl;

        // Same not compile scenario
//        std::cout << std::endl;
//        lib::con<int>::const_iterator cit_src(src.begin());
//        while (cit_src != src.end()) {
//            std::cout << *cit_src << " ";
//            ++cit_src;
//        }
//        std::cout << std::endl;

//        std::vector<int> src_etalon;
//        std::vector<const int> def_etalon(src.begin(), src.end());
//        std::vector<int>::const_iterator cit_src_etalon(src.begin());
//        while (cit_src_etalon != src.end()) {
//            std::cout << *cit_src_etalon << " ";
//            ++cit_src_etalon;
//        }
        // *cit_src = 6; // DOES NOT COMPILE
    }

    void reverse_iterators() {
        std::cout << "reverse_iterators" << std::endl;
        lib::con<int> src;
        for (int i = 0; i < 20; ++i) {
            src.push_back(i);
        }
        lib::con<const int> def(src.begin(), src.end());

        lib::con<const int>::const_reverse_iterator rcit(def.rbegin());

        while (rcit != def.rend()) {
            std::cout << *rcit << " ";
            ++rcit;
        }
        std::cout << std::endl;
//	*rcit = 6; // DOES NOT COMPILE

        --rcit;
        lib::con<const int>::const_reverse_iterator rcit2(def.rbegin());
        std::cout << (rcit > rcit2) << std::endl;
        std::cout << (rcit >= rcit2) << std::endl;
        std::cout << (rcit < rcit2) << std::endl;
        std::cout << (rcit <= rcit2) << std::endl;
        std::cout << (rcit == rcit2) << std::endl;

        //lib::con<int>::const_iterator iterator(src.begin());
        // Same not compile scenario
        lib::con<int>::const_reverse_iterator rcit_src(src.rbegin());
        while (rcit_src != src.rend()) {
            std::cout << *rcit_src << " ";
            ++rcit_src;
        }
        std::cout << std::endl;

//        std::vector<int> src_etalon;
//        for (int i = 0; i < 20; ++i) {
//            src_etalon.push_back(i);
//        }
//        std::vector<int>::const_reverse_iterator rcit_src_etalon(src_etalon.rbegin());
//        while (rcit_src_etalon != src.rend()) {
//            std::cout << *rcit_src_etalon << " ";
//            ++rcit_src_etalon;
//        }
//        std::cout << std::endl;
        // *rcit_src = 6; // DOES NOT COMPILE
    }

    void relational_operators() {
        std::cout << "relational_operators" << std::endl;
        lib::con<int> def;
        for (int i = 0; i < 20; i += 2) {
            def.push_back(2);
        }
        lib::con<int> def2;
        for (int i = 1; i < 20; i += 2) {
            def2.push_back(2);
        }
        std::cout << (def >  def2) << std::endl;
        std::cout << (def >= def2) << std::endl;
        std::cout << (def <  def2) << std::endl;
        std::cout << (def <= def2) << std::endl;
        std::cout << (def == def2) << std::endl;
        std::cout << (def != def2) << std::endl;
    }

    void const_iter_with_iter() {
        std::cout << "const_iter_with_iter" << std::endl;
        lib::con<int> def;
        for (int i = 0; i < 20; i += 2) {
            def.push_back(2);
        }
        lib::con<int>::iterator       it(def.begin());
        lib::con<int>::const_iterator cit(def.begin());

        std::cout << (it >  cit) << std::endl;
        std::cout << (it >= cit) << std::endl;
        std::cout << (it <  cit) << std::endl;
        std::cout << (it <= cit) << std::endl;
        std::cout << (it == cit) << std::endl;
        std::cout << (it != cit) << std::endl;

        lib::con<int>::reverse_iterator       rit(def.begin());
        lib::con<int>::const_reverse_iterator rcit(def.begin());

        std::cout << (rit >  rcit) << std::endl;
        std::cout << (rit >= rcit) << std::endl;
        std::cout << (rit <  rcit) << std::endl;
        std::cout << (rit <= rcit) << std::endl;
        std::cout << (rit == rcit) << std::endl;
        std::cout << (rit != rcit) << std::endl;
    }

    void ft_modifiers_test() {
//        ft_assign_iter_iter_leaks_test();
//        ft_assign_iter_iter_1280b_leaks_test();
//
        ft_assign_n_val_test();
//        ft_push_back_test();
//        ft_pop_back_test();
//        ft_insert_iter_val_test();
//        ft_insert_iter_n_val_test();
//        ft_insert_iter_iter_iter_test();
//        ft_insert_iter_iter_iter_8390_leaks_test();
//
//        ft_erase_2540_leaks_test();
//        ft_swap_test();
//        ft_clear_test();
//        ft_relational_operators();
    }

// =============================================================================

    int main(void)
    {
//        ft_constructors_capacity_test();
//        ft_operator_assignment();
//        ft_operator_const_assignment();
//        ft_iterator_test();
//        ft_el_access_test();
        ft_modifiers_test();
//
//        const_iterators();
//        reverse_iterators();
//        relational_operators();
//        const_iter_with_iter();
        return 0;
    }

//int main() {
//======================================simple===================================
/*
    std::cout << "Simple test" << std::endl;
    try {
        size_t var = std::numeric_limits<size_t>::max();
        std::cout << var << std::endl;
        //std::vector<int> test(var, 10);
        std::vector<int> test(0, 10);
        for (size_t i = 0; i < test.size(); ++i)
            std::cout << test[i] << std::endl;
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }
    */
//======================================assign capacity===================================
/*
    std::cout << "Assignation capacity test" << std::endl;

    std::vector<int> foo (3,0);
    std::vector<int> bar (1000,0);

    std::cout << "Capacity of foo: " << int(foo.capacity()) << '\n';
    std::cout << "Capacity of bar: " << int(bar.capacity()) << '\n';
    std::cout << "Size of foo: " << int(foo.size()) << '\n';
    std::cout << "Size of bar: " << int(bar.size()) << '\n';

    bar = foo;
    //foo = std::vector<int>();

    std::cout << "Capacity of foo: " << int(foo.capacity()) << '\n';
    std::cout << "Capacity of bar: " << int(bar.capacity()) << '\n';
    std::cout << "Size of foo: " << int(foo.size()) << '\n';
    std::cout << "Size of bar: " << int(bar.size()) << '\n';
    */
/*
//======================================destruction on assignation===================================
std::vector<S> v1;
std::vector<S> v2;
std::cout << "construction starts" << '\n';
S element1(1);
S element2(2);
S element3(3);
S element4(4);
std::cout << "construction ends" << '\n';
std::cout << "1 starts" << '\n';
v1.push_back(element1);
std::cout << "1 ends" << '\n';
std::cout << "2 starts" << '\n';
v1.push_back(element2);
std::cout << "2 ends" << '\n';
std::cout << "3 starts" << '\n';
v1.push_back(element3);
std::cout << "3 ends" << '\n';
v2.push_back(element3);
v2.push_back(element4);
v2.resize(4);
std::cout << "assignation starts" << '\n';
v1=v2;
std::cout << "assignation ends" << '\n';
for (size_t i=0;i<v1.size();i++)
    std::cout << v1[i].index_ << '\n';
*/
//======================================max size===================================
//    std::cout << "max size starts" << '\n';
//    std::vector<S> test_class_vector;
//    std::cout << "max size with class with 2 ints inside " << test_class_vector.max_size() << '\n';
//    std::vector<int> test_int_vector;
//    std::cout << "max size with int inside " << test_int_vector.max_size() << '\n';
//======================================resize capacity test========================
/*
    std::cout << "resize starts" << '\n';
    std::vector<int> resize_mini (3,0);
    std::cout << "capacity was " << resize_mini.capacity() << '\n';
    resize_mini.resize(5);
    std::cout << "capacity after resize 5 is " << resize_mini.capacity() << '\n';
    resize_mini.resize(13);
    std::cout << "capacity after resize 13 is " << resize_mini.capacity() << '\n';
//======================================reserve capacity test========================
    std::cout << "reserve starts" << '\n';
    std::vector<int> reserve_mini (3,0);
    std::cout << "capacity was " << reserve_mini.capacity() << '\n';
    reserve_mini.reserve(5);
    std::cout << "capacity after reserve 5 is " << reserve_mini.capacity() << '\n';
    reserve_mini.reserve(13);
    std::cout << "capacity after reserve 13 is " << reserve_mini.capacity() << '\n';
    */
//======================================opetator at test========================
/*
    std::cout << "at testkkkkk starts" << '\n';
    std::vector<int> at_vector (3,0);
    try {
        std::cout << at_vector.at(4) << std::endl;
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }
    */
//======================================iterator test========================
//    std::vector<int> iterator_mini (3,3);
//    std::vector<int>::iterator it = iterator_mini.begin();
//    std::vector<int>::iterator sec(it);
//    std::cout << sec[0] << std::endl;
//    std::cout << *sec << std::endl;
//    std::cout << "pointer it const starts" << '\n';
//    int xxx = 3;
//    int* xxx_pointer = &xxx;
//    std::vector<int>::iterator thir(xxx_pointer);
//
//    std::vector<S> iterator_mini_class (3,3);
//    std::vector<S>::iterator it_c = iterator_mini_class.begin();
//    std::cout << it_c->index_ << std::endl;
/*
char varb = 23;
    std::vector<int> iterator_plus (varb,3);
    iterator_plus[0] = 0;
    iterator_plus[1] = 1;
    //iterator_plus[2] = 2;
    std::vector<int>::iterator it1 = iterator_plus.begin();
    std::cout << *(it1 + 0) << std::endl;
    std::cout << *(it1 + 1) << std::endl;
    std::cout << *(1 + it1) << std::endl;
    iterator_plus.reserve(10);
    it1+=1;
    if (it1==it1)
        std::cout << *(it1 + 0) << std::endl;
    it1-=1;
    if (it1!=(it1 + 1))
    std::cout << *(it1 + 0) << std::endl;
    if (it1<(it1 + 1))
        std::cout << "less works" << std::endl;
    if (it1>(it1 - 1))
        std::cout << "more works" << std::endl;
    std::cout << it1 - (it1 + 1) << std::endl;
    advance(it1, 2);
    std::cout << *it1 << std::endl;
    */
//======================================reverse iterator test========================
/*
    std::vector<int> rev_it_vec (3,3);
    rev_it_vec[0] = 0;
    rev_it_vec[1] = 1;
    rev_it_vec[2] = 2;
    std::vector<int>::iterator it = rev_it_vec.begin();
    std::vector<int>::reverse_iterator rev_it(it);
    std::cout << "it "  << *it << std::endl;
    rev_it--;
    std::cout << "rev "  << *rev_it << " base " << *rev_it.base() << std::endl;
    std::cout << "rev points at 1 behind the original" << std::endl;
    std::vector<int>::iterator it2 = rev_it.base();
    std::cout << "original goes with reverse but one further" << std::endl;
    std::cout << "it2 "  << *it2 << std::endl;
    std::vector<int>::reverse_iterator rev_it2(it2);
    rev_it2--;
    std::cout << "rev "  << *rev_it2 << std::endl;
    std::cout << "we created 2nd reverse that is one more" << std::endl;
    rev_it = rev_it2;
    std::cout << "rev "  << *rev_it << " base " << *rev_it.base() << std::endl;
    std::cout << "after assignation it = it2 " << std::endl;
    std::cout << "rev "  << *(rev_it + 1) << std::endl;
    std::cout << "with + 1" << std::endl;
    std::cout << "rev "  << *(rev_it - 1) << std::endl;
    std::cout << "with - 1" << std::endl;
    if (rev_it - 1 < rev_it + 1)
        std::cout << "less works: rev - 1 < rev + 1 (double reverse)" << std::endl;
    std::cout << "rev "  << *rev_it << std::endl;
    std::cout << "with *rev = 1 (rev - 1)[1]: " << (rev_it - 1)[1] << std::endl;
    std::cout << "(rev - 1) - (rev + 1) " << (rev_it - 1) - (rev_it + 1) << std::endl;
    std::cout << "(rev - 1).base() - (rev + 1).base() " << (rev_it - 1).base() - (rev_it + 1).base() << std::endl;
    */

//    std::vector<S> vr1;
//    std::cout << "construction starts" << '\n';
//    S element1(1);
//    S element2(2);
////    vr1.push_back(element1);
////    vr1.push_back(element2);
////    std::vector<S>::iterator itrs = vr1.begin();
////    std::cout << "it[0].index " << itrs[0].index_ << std::endl;
////    std::cout << "it[1].index " << itrs[1].index_<< std::endl;
////    std::vector<S>::reverse_iterator rev_itrs(itrs);
////    rev_itrs--;
////    std::cout << "-> for this rev at begin-- " << rev_itrs->index_ << std::endl;
////    std::cout << "-> for this rev at base " << rev_itrs.base()->index_ << std::endl;
//    std::cout << "reservation starts" << std::endl;
//    vr1.reserve(5);
//    std::cout << "reservation ends" << std::endl;

//======================================insert test========================
//
//    size_t var = std::numeric_limits<size_t>::max();
//    std::cout << var << std::endl;
//    std::vector<int> test (3,3);
//    test[0] = 0;
//    test[1] = 1;
//    test[2] = 2;
//    std::cout << "was capacity" << test.capacity() << std::endl;
////    std::cout << *(test.insert(test.begin() + 1, 5, 5) + 1) << std::endl;
////    for (size_t i = 0; i < test.size(); ++i)
////        std::cout << test[i] << std::endl;
//    std::cout << "now capacity" << test.capacity() << std::endl;
//    std::vector<int> test2 (3,3);
//    test2[0] = 5;
//    test2[1] = 6;
//    test2[2] = 7;
//    test.insert(test.begin() + 1, test2.begin(), test2.end());
//    for (size_t i = 0; i < test.size(); ++i)
//        std::cout << test[i] << std::endl;
//    std::cout << std::endl;
////    std::cout << "erase end starts" << std::endl;
////    test2.erase(test2.end()); //sega
//    for (size_t i = 0; i < test2.size(); ++i)
//        std::cout << test2[i] << std::endl;
//    std::cout << "end - begin " << test2.end() - test2.begin() << " size " << test2.size() << std::endl;

//======================================dealloc zero size array========================
//    std::vector<int> test (0,0);
//    test.get_allocator().deallocate(&test[0], 0);
//======================================dealloc zero size array========================

//struct S {
//    int index_;
//    int fdjks;
//    S(int index) : index_(index) {
//        std::cout << "Calling S " << index_ << " constructor\n";
//    }
//    S() : index_(0) {
//        std::cout << "Calling S " << index_ << " default constructor\n";
//    }
//    S(const S& other) : index_(other.index_) {
//        std::cout << "Calling S " << index_ << " to " << other.index_ << " copy constructor\n";
//    }
//    S& operator= (const S& other){
//        std::cout << "Calling S " << index_ << " to " << other.index_ << " assignation\n";
//        return (*this);
//    }
//    ~S() {
//        std::cout << "Calling S " << index_ << " destructor\n";
//    }
//};
//
