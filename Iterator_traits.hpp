//
// Created by Namor Scarab on 2/23/22.
//

#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

#include <iostream>
#include <cstddef> // ptrdiff_t

namespace ft {

    template <class Iterator> struct iterator_traits {
        typedef typename Iterator::value_type            value_type;
        typedef typename Iterator::difference_type       difference_type;
        typedef typename Iterator::iterator_category     iterator_category;
        typedef typename Iterator::pointer               pointer;
        typedef typename Iterator::reference             reference;

    };

    template <class T> struct iterator_traits<T*> {
        typedef T                                        value_type;
        typedef std::ptrdiff_t                           difference_type;
        typedef std::random_access_iterator_tag          iterator_category;
        typedef T*                                       pointer;
        typedef T&                                       reference;
    };

    template <class T> struct iterator_traits<const T*> {
        typedef T                                        value_type;
        typedef std::ptrdiff_t                           difference_type;
        typedef std::random_access_iterator_tag          iterator_category;
        typedef const T*                                 pointer;
        typedef const T&                                 reference;
    };
}

#endif //ITERATOR_TRAITS_HPP
