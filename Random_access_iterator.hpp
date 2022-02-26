//
// Created by Namor Scarab on 2/22/22.
//

#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include <cstddef> // ptrdiff_t
#include "Iterator_traits.hpp"

namespace ft {

    template <class Category,            // iterator::iterator_category
            class T,                     // iterator::value_type
            class Distance = ptrdiff_t,  // iterator::difference_type
            class Pointer = T*,          // iterator::pointer
            class Reference = T&         // iterator::reference
    > class Random_access_iterator {

    public:
        //================================typedef===================================
        typedef T                                                   value_type;
        typedef Distance                                            difference_type;
        typedef Pointer                                             pointer;
        typedef Reference                                           reference;
        typedef Category                                            iterator_category;
        //typedef Random_access_iterator<Category, T, Distance,
        //Pointer, Reference>                                         this_type;
        //================================end typedef================================

        //============================constructors==================================
        Random_access_iterator() : arr_(0) {} //default
        Random_access_iterator(Random_access_iterator const &src)
                : arr_(src.arr_) {}//copy will it work if just ->

        Random_access_iterator(pointer src) : arr_(src) {} //pointer constr
        //======================end constructors====================================

        //============================destructor====================================
        ~Random_access_iterator() {}
        //============================end destructor================================

        //============================assignation====================================
        Random_access_iterator &operator=(Random_access_iterator const &rhs) {
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
        Random_access_iterator operator++() {
            ++arr_;
            return (*this);
        }

        // it++ does *a++work?
        Random_access_iterator operator++(int) {
            Random_access_iterator tmp(*this);
            ++arr_;
            return (*this);
        }

        // --it
        Random_access_iterator operator--() {
            --arr_;
            return (*this);
        }

        // it--
        Random_access_iterator operator--(int) {
            Random_access_iterator tmp(*this);
            --arr_;
            return (*this);
        }

        // it + n
        Random_access_iterator operator+(difference_type n) const {
            return Random_access_iterator(arr_ + n);
        }

        // n + it - non member
        friend Random_access_iterator operator+
                (difference_type n,
                 Random_access_iterator const & rhs) {
            return rhs + n;
        }

        // it - n
        Random_access_iterator operator-(difference_type n) const {
            return Random_access_iterator(arr_ - n);
        }

        // it - it - non member
        friend difference_type operator-
        (Random_access_iterator const & lhs,
         Random_access_iterator const & rhs) {
            return lhs.get_arr() - rhs.get_arr();
        }

        // it += n
        Random_access_iterator operator+=(difference_type n) {
            arr_ += n;
            return (*this);
        }

        // it -= n
        Random_access_iterator operator-=(difference_type n) {
            arr_ -= n;
            return (*this);
        }

        // <
        friend bool operator<(Random_access_iterator const &lhs,
                              Random_access_iterator const &rhs) {
            return lhs.arr_ < rhs.arr_;
        }

        // >
        friend bool operator>(Random_access_iterator const &lhs,
                              Random_access_iterator const &rhs) {
            return lhs.arr_ > rhs.arr_;
        }

        // <=
        friend bool operator<=(Random_access_iterator const &lhs,
                               Random_access_iterator const &rhs) {
            return lhs.arr_ <= rhs.arr_;
        }

        // >=
        friend bool operator>=(Random_access_iterator const &lhs,
                               Random_access_iterator const &rhs) {
            return lhs.arr_ >= rhs.arr_;
        }
        // it[n]
        Random_access_iterator operator[](difference_type n) const {
            return arr_[n];
        }
        //=========================end other operators===============================

        //==============================getter=======================================
        pointer get_arr() const {
            return arr_;
        }
        //============================end getter=====================================

    private:
        pointer arr_;
    };
    //=========================end random access class===============================

    //=========================relational operators===============================

    // it == it
    template <class lC, class lT, class lD, class lP, class lR,
            class rC, class rT, class rD, class rP, class rR>
    bool operator==
            (
                    const Random_access_iterator<lC, lT, lD, lP, lR> & lhs,
                    const Random_access_iterator<rC, rT, rD, rP, rR> & rhs
            )
    {
        return lhs.get_arr() == rhs.get_arr();
    }

    // it != it
    template <class lC, class lT, class lD, class lP, class lR,
            class rC, class rT, class rD, class rP, class rR>
    bool operator!=
            (
                    const Random_access_iterator<lC, lT, lD, lP, lR> & lhs,
                    const Random_access_iterator<rC, rT, rD, rP, rR> & rhs
            )
    {
        return lhs.get_arr() != rhs.get_arr();
    }
    // it > it
    template <class lC, class lT, class lD, class lP, class lR,
            class rC, class rT, class rD, class rP, class rR>
    bool operator>
            (
                    const Random_access_iterator<lC, lT, lD, lP, lR> & lhs,
                    const Random_access_iterator<rC, rT, rD, rP, rR> & rhs
            )
    {
        return lhs.get_arr() > rhs.get_arr();
    }

    // it < it
    template <class lC, class lT, class lD, class lP, class lR,
            class rC, class rT, class rD, class rP, class rR>
    bool operator<
            (
                    const Random_access_iterator<lC, lT, lD, lP, lR> & lhs,
                    const Random_access_iterator<rC, rT, rD, rP, rR> & rhs
            )
    {
        return lhs.get_arr() < rhs.get_arr();
    }
    // it >= it
    template <class lC, class lT, class lD, class lP, class lR,
            class rC, class rT, class rD, class rP, class rR>
    bool operator>=
            (
                    const Random_access_iterator<lC, lT, lD, lP, lR> & lhs,
                    const Random_access_iterator<rC, rT, rD, rP, rR> & rhs
            )
    {
        return lhs.get_arr() >= rhs.get_arr();
    }
    // it <= it
    template <class lC, class lT, class lD, class lP, class lR,
            class rC, class rT, class rD, class rP, class rR>
    bool operator<=
            (
                    const Random_access_iterator<lC, lT, lD, lP, lR> & lhs,
                    const Random_access_iterator<rC, rT, rD, rP, rR> & rhs
            )
    {
        return lhs.get_arr() <= rhs.get_arr();
    }

    // n + it
    template <class C, class T, class D, class P, class R>
    Random_access_iterator<C, T, D, P, R> operator+
            (
                    typename Random_access_iterator<C, T, D, P, R>::difference_type n,
                    Random_access_iterator<C, T, D, P, R> const & rhs
            )
    {
        return rhs + n;
    }

    // it - it
    template <class lC, class lT, class lD, class lP, class lR,
            class rC, class rT, class rD, class rP, class rR>
    typename Random_access_iterator<lC, lT, lD, lP, lR>::difference_type operator-
            (
                    const Random_access_iterator<lC, lT, lD, lP, lR> & lhs,
                    const Random_access_iterator<rC, rT, rD, rP, rR> & rhs
            )
    {
        return rhs.get_arr() - lhs.get_arr();
    }

    // distance(it, it)
    template< class InputIt >
    typename ft::iterator_traits<InputIt>::difference_type distance
            (
                    InputIt first,
                    InputIt last
            )
    {
        typename ft::iterator_traits<InputIt>::difference_type count = 0;
        while (first != last) {
            ++first;
            ++count;
        }
        return (count);
    }
}

#endif //RANDOM_ACCESS_ITERATOR_HPP