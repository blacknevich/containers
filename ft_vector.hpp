//
// Created by Namor Scarab on 2/15/22.
//

#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

//==================================lib includes===================================
#include <iostream>
#include <cstddef> // size_t , ?ptrdiff_t
#include <memory> // allocator
#include <exception> // exception
#include <cstring> // ?memmove
#include <limits> // ?numeric_limit=
//================================local includes===================================
#include "Random_access_iterator.hpp"
#include "Reverse_iterator.hpp"
#include "Iterator_traits.hpp"
#include "utils.hpp"

namespace ft {

    template<
            class T,
            class Allocator = std::allocator<T>
    > class Vector {

    public:
        //================================typedef===================================
        typedef T                                                           value_type;
        typedef Allocator                                                   allocator_type;
        typedef typename allocator_type::reference                          reference;
        typedef typename allocator_type::const_reference                    const_reference;
        typedef typename allocator_type::pointer                            pointer;
        typedef typename allocator_type::const_pointer                      const_pointer;
        typedef typename allocator_type::size_type                          size_type;

        typedef ft::Random_access_iterator
//                        <std::random_access_iterator_tag, value_type, ptrdiff_t ,  T*, T&> iterator;
                <typename ft::iterator_traits<T*>::iterator_category,
                        typename ft::iterator_traits<T*>::value_type,
                        typename ft::iterator_traits<T*>::difference_type,
                        typename ft::iterator_traits<T*>::pointer,
                        typename ft::iterator_traits<T*>::reference>        iterator;
        typedef ft::Random_access_iterator
//                <std::random_access_iterator_tag, value_type, ptrdiff_t , const T*, const T&> const_iterator;
                <typename ft::iterator_traits<const T*>::iterator_category,
                        typename ft::iterator_traits<const T*>::value_type,
                        typename ft::iterator_traits<const T*>::difference_type,
                        typename ft::iterator_traits<const T*>::pointer,
                        typename ft::iterator_traits<const T*>::reference>  const_iterator;
        typedef ft::Reverse_iterator<iterator>                              reverse_iterator;
        typedef ft::Reverse_iterator<const_iterator>                        const_reverse_iterator;
        typedef typename ft::iterator_traits<iterator>::difference_type     difference_type;
        //================================end typedef===============================

        //=============================private variables============================
    private:
        pointer arr_;
        size_type size_;
        size_type capacity_;
        allocator_type alloc_;
        //===========================end private variables==========================

    public:
        //============================constructors==================================
        explicit Vector (const allocator_type& alloc = allocator_type()) :
        arr_(0), size_(0), capacity_(0), alloc_(alloc) {
        } //default

        explicit Vector (
                size_type n,
                const value_type& val = value_type(),
                const allocator_type& alloc = allocator_type()
                        ) : arr_(0), size_(n), capacity_(n), alloc_(alloc) {
            try {
                arr_ = alloc_.allocate(n);
            }
            catch (std::exception& e) {
                throw Vector::FtLengthError();
            }
            for (size_type i = 0; i < n; ++i)
                alloc_.construct(arr_ + i, val);
        } //fill

        template <class InputIterator>
        Vector (
                InputIterator first, InputIterator last,
                const allocator_type& alloc = allocator_type(),
                typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = 0
        ) : arr_(0), size_(0), capacity_(0), alloc_(alloc) {
            //typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = 0
            //std::enable_if_t<std::is_base_of<std::input_iterator_tag,
            //typename std::iterator_traits<InputIterator>::iterator_category>::value, int> = 0>
            capacity_ = std::distance(first, last);
            size_ = capacity_;

            try {
                arr_ = alloc_.allocate(size_);
            }
            catch (std::exception& e) {
                throw Vector::FtLengthError();
            }

            for (size_type i = 0; i < size_; ++i){
                alloc_.construct(arr_ + i, *first);
                ++first;
            }
        } //range

        Vector (const Vector& x)
                : arr_(0), size_(x.size_), capacity_(x.capacity_), alloc_(x.alloc_) {
            arr_ = alloc_.allocate(x.capacity_);
            for (size_type i = 0; i < x.size_; ++i) {
                alloc_.construct(arr_ + i, x[i]);
            }
            //this->operator=(x);
        }//copy
        //======================end constructors====================================

        //============================destructor====================================
        ~Vector() {
            clear();
            alloc_.deallocate(arr_, capacity_);
            arr_ = 0;
            size_ = 0;
            capacity_ = 0;
        }
        //============================end destructor================================

        //=======================assignation operator===============================
        //if copy constructable calls for a copy constructor, if assignable - will
        // call an assignation, otherwise will directly copy; assignation prevails!!!
        //but if no element exists copy is used
        //only destroys those that above size
        //resize calls for default const only!
       Vector& operator= (const Vector& x) {
            if (this == &x)
                return (*this);
            clear();
            if (x.capacity() > capacity_){
                pointer tmp_arr = alloc_.allocate(x.capacity());
                alloc_.deallocate(arr_, capacity_);
                capacity_ = x.capacity();
                arr_ = tmp_arr;
            }
            for (size_type i = 0; i < x.size_; ++i) {
                alloc_.construct(arr_ + i, x[i]);
            }
            size_ = x.size_;
            return (*this);
        }
        //===================end assignation operator===============================

        //============================iterators====================================
        iterator begin() {
            return iterator(arr_);
        }

        const_iterator begin() const {
            return const_iterator(arr_);
        }

        iterator end() {
            return iterator(arr_ + size_);
        }

        const_iterator end() const {
            return const_iterator(arr_ + size_);
        }

        reverse_iterator rbegin() {
            return reverse_iterator(iterator(arr_ + size_ - 1));
        }

        const_reverse_iterator rbegin() const {
            return const_reverse_iterator(const_iterator(arr_ + size_ - 1));
        }

        reverse_iterator rend() {
            return reverse_iterator(iterator(arr_ - 1));

        }

        const_reverse_iterator rend() const {
            return const_reverse_iterator(const_iterator(arr_ - 1));
        }
        //==========================end_iterators==================================

        //==============================capacity====================================
        size_type size() const {
            return (size_);
        }

        size_type max_size() const {
            return alloc_.max_size();
        }

        void resize (size_type n, value_type val = value_type()) {

            if (n > max_size()) {
                throw FtLengthError();
            }
            if (n < size_) { //delete excessive elements
                for (size_type i = n; i < size_; ++i)
                    alloc_.destroy(arr_ + i);
                size_ = n;
            }
//            else
//                insert(end(), n, val);
            else if (n <= capacity_) { //construct more elements
                for (size_type i = size_; i < n; ++i)
                    alloc_.construct(arr_ + i, val);
                size_ = n;
            }
            else { //allocate more space and construct
               if (2 * size_ > n && 2 * size_ <= max_size())
                   reserve(2 * size_);
               else reserve(n);
                for (size_type i = size_; i < n; ++i)
                    alloc_.construct(arr_ + i, val);
                size_ = n;
            }
        }

        size_type capacity() const {
            return capacity_;
        }

        bool empty() const {
            return size_ == 0;
        }

        void reserve (size_type n) {
            if (n <= capacity_)
                return;
//            if (n > max_size()) {
//                throw FtLengthError();
//            }
            pointer tmp_arr;

            tmp_arr = alloc_.allocate(n);

            std::memmove(tmp_arr, arr_, sizeof(value_type) * size_);
            alloc_.deallocate(arr_, capacity_);
            capacity_ = n;
            arr_ = tmp_arr;
        }
        //==========================end capacity====================================

        //==========================element access==================================
        reference operator[] (size_type n) {
            return arr_[n];
        }

        const_reference operator[] (size_type n) const {
            return arr_[n];
        }

        reference at (size_type n) {
            if (n >= size_)
                throw FtOutOfRange();
            return arr_[n];
        }

        const_reference at (size_type n) const {
            if (n >= size_)
                throw FtOutOfRange();
            return arr_[n];
        }

        reference front() {
            return *arr_;
        }

        const_reference front() const {
            return *arr_;
        }

        reference back() {
            return arr_[size_ - 1];
        }

        const_reference back() const {
            return arr_[size_ - 1];
        }
        //=======================end element access=================================

        //=============================modifiers====================================
        template <class InputIterator>
        void assign
                (
                        InputIterator first,
                        InputIterator last,
                        typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = 0
                )
        {
            Vector backup(first, last);
            difference_type size_new = std::distance(first, last);

            clear();
            reserve(size_new);
            insert(begin(), backup.begin(), backup.end());
        } //range

        void assign (size_type n, const value_type& val) {
            value_type backup(val);

            clear();
            reserve(n);
            insert(begin(), n, backup);
        } //fill

        void push_back (const value_type& val) {
            insert(end(), val);
        }

        void pop_back() {
            alloc_.destroy(arr_ + size_ - 1);
            --size_;
        }

        iterator insert (iterator position, const value_type& val) {
            return insert(position, 1, val);
        }; //single element

        iterator insert (iterator position, size_type n, const value_type& val) {

            size_type position_index = (position - begin()); //insert before

            if (n <= 0)
                return position;
            if (size_ + n > max_size()) {
                throw FtLengthError();
            }
            //new capacity is 2x or size + n
            size_type new_capacity;
            if (size_ + n <= capacity_)
                new_capacity = capacity_;
            else if (size_ > n && 2 * size_ <= max_size())
                new_capacity = 2 * size_;
            else new_capacity = size_ + n;

            pointer tmp_arr;
            tmp_arr = alloc_.allocate(new_capacity);

            //first part move
            if (position_index > 0)
                std::memmove(tmp_arr, arr_, sizeof(value_type) * position_index);
//            for (size_type i = 0; i < position_index; ++i)
//                alloc_.construct(tmp_arr + i, arr_[i]);

            //second part move
            if (size_ - position_index > 0)
                std::memmove(tmp_arr + position_index + n, arr_ + position_index,
                             sizeof(value_type) * (size_ - position_index));
//            for (size_type i = 0; i < size_ - position_index; ++i)
//                alloc_.construct(tmp_arr + position_index + n + i, arr_ + position_index + i);

            //fill between
            for (size_type i = 0; i < n; ++i)
                alloc_.construct(tmp_arr + position_index + i, val);

            alloc_.deallocate(arr_, capacity_);
            capacity_ = new_capacity;
            arr_ = tmp_arr;
//            else {
//                //second part move
//                if (size_ - position_index > 0)
//                std::memmove(arr_ + position_index + n, arr_ + position_index,
//                             sizeof(value_type) * (size_ - position_index));
//
//                //fill between
//                for (size_type i = 0; i < n; ++i)
//                    alloc_.construct(arr_ + position_index + i, val);
//            }
            size_ += n;
            return position;
        }; //fill

        template <class InputIterator>
        iterator insert (
                iterator position,
                InputIterator first,
                InputIterator last,
                typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = 0
        )
        {
            size_type position_index = position - begin(); //insert before
            size_type n = std::distance(first, last);

            if (n <= 0 || (n > 0 && size_ > std::numeric_limits<size_type>::max() - n))
                return position;
            if (size_ + n > max_size()) {
                throw FtLengthError();
            }
            pointer tmp_arr;

            //new capacity is 2x or size + n
            size_type new_capacity;
            if (size_ + n <= capacity_)
                new_capacity = capacity_;
            else if (size_ > n && 2 * size_ <= max_size())
                new_capacity = 2 * size_;
            else new_capacity = size_ + n;

            tmp_arr = alloc_.allocate(new_capacity);

            //first part move
            if (position_index > 0)
                std::memmove(tmp_arr, arr_, sizeof(value_type) * position_index);
//            for (size_type i = 0; i < position_index; ++i)
//                alloc_.construct(tmp_arr + i, arr_[i]);

            //second part move
            if (size_ - position_index > 0)
                std::memmove(tmp_arr + position_index + n, arr_ + position_index,
                         sizeof(value_type) * (size_ - position_index));
//            for (size_type i = 0; i < size_ - position_index; ++i)
//                alloc_.construct(tmp_arr + position_index + n + i, arr_ + position_index + i);

            //fill between
            std::copy(first, last, tmp_arr + position_index);
//            for (size_type i = 0; i < n; ++i)
//                alloc_.construct(tmp_arr + position_index + i, *(first + i));
            alloc_.deallocate(arr_, capacity_);
            capacity_ = new_capacity;
            arr_ = tmp_arr;
//            else {
//                //second part move
//                std::memmove(arr_ + position_index + n, arr_ + position_index,
//                             sizeof(value_type) * (size_ - position_index));
//
//                //fill between
//                std::copy(first, last, arr_ + position_index);
//            }
            size_ += n;
            return position;
        };

        iterator erase (iterator position) {
            difference_type span = position - begin();
            if (size_ == 0)
                return (iterator(arr_+ span));
            alloc_.destroy(arr_ + span);
            --size_;
            std::memmove(arr_ + span, arr_ + span + 1, sizeof(value_type) * (size_ - span));
            return (iterator(arr_+ span));
        }

        iterator erase (iterator first, iterator last) {
            if (std::distance(first, last) < 0)
                return arr_;
            difference_type span = first - begin();
            while (first != last) {
                erase(first);
                --last;
            }
            return (iterator(arr_+ span));
        }

        void swap(Vector & x) {
            ft::swap(arr_, x.arr_);
            ft::swap(size_, x.size_);
            ft::swap(capacity_, x.capacity_);
            ft::swap(alloc_, x.alloc_);
        }

        void clear() {

            if (arr_ != 0) {
                for (size_type i = 0; i < size_; ++i)
                    alloc_.destroy(arr_ + i);
            }
            size_ = 0;
        }
        //===========================end_modifiers==================================

        //=============================allocator====================================
        allocator_type get_allocator() const {
            return alloc_;
            //return allocator_type(alloc_);
        }
        //===========================end allocator==================================

        //============================exceptions====================================
        class FtLengthError : public std::exception{
            const char* what() const throw() {
                return ("vector");
            }
        };

        class FtOutOfRange : public std::exception{
            const char* what() const throw() {
                return ("vector");
            }
        };
        //============================end exceptions=================================
    };
    //================================end class vector===============================

    //================================non member functions===========================
    template <class T, class Alloc>
    bool operator== (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) {

        if (lhs.size() != rhs.size())
            return false;
        int count = 0;
        for (size_t i = 0; i < lhs.size(); ++i) {
            if (lhs[count] != rhs[count])
                return false;
        }
        return true;
    }

    template <class T, class Alloc>
    bool operator!= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) {
        return !(lhs == rhs);
    }

    template <class T, class Alloc>
    bool operator<  (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(),
                                    rhs.begin(), rhs.end());
    }

    template <class T, class Alloc>
    bool operator<= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) {
        return !(rhs < lhs);
    }

    template <class T, class Alloc>
    bool operator>  (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) {
        return rhs < lhs;
    }

    template <class T, class Alloc>
    bool operator>= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) {
        return !(lhs < rhs);
    }

    template <class T, class Alloc>
    void swap (Vector<T,Alloc>& x, Vector<T,Alloc>& y) {
        x.swap(y);
    }
    //==============================end non member functions=========================
}
#endif //FT_VECTOR_HPP
