//
// Created by Namor Scarab on 3/11/22.
//

#ifndef BIDIRECTIONAL_ITERATOR_HPP
#define BIDIRECTIONAL_ITERATOR_HPP

#include "utils.hpp" // std::conditional
#include <memory> // std::addressof
#include "Node_struct.hpp"
namespace ft {

	// -- conditional

	template<bool B, class T, class F>
	struct conditional { typedef T type; };
	template<class T, class F>
	struct conditional<false, T, F> { typedef F type; };

	template<typename Value, bool IsConst = false>
	class BidirectionalIterator {
		public:
			typedef Value									value_type;
			typedef t_node<value_type>*						node_type;
			typedef typename ft::conditional<IsConst,
					const value_type*, value_type*>::type	pointer;
			typedef typename ft::conditional<IsConst, 
					const value_type&, value_type&>::type	reference;
			// typedef value_type*	pointer;
			// typedef value_type&	reference;


			typedef BidirectionalIterator<Value, IsConst>		iterator;
			typedef std::ptrdiff_t							difference_type;
			typedef std::bidirectional_iterator_tag			iterator_category;

			BidirectionalIterator() : node() {}
			BidirectionalIterator(node_type _node) : node(_node) {}
			BidirectionalIterator(const BidirectionalIterator<Value>& other) :
				node(other.get_pointer()) {}
			
			iterator& operator= (const iterator& other)
			{
				node = other.node;
				return *this;
			}

			~BidirectionalIterator() {}

			reference operator*() const { return (node->n_val_); }

			pointer operator->() const { return &(node->n_val_); }

			// ++it
			iterator& operator++() {
				node = next_key_node(node);
				return *this;
			}

			// it++
			iterator operator++(int) {
				iterator old = *this;
				node = next_key_node(node);
				return old;
			}

			// --it
			iterator& operator--() {
				node = prev_key_node(node);
				return *this;
			}

			// it--
			iterator operator--(int) {
				iterator old = *this;
				node = prev_key_node(node);
				return old;
			}

			node_type get_pointer() const { return node; }
			pointer	get_value() const { return node->n_val_; }

            // bool operator == ( const iterator &src ) const	{ return node == src.get_pointer(); }
			// bool operator != ( const iterator &src ) const	{ return node != src.get_pointer(); }
			// bool operator > ( const iterator &src ) const	{ return node->n_val_ > src.get_pointer()->n_val_; }
			// bool operator < ( const iterator &src ) const	{ return node->n_val_ < src.get_pointer()->n_val_; }
			// bool operator >= ( const iterator &src ) const	{ return node->n_val_ >= src.get_pointer()->n_val_; }
			// bool operator <= ( const iterator &src ) const	{ return node->n_val_ <= src.get_pointer()->n_val_; }

		private:
			node_type node;

			node_type next_key_node(node_type x){
				if (x->is_null) {
					if (x->parent_) return x->parent_;
					return x->left_;
				}
				if (x->right_->is_null == false){
					node_type parent = x;
					x = x->right_;
					while (x->is_null == false)
					{
						parent = x;
						x = x->left_;
					}
					return parent;
				}
				node_type tmp = x;
				node_type y = x->parent_;
				while (y->is_null == false && x == y->right_){
					x = y;
					y = y->parent_;
				}
				if (y->is_null) y->parent_ = tmp;
				return y;
			}

			node_type prev_key_node(node_type x){
				if (x->is_null) {
					if (x->parent_) return x->parent_;
					return x->right_;
				}
				if (x->left_->is_null == false){
					node_type parent = x;
					x = x->left_;
					while (x->is_null == false)
					{
						parent = x;
						x = x->right_;
					}
					return parent;
				}
				node_type tmp = x;
				node_type y = x->parent_;
				while (y->is_null == false && x == y->left_){
					x = y;
					y = y->parent_;
				}
				if (y->is_null) y->parent_ = tmp;
				return y;
			}
	};

	template<typename T, bool IsConstL, bool IsConstR> 
	bool operator==(const BidirectionalIterator<T, IsConstL>& lhs, const BidirectionalIterator<T, IsConstR>& rhs)
	{
		return lhs.get_pointer() == rhs.get_pointer();
	}


	template<typename T, bool IsConstL, bool IsConstR>
	bool operator!=(const BidirectionalIterator<T, IsConstL>& lhs, const BidirectionalIterator<T, IsConstR>& rhs)
	{
		return lhs.get_pointer() != rhs.get_pointer();
	}

	template<typename T, bool IsConstL, bool IsConstR>
	bool operator<(const BidirectionalIterator<T, IsConstL>& lhs, const BidirectionalIterator<T, IsConstR>& rhs)
	{
		return lhs.get_value() < rhs.get_value();
	}

	template<typename T, bool IsConstL, bool IsConstR>
	bool operator>(const BidirectionalIterator<T, IsConstL>& lhs, const BidirectionalIterator<T, IsConstR>& rhs)
	{
		return lhs.get_value() > rhs.get_value();
	}

	template<typename T, bool IsConstL, bool IsConstR>
	bool operator<=(const BidirectionalIterator<T, IsConstL>& lhs, const BidirectionalIterator<T, IsConstR>& rhs)
	{
		return lhs.get_value() <= rhs.get_value();
	}

	template<typename T, bool IsConstL, bool IsConstR>
	bool operator>=(const BidirectionalIterator<T, IsConstL>& lhs, const BidirectionalIterator<T, IsConstR>& rhs)
	{
		return lhs.get_value() >= rhs.get_value();
	}

}
#endif //BIDIRECTIONAL_ITERATOR_HPP
