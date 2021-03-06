//
// Created by Namor Scarab on 2/22/22.
//

#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include <cstddef> // ptrdiff_t
#include "utils.hpp"

namespace ft {

    template<class Category,            // iterator::iterator_category
            class T,                     // iterator::value_type
            class Distance = ptrdiff_t,  // iterator::difference_type
            class Pointer = T *,          // iterator::pointer
            class Reference = T &         // iterator::reference
    >
    class Random_access_iterator {

    public:
        //================================typedef===================================
        typedef T                                   value_type;
        typedef Distance                            difference_type;
        typedef Pointer                             pointer;
        typedef Reference                           reference;
        typedef Category                            iterator_category;

        typedef Random_access_iterator<Category,
                T, Distance, Pointer, Reference>    this_type;
        //================================get_tree_end typedef================================

        //============================constructors==================================
        Random_access_iterator() : arr_(0) {} //default
//        Random_access_iterator(Random_access_iterator const &src)
//                : arr_(src.get_arr()) {}//assign_node_no_value will it work if just ->
        Random_access_iterator(Random_access_iterator<Category, T, Distance, T *, T &> const &src)
                : arr_(src.get_arr()) {}//assign_node_no_value constr
        Random_access_iterator(pointer src) : arr_(src) {} //pointer constr
        //======================get_tree_end constructors====================================

        //============================destructor====================================
        ~Random_access_iterator() {}
        //============================get_tree_end destructor================================

        //============================assignation====================================
        this_type &operator=(Random_access_iterator const &rhs) {
            if (this == &rhs)
                return *this;
            arr_ = rhs.arr_;
            return *this;
        }
        //==========================end_assignation==================================

        //===========================other operators=================================
        // *
        reference operator*() const {
            return *arr_;
        }

        // ->
        pointer operator->() const {
            return arr_;
        }

        // ++it
        this_type operator++() {
            ++arr_;
            return (*this);
        }

        // it++ does *a++work?
        this_type operator++(int) {
            this_type tmp(*this);
            ++arr_;
            return (*this);
        }

        // --it
        this_type operator--() {
            --arr_;
            return (*this);
        }

        // it--
        this_type operator--(int) {
            this_type tmp(*this);
            --arr_;
            return (*this);
        }

        // it + n
        this_type operator+(difference_type n) const {
            return this_type(arr_ + n);
        }

        // it - n
        this_type operator-(difference_type n) const {
            return this_type(arr_ - n);
        }

        // it += n
        this_type operator+=(difference_type n) {
            arr_ += n;
            return (*this);
        }

        // it -= n
        this_type operator-=(difference_type n) {
            arr_ -= n;
            return (*this);
        }

        // it[n]
        Random_access_iterator operator[](difference_type n) const {
            return arr_[n];
        }
        //=========================get_tree_end other operators===============================

        //==============================getter=======================================
        pointer get_arr() const {
            return arr_;
        }
        //============================get_tree_end getter=====================================

    private:
        pointer arr_;
    };
    //=========================get_tree_end random access class===============================

    //=========================relational operators===============================

    // it == it
    template<class lC, class lT, class lD, class lP, class lR,
            class rC, class rT, class rD, class rP, class rR>
    bool operator==
            (
                    const Random_access_iterator<lC, lT, lD, lP, lR> &lhs,
                    const Random_access_iterator<rC, rT, rD, rP, rR> &rhs
            ) {
        return lhs.get_arr() == rhs.get_arr();
    }

    // it != it
    template<class lC, class lT, class lD, class lP, class lR,
            class rC, class rT, class rD, class rP, class rR>
    bool operator!=
            (
                    const Random_access_iterator<lC, lT, lD, lP, lR> &lhs,
                    const Random_access_iterator<rC, rT, rD, rP, rR> &rhs
            ) {
        return lhs.get_arr() != rhs.get_arr();
    }

    // it > it
    template<class lC, class lT, class lD, class lP, class lR,
            class rC, class rT, class rD, class rP, class rR>
    bool operator>
            (
                    const Random_access_iterator<lC, lT, lD, lP, lR> &lhs,
                    const Random_access_iterator<rC, rT, rD, rP, rR> &rhs
            ) {
        return lhs.get_arr() > rhs.get_arr();
    }

    // it < it
    template<class lC, class lT, class lD, class lP, class lR,
            class rC, class rT, class rD, class rP, class rR>
    bool operator<
            (
                    const Random_access_iterator<lC, lT, lD, lP, lR> &lhs,
                    const Random_access_iterator<rC, rT, rD, rP, rR> &rhs
            ) {
        return lhs.get_arr() < rhs.get_arr();
    }

    // it >= it
    template<class lC, class lT, class lD, class lP, class lR,
            class rC, class rT, class rD, class rP, class rR>
    bool operator>=
            (
                    const Random_access_iterator<lC, lT, lD, lP, lR> &lhs,
                    const Random_access_iterator<rC, rT, rD, rP, rR> &rhs
            ) {
        return lhs.get_arr() >= rhs.get_arr();
    }

    // it <= it
    template<class lC, class lT, class lD, class lP, class lR,
            class rC, class rT, class rD, class rP, class rR>
    bool operator<=
            (
                    const Random_access_iterator<lC, lT, lD, lP, lR> &lhs,
                    const Random_access_iterator<rC, rT, rD, rP, rR> &rhs
            ) {
        return lhs.get_arr() <= rhs.get_arr();
    }

    // n + it
    template<class C, class T, class D, class P, class R>
    Random_access_iterator<C, T, D, P, R> operator+
            (
                    typename Random_access_iterator<C, T, D, P, R>::difference_type n,
                    Random_access_iterator<C, T, D, P, R> const &rhs
            ) {
        return rhs + n;
    }

    // it - it
    template<class lC, class lT, class lD, class lP, class lR,
            class rC, class rT, class rD, class rP, class rR>
    typename Random_access_iterator<lC, lT, lD, lP, lR>::difference_type operator-
            (
                    const Random_access_iterator<lC, lT, lD, lP, lR> &lhs,
                    const Random_access_iterator<rC, rT, rD, rP, rR> &rhs
            ) {
        return lhs.get_arr() - rhs.get_arr();
    }
}
#endif //RANDOM_ACCESS_ITERATOR_HPP