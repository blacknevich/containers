//
// Created by Namor Scarab on 2/24/22.
//

#ifndef UTILS_HPP
#define UTILS_HPP


#include <iostream>

namespace ft {
//===============================enable if===================================
    template<bool B, class T = void>
    struct enable_if {};

    template<class T>
    struct enable_if<true, T> { typedef T type; };
//=============================get_tree_end enable if=================================

//===============================is integral=================================
    template<typename T, bool is_integral_bool>
    struct is_integral_type_bool {
        typedef T type;

        static const bool value = is_integral_bool;
    };

    template<typename>
    struct is_integral : public is_integral_type_bool<bool, false> {};

    template<>
    struct is_integral<bool> : public is_integral_type_bool<bool, true> {};

    template<>
    struct is_integral<char> : public is_integral_type_bool<char, true> {};

    template<>
    struct is_integral<wchar_t> : public is_integral_type_bool<wchar_t, true> {};

    template<>
    struct is_integral<short> : public is_integral_type_bool<short, true> {};

    template<>
    struct is_integral<int> : public is_integral_type_bool<int, true> {};

    template<>
    struct is_integral<long> : public is_integral_type_bool<long, true> {};

    template<>
    struct is_integral<long long> : public is_integral_type_bool<long long, true> {};

// other signed/unsigned

    template<>
    struct is_integral<signed char> : public is_integral_type_bool<signed char, true> {};

    template<>
    struct is_integral<unsigned char> : public is_integral_type_bool<unsigned char, true> {};

    template<>
    struct is_integral<unsigned short> : public is_integral_type_bool<unsigned short, true> {};

    template<>
    struct is_integral<unsigned long> : public is_integral_type_bool<unsigned long, true> {};

    template<>
    struct is_integral<unsigned long long> : public is_integral_type_bool<unsigned long long, true> {};

//=============================get_tree_end is integral===============================

//====================lexicographical compare================================
    template <class InputIterator1, class InputIterator2>
    bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                  InputIterator2 first2, InputIterator2 last2)
    {
        while (first1!=last1)
        {
            if (first2==last2 || *first2<*first1)
                return false; // if first range is more
            else if (*first1<*first2)
                return true; // if first range is less
            ++first1;
            ++first2;
        }
        return (first2!=last2); //if 1st range is over but 2nd is not => 1st is less(true)
    }
//====================lexicographical compare================================
//================================equal======================================
    template<class InputIt1, class InputIt2>
    bool equal(InputIt1 first1, InputIt1 last1,
               InputIt2 first2)
    {
        for (; first1 != last1; ++first1, ++first2) {
            if (!(*first1 == *first2)) {
                return false;
            }
        }
        return true;
    }
//==============================end_equal====================================
//===========================iterator_traits=================================
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
//=========================get_tree_end iterator_traits===============================
//=================================pair======================================
    template <class T1, typename T2>
    struct pair {

        typedef T1	first_type;
        typedef T2	second_type;

        first_type	first;
        second_type	second;

        pair () : first(), second() {}

        pair (const first_type &x, const second_type &y) : first(x), second(y) {}

        template <class U1, class U2>
        pair (const pair<U1, U2> &p) : first(p.first), second(p.second) {}

        pair &operator = ( const pair &src ) {
            if (this == &src)
                return *this;
            first = src.first;
            second = src.second;
            return *this;
        }
    };

    template< class T1, class T2 >
    ft::pair<T1,T2> make_pair( T1 t, T2 u ) {
        return ft::pair<T1, T2>(t, u);
    }

    template< class T1, class T2 >
    bool operator==( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }

    template< class T1, class T2 >
    bool operator!=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {
        return !(lhs == rhs);
    }

    template< class T1, class T2 >
    bool operator<( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {
        return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second );
    }

    template< class T1, class T2 >
    bool operator<=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {
        return !(rhs < lhs);
    }

    template< class T1, class T2 >
    bool operator>( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {
        return rhs < lhs;
    }

    template< class T1, class T2 >
    bool operator>=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {
        return !(lhs < rhs);
    }
//===============================get_tree_end pair====================================

//===============================iterator====================================
    template <class Category, class T, class Distance = ptrdiff_t,
			class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef T        	value_type;
		typedef Distance 	difference_type;
		typedef Pointer  	pointer;
		typedef Reference	reference;
		typedef Category 	iterator_category;
	};
//=============================get_tree_end iterator==================================
}
#endif //UTILS_HPP
