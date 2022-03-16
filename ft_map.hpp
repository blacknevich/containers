//
// Created by Namor Scarab on 3/10/22.
//

#ifndef FT_MAP_HPP
#define FT_MAP_HPP

//==================================lib includes===================================
#include <iostream>
#include <functional> // std::binary_function
//================================local includes===================================
#include "Node_struct.hpp"
#include "Map_iterator.hpp"
#include "Reverse_iterator.hpp"

namespace ft{
    template<
            class Key,
            class T,
            class Compare = std::less<Key>,
            class Allocator = std::allocator<ft::pair<const Key, T> > >
    class Map
	{
		public:
        //================================typedef===================================
			typedef Key																	key_type;
			typedef T																	mapped_type;
			typedef ft::pair<const Key, T>												value_type;
			typedef std::size_t															size_type;
			typedef std::ptrdiff_t														difference_type;
			typedef Compare																key_compare;
			typedef Allocator															allocator_type;
			typedef value_type&															reference;
			typedef const value_type&													const_reference;
			typedef typename Allocator::pointer											pointer;
			typedef typename Allocator::const_pointer									const_pointer;
			typedef ft::t_node<value_type>												node;
			typedef typename ft::BidirectionalIterator<value_type>						iterator;
			typedef typename ft::BidirectionalIterator<value_type, true>				const_iterator;

			typedef ft::Reverse_iterator<iterator>										reverse_iterator;
			typedef ft::Reverse_iterator<const_iterator>								const_reverse_iterator;
        //================================end typedef===============================

        //================================nested class==============================
			class value_compare : public std::binary_function<value_type, value_type, bool> {
				friend class Map;
				
				public:
					typedef bool		result_type;
					typedef value_type	first_argument_type;
					typedef value_type	second_argument_type;

					bool operator()( const first_argument_type& lhs, const second_argument_type& rhs ) const{
						return comp(lhs.first, rhs.first);
					}
				
				protected:
 					key_compare	comp;

					value_compare(const key_compare c) : comp(c) {}
			};
        //==============================end nested class============================

        //=============================private variables============================
    private:
        typedef Red_black_tree<Key, T, value_compare, Allocator>	rbtree_type;
        allocator_type 	alloc_;
        key_compare		kcomp_;
        size_type		size_;
        rbtree_type		tree_;
        //===========================end private variables==========================

    public:
        //============================constructors==================================
			Map() : alloc_(allocator_type()), kcomp_(key_compare()),
                    size_(0), tree_(kcomp_) {} //default

        explicit Map(
                const Compare& comp,
                const Allocator& _alloc = Allocator()
        ) : alloc_(_alloc),
            kcomp_(comp), size_(0), tree_(kcomp_) {}

        template< class InputIt >
        Map(
                InputIt first, InputIt last,
                const Compare& comp = Compare(),
                const Allocator& _alloc = Allocator()
        ) : alloc_(_alloc), kcomp_(comp),
            size_(0), tree_(kcomp_) {

            for ( ; first != last; ++first )
            {
                insert( *first);
            }
        } //range

        Map(const Map& other)
                : alloc_(other.alloc_), kcomp_(other.kcomp_),
                  size_(other.size_), tree_(other.tree_) {} //copy
        //======================end constructors====================================

        //=======================assignation operator===============================
			Map& operator=(const Map& other ){
				if ( this != &other ) {
                    alloc_ = other.alloc_;
                    kcomp_ = other.kcomp_;
                    size_ = other.size_;
                    tree_ = other.tree_;
				}
				return *this; 
			}
        //===================end assignation operator===============================

        //============================iterators====================================
        iterator begin() { return iterator(tree_.get_tree_begin()); }
        const_iterator begin() const { return const_iterator(tree_.get_tree_begin()); }

        iterator end() { return iterator(tree_.get_tree_end()); }
        const_iterator end() const { return const_iterator(tree_.get_tree_end()); }

        reverse_iterator rbegin() { return reverse_iterator(tree_.get_tree_last()); }
        const_reverse_iterator rbegin() const { return const_reverse_iterator(tree_.get_tree_last()); }

        reverse_iterator rend() { return reverse_iterator(tree_.get_tree_null_node()); }
        const_reverse_iterator rend() const { return const_reverse_iterator(tree_.get_tree_null_node()); }
        //==========================end_iterators==================================

        //==============================capacity====================================
        bool empty() const { return (size_ == 0); }

        size_type size() const { return size_; }

        size_type max_size() const { return alloc_.max_size(); }
        //==========================end capacity====================================

        //==========================element access==================================
			mapped_type& at( const Key& key )
            {
				iterator it = this->find(key);
				if (it == this->end())
                    throw FtOutOfRange();
				return it->second;
			}

			const mapped_type& at( const Key& key ) const
            {
				iterator it = this->find(key);
				if (it == this->end())
                    throw FtOutOfRange();
				return it->second;
			}

			mapped_type& operator[]( const Key& key )
            {
				return insert(ft::make_pair(key, mapped_type())).first->second;
			}
        //=======================end element access=================================

