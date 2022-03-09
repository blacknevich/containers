//
// Created by Namor Scarab on 2/15/22.
//

#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

//==================================lib includes===================================
//#include <iostream>
#include <cstddef> // size_t , ?ptrdiff_t
#include <memory> // allocator
#include <exception> // exception
#include <cstring> // ?memmove
#include <limits> // ?numeric_limit=
//================================local includes===================================
#include "Random_access_iterator.hpp"
#include "Reverse_iterator.hpp"
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
                typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0
        ) : arr_(0), size_(0), capacity_(0), alloc_(alloc) {
            //typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0
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
                : arr_(0), size_(x.size_), capacity_(x.size_), alloc_(x.alloc_) {
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
                return;
            }
//            else
//                insert(end(), n, val);

            if (n <= capacity_) { //construct more elements
                for (size_type i = size_; i < n; ++i)
                    alloc_.construct(arr_ + i, val);
                size_ = n;
                return;
            }

            if (n > capacity_) { //allocate more space and construct
               if (n > 2 * capacity_ && 2 * capacity_ <= max_size())
                   reserve(n);
               else
                   reserve(2 * capacity_);

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
//            for (size_type i = 0; i < size_; ++i) {
//                alloc_.construct(tmp_arr + i, arr_[i]);
//                alloc_.destroy(arr_ + i);
//            }
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

        T* data() {
            return (arr_);
        }

        const T* data() const {
            return (arr_);
        }

        //=======================end element access=================================

        //=============================modifiers====================================
        template <class InputIterator>
        void assign
                (
                        InputIterator first,
                        InputIterator last,
                        typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0
                )
        {
            difference_type size_new = std::distance(first, last);
            if (size_new < 0) {
                this->~Vector();
                throw FtLengthError();
            }
            Vector backup(first, last);

            clear();
            reserve(size_new);
            insert(begin(), backup.begin(), backup.end());


//            clear();
//            difference_type size_new = std::distance(first, last);
//            if (size_new < 0) {
//                this->~Vector();
//                throw FtLengthError();
//            }
//            if (size_new) {
//                if ((size_type)size_new > capacity_) {
//                    alloc_.deallocate(arr_, capacity_);
////               reserve(size_new);
//                    arr_ = alloc_.allocate(size_new);
//                }
//                std::copy(first, last, begin());
//            }
        } //range

        void assign (size_type n, const value_type& val) {
            value_type backup(val);

            clear();
            reserve(n);
            insert(begin(), n, backup);
        } //fill

        void push_back (const value_type& val) {
            const value_type backup = val;
            if (size_ == 0)
                reserve(1);
            else if (size_ == capacity_)
                reserve(capacity_ * 2);
            alloc_.construct(arr_ + size_, backup);
            ++size_;
//            insert(end(), val);
        }

        void pop_back() {
            alloc_.destroy(arr_ + size_ - 1);
            --size_;
        }

        iterator insert (iterator position, const value_type& val) {
            return insert(position, 1, val);
        }; //single element

        iterator insert (iterator position, size_type n, const value_type& val) {

            size_type insert_place_ind = position - begin();
            value_type backup_val(val);

//            if (size_ == 0 && position.get_arr() == arr_) {
//                for (size_type i = 0; i < n; ++i)
//                    push_back(val);
//                return iterator(arr_ + insert_place_ind);
//            }
//
            if (capacity_ >= size_ + n) {
                size_type end_index = (size_ == 0) ? 0 : size_ - 1;

                // moving from end to begin the part after insert place
                for (size_type i = insert_place_ind; i < size_; ++i, --end_index) {
                    memmove
                            (
                                    arr_ + end_index + n,
                                    arr_ + end_index,
                                    sizeof(value_type)
                            );
//                    alloc_.construct((arr_ + end_index + n), arr_[end_index - 1]);
//                    alloc_.destroy(arr_ + end_index - 1);
                }
                // inserting objects
                for (size_type i = 0; i < n; ++i) {
                    alloc_.construct(arr_ + insert_place_ind + i, backup_val);
                }
                size_ += n;
                return iterator(arr_ + insert_place_ind);
            }
            // capacity_ < size_ + n: allocate new memory
            size_type new_capacity = capacity_ * 2;

//            if (size_ > n && 2 * capacity_ <= max_size())
//                new_capacity = 2 * capacity_;
//            else new_capacity = size_ + n;

            if (new_capacity < size_ + n)
                new_capacity = size_ + n;

            difference_type backup_place(position - begin());

            reserve(new_capacity);
            insert(iterator(arr_ + backup_place), n, backup_val);
            return iterator(arr_ + insert_place_ind);

        }; //fill

        template <class InputIterator>
        iterator insert (
                iterator position,
                InputIterator first,
                InputIterator last,
                typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0
        )
        {
            size_type position_index = position - begin(); //insert before
            size_type n = std::distance(first, last);

            if (size_ + n > max_size()) {
                throw FtLengthError();
            }
            pointer tmp_arr;
            //overflow deal
            if (n <= 0 || (n > 0 && size_ > std::numeric_limits<size_type>::max() - n))
                return position;

            //new capacity is 2x or size + n
            size_type new_capacity;
            if (size_ + n <= capacity_)
                new_capacity = capacity_;
            else if (size_ > n && 2 * size_ <= max_size())
                new_capacity = 2 * capacity_;
            else new_capacity = size_ + n;

            tmp_arr = alloc_.allocate(new_capacity);

                //first part move
            if (position_index > 0)
                std::memmove(tmp_arr, arr_, sizeof(value_type) * position_index);
//                for (size_type i = 0; i < position_index; ++i) {
//                    alloc_.construct(tmp_arr + i, arr_[i]);
//                    alloc_.destroy(arr_ + i);
//                }

                //second part move
            if (size_ - position_index > 0)
                std::memmove(tmp_arr + position_index + n, arr_ + position_index,
                         sizeof(value_type) * (size_ - position_index));
//                for (size_type i = 0; i < size_ - position_index; ++i) {
//                    alloc_.construct(tmp_arr + position_index + n + i, arr_[position_index + i]);
//                   alloc_.destroy(arr_ + position_index + i);
//                }

                //fill between
            std::copy(first, last, tmp_arr + position_index);
//                for (size_type i = 0; i < n; ++i)
//                    alloc_.construct(tmp_arr + position_index + i, *(first + i));
            alloc_.deallocate(arr_, capacity_);
            capacity_ = new_capacity;
            arr_ = tmp_arr;
            size_ += n;
            return position;
        };

        iterator erase (iterator position) {
            difference_type span = position - begin();
            if (size_ == 0)
                return (iterator(arr_+ span));
            if (position == end() - 1) {
                pop_back();
                return (iterator(arr_+ span));
            }
            alloc_.destroy(arr_ + span);
            --size_;
            std::memmove(arr_ + span, arr_ + span + 1, sizeof(value_type) * (size_ - span));
            return (iterator(arr_+ span));
        }// one

        iterator erase (iterator first, iterator last) {
            if (std::distance(first, last) < 0)
                return arr_;
            difference_type span = first - begin();
            difference_type n = std::distance(first, last);
            difference_type count;
            if (last == end() - 1) {
                for (count = 0; count < n; ++count) {
                    pop_back();
                }
                return (iterator(arr_+ span));
            }
            for (count = span; count < span + n; ++count) {
                alloc_.destroy(arr_ + count);
            }
            std::memmove(arr_ + span, arr_ + span + n, sizeof(value_type) * (size_ - span - n));
            size_ -= n;
            return (iterator(arr_+ span));
        }// range

        void swap(Vector & x) {
            pointer arr_tmp = arr_;
            size_type size_tmp = size_;
            size_type capacity_tmp = capacity_;
            allocator_type alloc_tmp = get_allocator();

            arr_ = x.arr_;
            size_ = x.size_;
            capacity_ = x.capacity_;
            alloc_ = x.alloc_;

            x.arr_ = arr_tmp;
            x.size_ = size_tmp;
            x.capacity_ = capacity_tmp;
            x.alloc_ = alloc_tmp;
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
        return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
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

namespace std {
    template <class T, class Alloc>
    void swap (ft::Vector<T,Alloc>& x, ft::Vector<T,Alloc>& y) {
        x.swap(y);
    }
}
#endif //FT_VECTOR_HPP
