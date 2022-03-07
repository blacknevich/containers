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
//=============================end enable if=================================

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

//=============================end is integral===============================

//==================================swap=====================================
    template <typename T>
    void swap(T &a, T &b) {
        T c(a);

        a = b;
        b = c;
    }
//================================end swap===================================
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
}
#endif //UTILS_HPP
