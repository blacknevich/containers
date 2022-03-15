//
// Created by Namor Scarab on 3/11/22.
//

#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include <iostream>
#include "utils.hpp"

namespace ft{

    enum colors {red, black};

    template< class value_type>
    struct t_node {
        struct t_node*  left_;
        struct t_node*	right_;
        struct t_node*	parent_;
        colors          color_;
        value_type      n_val_;
        bool            is_null;
        //============================constructors==================================
        t_node(): left_(nullptr), right_(nullptr), parent_(nullptr), color_(black), is_null(true) {} //default

        t_node(
                t_node* _left, t_node* _right,
                t_node* _parent, colors c,
                value_type _data
        ) : left_(_left), right_(_right), parent_(_parent), color_(c), n_val_(_data), is_null(false) {} //full

        t_node(const t_node* obj)
                : left_(obj->left_), right_(obj->right_), parent_(obj->parent_),
                  color_(obj->color_), n_val_(obj->n_val_), is_null(false) {} //copy

        //======================end constructors====================================
        void assign_node_no_value(const t_node* obj){
            left_ = obj->left_;
            right_ = obj->right_;
            parent_ = obj->parent_;
            color_ = obj->color_;
        }
    };
}

namespace ft{

    template<
            class Key,
            class T,
            class Compare = std::less<Key>,
            class Allocator = std::allocator<ft::pair<const Key, T> >
    > class Red_black_tree{

        //================================typedef===================================
    public:
        typedef ft::pair<const Key, T>									value_type;
        typedef ft::t_node<value_type>									node;
        typedef Compare													key_compare;
        typedef typename Allocator::template rebind<node>::other		allocator_type;
        //================================end typedef===============================

        //=============================private variables============================
    private:
        key_compare		comp_;
        allocator_type	alloc_;
        node* 			root_;
        node*			null_node_;
        //===========================end private variables==========================

        //=============================private functions============================

        void delete_tree(node** _x){ //recursion
            node* x = *_x;
            if (x->is_null) return;
            delete_tree(&x->left_);
            delete_tree(&x->right_);
            obliviate_Node(x);
        }

        void obliviate_Node(node *x){
            alloc_.destroy(x);
            alloc_.deallocate(x, 1);
        }

        node* return_uncle(node* x) {
            node* grandpa = x->parent_->parent_;
            if (grandpa->left_ == x->parent_)
                return grandpa->right_;
            else return grandpa->left_;
        }

        node* return_brother(node* x) {
            if (x->parent_->left_ == x)
                return x->parent_->right_;
            else return x->parent_->left_;
        }

        bool are_values_equal(const value_type& lhs, const value_type& rhs){
            if (!comp_(lhs, rhs) && !comp_(rhs, lhs)) return true;
            else return false;
        }

        node* find(const value_type& _data){
            node* current = root_;
            node* parent = nullptr;
            while(!current->is_null && !are_values_equal(current->n_val_, _data)){
                parent = current;
                if (comp_(_data, current->n_val_))
                    current = current->left_;
                else
                    current = current->right_;
            }
            return current;
        }

        void give_away_parent(node* x, node* y){
            if (!y->is_null)
                y->parent_ = x->parent_;
            if (x == root_) {
                root_ = y;
                return;
            }
            if (x->parent_->left_ == x)
                x->parent_->left_ = y;
            else x->parent_->right_ = y;
        }

        void swap_node_no_value(node* x, node* y){
            node* tmp = alloc_.allocate(1);
            alloc_.construct(tmp, y); //copy y to tmp

            give_away_parent(y, tmp);
            give_away_parent(x, y);

            y->assign_node_no_value(x);
            y->left_->parent_ = y;
            y->right_->parent_ = y;

            give_away_parent(tmp, x);
            x->assign_node_no_value(tmp);
            x->right_->parent_ = x;
            obliviate_Node(tmp);
        }

        void	copyTreeByNode( node* node ) {
            if ( !node->left_->is_null )
                copyTreeByNode( node->left_ );
            if ( !node->is_null )
                insert( node->n_val_ );
            if ( !node->right_->is_null )
                copyTreeByNode( node->right_ );
        }

        void updateNIL(node* x){
            if (comp_(x->n_val_, null_node_->left_->n_val_) || null_node_->left_->is_null)
                null_node_->left_ = x;
            if (comp_(null_node_->right_->n_val_, x->n_val_) || null_node_->right_->is_null)
                null_node_->right_ = x;
        }

        void updateNIL(){
            null_node_->left_ = begin();
            null_node_->right_ = last();
        }
        //===========================end private functions==========================

    public:

        // --- CONSTRUCTORS, destructor

        Red_black_tree(const key_compare& _comp) : comp_(_comp), alloc_(allocator_type()){
            null_node_ = alloc_.allocate(1);
            alloc_.construct(null_node_);
            root_ = null_node_;
            updateNIL();
        }

        Red_black_tree(const Red_black_tree& obj) : comp_(obj.comp_), alloc_(obj.alloc_){
            null_node_ = alloc_.allocate(1);
            alloc_.construct(null_node_);
            root_ = null_node_;
            updateNIL();

            for (node* current = obj.begin(); current->is_null == false; current = nextNode(current))
                insert(current->n_val_);
        }

        void deleteTree(){
            delete_tree(&root_);
            root_ = null_node_;
        }

        void copyTree( const Red_black_tree& other ){
            deleteTree();
            copyTreeByNode(other.get_root());
        }

        Red_black_tree& operator=(const Red_black_tree& other ){
            copyTree(other);
            return *this;
        }


        ~Red_black_tree() {
            deleteTree();
            obliviate_Node(null_node_);
        }

        void	leftRotate(node* x){
            node*	rightTree = x->right_;

            rightTree->parent_ = x->parent_;
            if ( !x->parent_->is_null ) {
                if (x->parent_->left_ == x )
                    x->parent_->left_ = rightTree;
                else
                    x->parent_->right_ = rightTree;
            }
            x->right_ = rightTree->left_;
            if ( rightTree->left_ )
                rightTree->left_->parent_ = x;
            x->parent_ = rightTree;
            rightTree->left_ = x;
            if (x == root_ ) root_ = rightTree;
        }

        void	rightRotate(node* x){
            node*	leftTree = x->left_;

            leftTree->parent_ = x->parent_;
            if ( x->parent_ ) {
                if (x->parent_->left_ == x )
                    x->parent_->left_ = leftTree;
                else
                    x->parent_->right_ = leftTree;
            }
            x->left_ = leftTree->right_;
            if ( leftTree->right_ )
                leftTree->right_->parent_ = x;
            x->parent_ = leftTree;
            leftTree->right_ = x;
            if (x == root_ ) root_ = leftTree;
        }

        node* nextNode(node* x){
            if (x->right_->is_null == false){
                node* parent = x;
                x = x->right_;
                while (x->is_null == false)
                {
                    parent = x;
                    x = x->left_;
                }
                return parent;
            }
            node* y = x->parent_;
            while (y->is_null == false && x == y->right_){
                x = y;
                y = y->parent_;
            }
            return y;
        }

        node* prevNode(node* x){
            if (x->left_->is_null == false){
                node* parent = x;
                x = x->left_;
                while (x->is_null == false)
                {
                    parent = x;
                    x = x->right_;
                }
                return parent;
            }
            node* y = x->parent_;
            while (y->is_null == false && x == y->left_){
                x = y;
                y = y->parent_;
            }
            return y;
        }

        void swap(Red_black_tree& x){
            node* tmp = root_;
            root_ = x.get_root();
            x.root_ = tmp;

            tmp = null_node_;
            null_node_ = x.null_node_;
            x.null_node_ = tmp;
        }

        node* begin() const{
            node* current = root_;
            node* parent = current;
            while(!current->is_null){
                parent = current;
                current = current->left_;
            }
            return parent;
        }

        node* prebegin() const{
            return null_node_;
        }

        node* last() const{
            node* current = root_;
            node* parent = current;
            while(!current->is_null){
                parent = current;
                current = current->right_;
            }
            return parent;
        }

        node* end() const{
            null_node_->parent_ = nullptr;
            return null_node_;
        }


        // --- INSERT

        void 	insertFix(node* x){
            while(x->parent_->color_ == red){
                node* uncle = return_uncle(x);
                if (x->parent_ == x->parent_->parent_->left_) // parent_ is left_
                {
                    //---- uncle red

                    if (uncle->color_ == red){
                        x->parent_->color_ = black;
                        uncle->color_ = black;
                        x->parent_->parent_->color_ = red;
                        x = x->parent_->parent_;
                    }

                        //---- uncle black

                    else if (uncle->color_ == black){
                        if (x->parent_->right_ == x){
                            leftRotate(x->parent_);
                            x = x->left_;
                        }
                        rightRotate(x->parent_->parent_);
                        x->parent_->color_ = black;
                        x->parent_->left_->color_ = red;
                        x->parent_->right_->color_ = red;
                        return;
                    }
                }
                else // parent_ is right_
                {
                    //---- uncle red

                    if (uncle->color_ == red){
                        x->parent_->color_ = black;
                        uncle->color_ = black;
                        x->parent_->parent_->color_ = red;
                        x = x->parent_->parent_;
                    }

                        //---- uncle black

                    else if (uncle->color_ == black){
                        if (x->parent_->left_ == x){
                            rightRotate(x->parent_);
                            x = x->right_;
                        }
                        leftRotate(x->parent_->parent_);
                        x->parent_->color_ = black;
                        x->parent_->left_->color_ = red;
                        x->parent_->right_->color_ = red;
                        return;
                    }
                }
            }
            root_->color_ = black;
        }

        ft::pair<node*, bool>	insert(const value_type& _data){
            node* current = find(_data);
            if (current->is_null == false) return ft::make_pair(current, false);

            node* x = alloc_.allocate(1);
            alloc_.construct(x, node(null_node_, null_node_, null_node_, red, _data));

            if (root_->is_null == true){
                x->color_ = black;
                root_ = x;
                updateNIL(x);
                return ft::make_pair(root_, true);
            }

            current = root_;
            node* parent = current;
            while (current->is_null == false)
            {
                parent = current;
                if (comp_(_data, current->n_val_))
                    current = current->left_;
                else
                    current = current->right_;
            }

            if (comp_(_data, parent->n_val_))
                parent->left_ = x;
            else
                parent->right_ = x;
            x->parent_ = parent;

            updateNIL(x);

            insertFix(x);
            return ft::make_pair(x, true);
        }

        ft::pair<node*, bool>	insertByHint(node* hint, const value_type& _data){
            node* current;
            node* parent;
            node* x;

            current = hint;
            parent = nullptr;
            while (!current->is_null) {
                if (_data.first == current->n_val_.first)
                    return ft::make_pair(current, false);
                parent = current;
                current = comp_(_data, current->n_val_) ?
                          current->left_ : current->right_;
            }

            x = alloc_.allocate(1);
            alloc_.construct(x, node(null_node_, null_node_, parent, red, _data));

            if (parent) {
                if (comp_(_data, parent->n_val_))
                    parent->left_ = x;
                else
                    parent->right_ = x;
            } else {
                x->color_ = black;
                root_ = x;
            }

            updateNIL(x);

            //insertFix(x);
            return ft::make_pair(x, true);
        }

        // --- DELETE


        void	deleteFix(node* x){
            while (x != root_ && x->color_ == black)
            {
                node* brother = return_brother(x);
                if (x->parent_->left_ == x){
                    if (brother->color_ == red){
                        brother->color_ = black;
                        brother->parent_->color_ = red;
                        leftRotate(x->parent_);
                        brother = x->parent_->left_;
                    }
                    if (brother->color_ == black){
                        if (brother->left_->color_ == black
                            && brother->right_->color_ == black){
                            brother->color_ = red;
                            x = x->parent_;
                        }
                        else if (brother->right_->color_ == black){
                            brother->color_ = red;
                            brother->left_->color_ = black;
                            rightRotate(brother);
                            brother = x->parent_->right_;
                        }
                        if (brother->right_->color_ == red){
                            brother->color_ = brother->parent_->color_;
                            brother->right_->color_ = black;
                            brother->parent_->color_ = black;
                            leftRotate(x->parent_);
                        }
                    }
                }
                else  {
                    if (brother->color_ == red){
                        brother->color_ = black;
                        brother->parent_->color_ = red;
                        rightRotate(x->parent_);
                        brother = x->parent_->right_;
                    }
                    if (brother->color_ == black){
                        if (brother->right_->color_ == black
                            && brother->left_->color_ == black){
                            brother->color_ = red;
                            x = x->parent_;
                        }
                        else if (brother->left_->color_ == black){
                            brother->color_ = red;
                            brother->right_->color_ = black;
                            leftRotate(brother);
                            brother = x->parent_->left_;
                        }
                        if (brother->left_->color_ == red){
                            brother->color_ = brother->parent_->color_;
                            brother->left_->color_ = black;
                            brother->parent_->color_ = black;
                            rightRotate(x->parent_);
                        }
                    }
                }
            }
            x->color_ = black;
        }

        bool	deleteNode(const value_type& _data){
            node* x = find(_data);
            return deleteNode(x);
        }

        bool	deleteNode(node* x){
//				bool isBlack = x->color_;

            if (x == null_node_) return false;

            node* next = null_node_;
            if (x->left_ == null_node_ && x->right_ == null_node_){ // not child
                null_node_->parent_ = x->parent_;
                give_away_parent(x, null_node_);
                obliviate_Node(x);
            }
            else if (x->left_ != null_node_ && x->right_ != null_node_){ // 2 childs
                next = nextNode(x);
                swap_node_no_value(x, next);
                deleteNode(x);
//					isBlack = false;
            }
            else{ // 1 ребенок
                next = (!x->left_->is_null) ? x->left_ : x->right_;
//					isBlack = next->color_;
                give_away_parent(x, next);
                next->color_ = black; // recolor in black
                obliviate_Node(x);
            }

            //if (isBlack) deleteFix(next); //balancing
            updateNIL();
            return true;
        }

        node* get_root() const { return root_; }
    };

    // template< class Key, class T, class Compare, class Allocator >
    // ft::t_node<ft::pair<const Key, T> >* Red_black_tree<Key, T, Compare, Allocator>::null_node_ = new t_node<ft::pair<const Key, T> >();
}
#endif //BINARY_TREE_HPP
