//
// Created by Namor Scarab on 2/23/22.
//

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include <iostream>
#include "Random_access_iterator.hpp"
#include "utils.hpp"

namespace ft {

    template<class Iterator>
    class Reverse_iterator {

    public:
        //================================typedef===================================
        typedef Iterator                                                    iterator_type;
        typedef typename Iterator::iterator_category                        iterator_category;
        typedef typename Iterator::value_type                               value_type;
        typedef typename Iterator::difference_type                          difference_type;
        typedef typename Iterator::pointer                                  pointer;
        typedef typename Iterator::reference                                reference;
        //================================end typedef================================

        //============================constructors==================================
        Reverse_iterator() : current() {} //default
        explicit Reverse_iterator(iterator_type it) : current(it) {} //initialization
        template<class Iter>
        Reverse_iterator(const Reverse_iterator<Iter> &rev_it) : current(rev_it.base()) {} //assign_node_no_value
        //======================end constructors====================================

        //============================destructor====================================
        ~Reverse_iterator() {}
        //============================end destructor================================

        //============================member functions==============================
        iterator_type base() const {
            return current;
        }
        //============================end member functions==========================

        //============================operators====================================
        // rev = rev
        Reverse_iterator &operator=(Reverse_iterator const &rhs) {
            if (this == &rhs)
                return *this;
            Reverse_iterator tmp = rhs.base();
            --rhs.base();
            current = tmp;
            return *this;
        }

        // *
        reference operator*() const {
            return *current;
        }

        // ->
        pointer operator->() const {
//            return current.get_arr_();
            return current.operator->();
        }

        // ++rev
        Reverse_iterator operator++() {
            --current;
            return (*this);
        }

        // rev++
        Reverse_iterator operator++(int) {
            Reverse_iterator tmp(*this);
            --current;
            return (*this);
        }

        // --rev
        Reverse_iterator operator--() {
            ++current;
            return (*this);
        }

        // rev--
        Reverse_iterator operator--(int) {
            Reverse_iterator tmp(*this);
            ++current;
            return (*this);
        }

        // it + n
        Reverse_iterator operator+(difference_type n) const {
            return Reverse_iterator(current - n);
        }

        // it - n
        Reverse_iterator operator-(difference_type n) const {
            return Reverse_iterator(current + n);
        }

        // it += n
        Reverse_iterator operator+=(difference_type n) {
            current -= n;
            return (*this);
        }

        // it -= n
        Reverse_iterator operator-=(difference_type n) {
            current += n;
            return (*this);
        }
        // rev < rev
        bool operator<(Reverse_iterator const &rhs) const {
            return current > rhs.base();
        }

        // rev > rev
        bool operator>(Reverse_iterator const &rhs) const {
            return current < rhs.base();
        }

        // rev <= rev
        bool operator<=(Reverse_iterator const &rhs) const {
            return current >= rhs.base();
        }

        // rev >= rev
        bool operator>=(Reverse_iterator const &rhs) const {
            return current <= rhs.base();
        }

        // rev[n]
        Reverse_iterator operator[](difference_type n) const {
            return current[-n];
        }
        //==========================end operators==================================
    protected:
        iterator_type current;
    };
    //=========================end return iterator class===============================

    //=========================relational operators===============================

    // rev == rev
    template<class lIterator, class rIterator>
    bool operator==
            (
                    const Reverse_iterator<lIterator> &lhs,
                    const Reverse_iterator<rIterator> &rhs
            ) {
        return lhs.base() == rhs.base();
    }

    // rev != rev
    template<class lIterator, class rIterator>
    bool operator!=
            (
                    const Reverse_iterator<lIterator> &lhs,
                    const Reverse_iterator<rIterator> &rhs
            ) {
        return lhs.base() != rhs.base();
    }

    // rev < rev
    template<class lIterator, class rIterator>
    bool operator<
            (
                    const Reverse_iterator<lIterator> &lhs,
                    const Reverse_iterator<rIterator> &rhs
            ) {
        return lhs.base() > rhs.base();
    }

    // rev <= rev
    template<class lIterator, class rIterator>
    bool operator<=
            (
                    const Reverse_iterator<lIterator> &lhs,
                    const Reverse_iterator<rIterator> &rhs
            ) {
        return lhs.base() >= rhs.base();
    }

    // rev > rev
    template<class lIterator, class rIterator>
    bool operator>
            (
                    const Reverse_iterator<lIterator> &lhs,
                    const Reverse_iterator<rIterator> &rhs
            ) {
        return lhs.base() < rhs.base();
    }

    // rev >= rev
    template<class lIterator, class rIterator>
    bool operator>=
            (
                    const Reverse_iterator<lIterator> &lhs,
                    const Reverse_iterator<rIterator> &rhs
            ) {
        return lhs.base() <= rhs.base();
    }

    // n + rev
    template<class Iterator>
    Reverse_iterator<Iterator> operator+
            (
                    typename Reverse_iterator<Iterator>::difference_type n,
                    const Reverse_iterator <Iterator> &rev_i
            )
    {
        return rev_i + n;
    }

    // iter - iter
    template <class Iterator>
    typename Reverse_iterator<Iterator>::difference_type operator-
    (
            const Reverse_iterator<Iterator>& lhs,
            const Reverse_iterator<Iterator>& rhs
            )
    {
        return rhs.base() - lhs.base();
    }
}


#endif //REVERSE_ITERATOR_HPP