        //=============================modifiers====================================

			void clear()
            {
                size_ = 0;
                tree_.obliviate_tree();
			}

			ft::pair<iterator, bool> insert( const value_type& value )
            {
				ft::pair<node*, bool> p = tree_.insert(value);
				if (p.second == true) size_++;
				return ft::make_pair(iterator(p.first), p.second);
			}

			iterator insert( iterator hint, const value_type& value )
            {
				(iterator)hint;
				ft::pair<node*, bool> p = tree_.insert(value);
				if (p.second == true) size_++;
				return iterator(p.first);
			}

        template<class InputIterator>
        void insert(
                InputIterator first,
                InputIterator last )
        {
            for ( ; first != last; ++first )
                insert( ft::make_pair( first->first, first->second ) );
        }

        void erase( iterator pos ){
            if (tree_.delete_node(*pos))
                size_--;
        }

        void erase(
                iterator first,
                iterator last
        )
        {
            iterator tmp;
            for ( ; first != last;  )
            {
                tmp = first++;
                erase(tmp);
            }
        }

			size_type erase( const Key& key )
            {
				iterator x = this->find(key);
				if (x == this->end())
                    return 0;
				erase(x);
				return 1;
			}

			void swap(Map& other ) {
                size_type tmp_size;

                tree_.swap_trees(other.tree_);

                tmp_size = size_;
                size_ = other.size_;
                other.size_ = tmp_size;
			}
        //===========================end_modifiers==================================

        //=============================observers====================================
        key_compare	key_comp( void ) const	{ return kcomp_; }

        ft::Map<key_type, mapped_type, key_compare, allocator_type>::value_compare	value_comp(void ) const
        {
            return value_compare( key_comp() );
        }
        //===========================end observers==================================

        //=============================operations====================================

        iterator find( const key_type &key )
        {
            node* tmp = tree_.get_root();
            node* end = tree_.get_tree_end();

            while (tmp != end) {
                if (key == tmp->n_val_.first)
                    return iterator(tmp);
                else
                    tmp = kcomp_(key, tmp->n_val_.first) ? tmp->left_ : tmp->right_;
            }
            return tmp;
        }

			const_iterator find( const Key& key ) const
            {
				node* tmp = tree_.get_root();
				node* end = tree_.get_tree_end();

				while (tmp != end) {
					if (key == tmp->n_val_.first)
						return iterator(tmp);
					else
						tmp = kcomp_(key, tmp->n_val_.first) ? tmp->left_ : tmp->right_;
				}
				return tmp;
			}
			
			size_type	count( const key_type &key ) const
            {
				return (find(key) == end()) ? 0 : 1;
			}

			ft::pair<iterator,iterator> equal_range( const Key& key )
            {
				return ft::make_pair( lower_bound( key ), upper_bound( key ) );
			}

			iterator lower_bound( const Key& key )
            {
				iterator it = begin();
				while (it != end() && kcomp_(it->first, key))
					it++;
				return it;
			}
	
			const_iterator lower_bound( const Key& key ) const
            {
				iterator it = begin();
				while (it != end() && kcomp_(it->first, key))
					it++;
				return it;
			}

			iterator upper_bound( const Key& key )
            {
				iterator it = begin();
				while (it != end() && !kcomp_(key, it->first))
					it++;
				return it;
			}

			const_iterator upper_bound( const Key& key ) const
            {
				iterator it = begin();
				while (it != end() && !kcomp_(key, it->first))
					it++;
				return it;
			}

			ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const
            {
				return ft::make_pair( lower_bound( key ), upper_bound( key ) );
			}
        //===========================end operations=================================

        //=============================allocator====================================
        allocator_type get_allocator() const { return alloc_; }
        //===========================end allocator==================================

        //============================exceptions====================================
        class FtOutOfRange : public std::exception
        {
            const char* what() const throw() {
                return ("map::at:  key not found");
            }
        };
        //============================end exceptions=================================
	};

	template< class Key, class T > 
	bool operator==(const Map<Key, T>& lhs, const Map<Key, T>& rhs )
	{
		return (lhs.size() == rhs.size() 
			&& std::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template< class Key, class T > 
	bool operator!=(const ft::Map<Key, T>& lhs, const ft::Map<Key, T>& rhs )
	{
		return !(lhs == rhs);
	}

	template< class Key, class T > 
	bool operator<(const ft::Map<Key, T>& lhs, const ft::Map<Key, T>& rhs )
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template< class Key, class T > 
	bool operator<=(const ft::Map<Key, T>& lhs, const ft::Map<Key, T>& rhs )
	{
		return (!(rhs < lhs));
	}

	template< class Key, class T > 
	bool operator>(const ft::Map<Key, T>& lhs, const ft::Map<Key, T>& rhs )
	{
        return (rhs < lhs);
	}

	template< class Key, class T > 
	bool operator>=(const ft::Map<Key, T>& lhs, const ft::Map<Key, T>& rhs )
	{
        return (!(lhs < rhs));
	}
}
#endif //FT_MAP_HPP
