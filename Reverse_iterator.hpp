//
// Created by Namor Scarab on 2/23/22.
//

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include <iostream>
#include "Random_access_iterator.hpp"
#include "Iterator_traits.hpp"

namespace ft {

    template<class Iterator>
    class Reverse_iterator {

    public:
        //================================typedef===================================
        typedef Iterator                                                     iterator_type;
        typedef typename ft::iterator_traits<Iterator>::iterator_category    iterator_category;
        typedef typename ft::iterator_traits<Iterator>::value_type           value_type;
        typedef typename ft::iterator_traits<Iterator>::difference_type      difference_type;
        typedef typename ft::iterator_traits<Iterator>::pointer              pointer;
        typedef typename ft::iterator_traits<Iterator>::reference            reference;
        //================================end typedef================================

        //============================constructors==================================
        Reverse_iterator() : it_() {} //default
        explicit Reverse_iterator(iterator_type it) : it_(it - 1) {} //initialization
        template<class Iter>
        Reverse_iterator(const Reverse_iterator<Iter> &rev_it) : it_(rev_it.base() - 1) {} //copy
        //======================end constructors====================================

        //============================destructor====================================
        ~Reverse_iterator() {}
        //============================end destructor================================

        //============================member functions==============================
        iterator_type base() const {
            return (it_ + 1);
        }
        //============================end member functions==========================

        //============================operators====================================
        // rev = rev
        Reverse_iterator &operator=(Reverse_iterator const &rhs) {
            if (this == &rhs)
                return *this;
            it_ = rhs.base() - 1;
            return *this;
        }

        // *
        reference operator*() const {
            return *it_;
        }

        // ->
        pointer operator->() const {
            return it_.get_arr_();
        }

        // ++rev
        Reverse_iterator operator++() {
            --it_;
            return (*this);
        }

        // rev++
        Reverse_iterator operator++(int) {
            Reverse_iterator tmp(*this);
            --it_;
            return (*this);
        }

        // --rev
        Reverse_iterator operator--() {
            ++it_;
            return (*this);
        }

        // rev--
        Reverse_iterator operator--(int) {
            Reverse_iterator tmp(*this);
            ++it_;
            return (*this);
        }

        // it + n
        Reverse_iterator operator+(difference_type n) const {
            return Reverse_iterator(it_ - n);
        }

        // it - n
        Reverse_iterator operator-(difference_type n) const {
            return Reverse_iterator(it_ + n);
        }

        // it += n
        Reverse_iterator operator+=(difference_type n) {
            it_ -= n;
            return (*this);
        }

        // it -= n
        Reverse_iterator operator-=(difference_type n) {
            it_ += n;
            return (*this);
        }
/* transferred to non-member function overloads
        // rev < rev
        bool operator<(Reverse_iterator const &rhs) const {
            return base() > rhs.base();
        }

        // rev > rev
        bool operator>(Reverse_iterator const &rhs) const {
            return base() < rhs.base();
        }

        // rev <= rev
        bool operator<=(Reverse_iterator const &rhs) const {
            return base() >= rhs.base();
        }

        // rev >= rev
        bool operator>=(Reverse_iterator const &rhs) const {
            return base() <= rhs.base();
        }
*/
        // rev[n]
        Reverse_iterator operator[](difference_type n) const {
            return it_[-n];
        }
        //==========================end operators==================================
    private:
        iterator_type it_;
    };
    //=========================end return iterator class===============================

    //=========================relational operators===============================

    // rev == rev
    template<class Iterator>
    Reverse_iterator<Iterator> operator==
            (
                    Reverse_iterator<Iterator> const &lhs,
                    Reverse_iterator<Iterator> const &rhs
            ) {
        return lhs.base() == rhs.base();
    }

    // rev != rev
    template<class Iterator>
    Reverse_iterator<Iterator> operator!=
            (
                    Reverse_iterator<Iterator> const &lhs,
                    Reverse_iterator<Iterator> const &rhs
            ) {
        return lhs.base() != rhs.base();
    }

    // rev < rev
    template<class Iterator>
    Reverse_iterator<Iterator> operator<
            (
                    Reverse_iterator<Iterator> const &lhs,
                    Reverse_iterator<Iterator> const &rhs
            ) {
        return lhs.base() > rhs.base();
    }

    // rev <= rev
    template<class Iterator>
    Reverse_iterator<Iterator> operator<=
            (
                    Reverse_iterator<Iterator> const &lhs,
                    Reverse_iterator<Iterator> const &rhs
            ) {
        return lhs.base() >= rhs.base();
    }

    // rev > rev
    template<class Iterator>
    Reverse_iterator<Iterator> operator>
            (
                    Reverse_iterator<Iterator> const &lhs,
                    Reverse_iterator<Iterator> const &rhs
            ) {
        return lhs.base() < rhs.base();
    }

    // rev >= rev
    template<class Iterator>
    Reverse_iterator<Iterator> operator>=
            (
                    Reverse_iterator<Iterator> const &lhs,
                    Reverse_iterator<Iterator> const &rhs
            ) {
        return lhs.base() <= rhs.base();
    }

    // n + rev
    template<class Iterator>
    Reverse_iterator <Iterator> operator+
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
        return lhs.base() - rhs.base();
    }
}


#endif //REVERSE_ITERATOR_HPP
