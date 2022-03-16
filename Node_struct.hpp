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
                t_node* _parent, colors _c,
                value_type _val
        ) : left_(_left), right_(_right), parent_(_parent), color_(_c), n_val_(_val), is_null(false) {} //full

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

    public:
        //============================constructors==================================
        Red_black_tree(const key_compare& _comp) : comp_(_comp), alloc_(allocator_type())
        {
            null_node_ = alloc_.allocate(1);
            alloc_.construct(null_node_);
            root_ = null_node_;
            update_null_node();
        } //basic

        Red_black_tree(const Red_black_tree& obj) : comp_(obj.comp_), alloc_(obj.alloc_)
        {
            null_node_ = alloc_.allocate(1);
            alloc_.construct(null_node_);
            root_ = null_node_;
            update_null_node();

            for (node* current = obj.get_tree_begin(); current->is_null == false; current = next_key_node(current))
                insert(current->n_val_);
        } //copy
        //======================end constructors====================================

        //============================destructor====================================
        virtual ~Red_black_tree()
        {
            obliviate_tree();
            obliviate_Node(null_node_);
        }
        //============================end destructor================================

    private:
        //=============================private functions============================

        void delete_tree(node** _x)
        { //recursion
            node* x = *_x;
            if (x->is_null)
                return;
            delete_tree(&x->left_);
            delete_tree(&x->right_);
            obliviate_Node(x);
        }

        void obliviate_Node(node *x)
        {
//            x->right_ = nullptr;
//            x->left_ = nullptr;
//            x->parent_ = nullptr;
            alloc_.destroy(x);
            alloc_.deallocate(x, 1);
//            x = nullptr;
        }

        node* return_uncle(node* x)
        {
            node* grandpa = x->parent_->parent_;
            if (grandpa->left_ == x->parent_)
                return grandpa->right_;
            else return grandpa->left_;
        }

        node* return_brother(node* x)
        {
            if (x->parent_->left_ == x)
                return x->parent_->right_;
            else return x->parent_->left_;
        }

        bool are_values_equal(const value_type& lhs, const value_type& rhs)
        {
            if (!comp_(lhs, rhs) && !comp_(rhs, lhs)) return true;
            else return false;
        }

        node* find(const value_type& val)
        {
            node* current = root_;
            while(
                    !current->is_null &&
                    !are_values_equal(current->n_val_, val)
                    )
            {
                if (comp_(val, current->n_val_))
                    current = current->left_;
                else
                    current = current->right_;
            }
            return current;
        }

        void give_away_parent(node* x, node* y)
        {
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

        void swap_node_no_value(node* x, node* y)
        {
            node* tmp = alloc_.allocate(1);
            alloc_.construct(tmp, y); //copy y to tmp

            give_away_parent(y, tmp); //tmp has ys parents
            give_away_parent(x, y); //y has xs parents

            y->assign_node_no_value(x); //y has other xs surrounding
            y->left_->parent_ = y;
            y->right_->parent_ = y;

            give_away_parent(tmp, x); //x has tmps parents
            x->assign_node_no_value(tmp); //x has other ys surroundings
            x->left_->parent_ = x;
            x->right_->parent_ = x;
            obliviate_Node(tmp); //kill tmp
        }

        void	full_tree_copy(node* node )
        { //recursive , straight go over
            if ( !node->left_->is_null ) //get_tree_end state
                full_tree_copy(node->left_);
            if ( !node->is_null )
                insert( node->n_val_ );
            if ( !node->right_->is_null ) //get_tree_end state
                full_tree_copy(node->right_);
        }

        void update_null_node()
        {
            null_node_->left_ = get_tree_begin();
            null_node_->right_ = get_tree_last();
        }
        //===========================end private functions==========================
    public:
        //=============================public functions=============================
        void obliviate_tree()
        {
            delete_tree(&root_);
            root_ = null_node_;
        }

        void replace_tree(const Red_black_tree& other)
        {
            obliviate_tree();
            full_tree_copy(other.get_root());
        }

        Red_black_tree& operator=(const Red_black_tree& other ){
            replace_tree(other);
            return *this;
        }

        void	rotate_left(node* x)
        {
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

        void	rotate_right(node* x)
        {
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

        node* next_key_node(node* x)
        {
            node* tmp;
            if (x->right_->is_null == false){
                tmp = x;
                x = x->right_;
                while (x->is_null == false)
                {
                    tmp = x;
                    x = x->left_;
                }
                return tmp;
            }
            tmp = x->parent_;
            while (tmp->is_null == false && x == tmp->right_){
                x = tmp;
                tmp = tmp->parent_;
            }
            return tmp;
        }

        void swap_trees(Red_black_tree& x)
        {
            node* tmp = root_;
            root_ = x.get_root();
            x.root_ = tmp;

            tmp = null_node_;
            null_node_ = x.null_node_;
            x.null_node_ = tmp;
        }

        node* get_tree_begin() const
        {
            node* current = root_;
            node* parent = current;
            while(!current->is_null){
                parent = current;
                current = current->left_;
            }
            return parent;
        }

        node* get_tree_null_node() const
        {
            return null_node_;
        }

        node* get_tree_last() const //not get_tree_end!
        {
            node* current = root_;
            node* parent = current;
            while(!current->is_null){
                parent = current;
                current = current->right_;
            }
            return parent;
        }

        node* get_tree_end() const
        {
            null_node_->parent_ = nullptr;
            return null_node_;
        }

        void 	rebalance_after_insert(node* x){ //watch pictures
            while(x->parent_->color_ == red){
                node* uncle = return_uncle(x);
                if (x->parent_ == x->parent_->parent_->left_) // parent is left
                {
                    if (uncle->color_ == red)
                    {
                        x->parent_->color_ = black;
                        uncle->color_ = black;
                        x->parent_->parent_->color_ = red;
                        x = x->parent_->parent_;
                    }
                    else if (uncle->color_ == black)
                    {
                        if (x->parent_->right_ == x)
                        {
                            rotate_left(x->parent_);
                            x = x->left_;
                        }
                        rotate_right(x->parent_->parent_);
                        x->parent_->color_ = black;
                        x->parent_->left_->color_ = red;
                        x->parent_->right_->color_ = red;
                        return;
                    }
                }
                else // parent_ is right_
                {
                    if (uncle->color_ == red)
                    {
                        x->parent_->color_ = black;
                        uncle->color_ = black;
                        x->parent_->parent_->color_ = red;
                        x = x->parent_->parent_;
                    }
                    else if (uncle->color_ == black)
                    {
                        if (x->parent_->left_ == x)
                        {
                            rotate_right(x->parent_);
                            x = x->right_;
                        }
                        rotate_left(x->parent_->parent_);
                        x->parent_->color_ = black;
                        x->parent_->left_->color_ = red;
                        x->parent_->right_->color_ = red;
                        return;
                    }
                }
            }
            root_->color_ = black;
        }

        ft::pair<node*, bool>	insert(const value_type& val){
            node* current = find(val);
            if (current->is_null == false)
                return (ft::make_pair(current, false));

            node* x = alloc_.allocate(1); //create node to insert
            alloc_.construct(x, node(null_node_, null_node_, null_node_, red, val));

            if (root_->is_null == true) // if we are empty
            {
                x->color_ = black;
                root_ = x;
                update_null_node();
                return ft::make_pair(root_, true);
            }

            current = root_;
            node* backup_of_current = current;
            while (current->is_null == false)
            {
                backup_of_current = current;
                if (comp_(val, current->n_val_))
                    current = current->left_;
                else
                    current = current->right_;
            }//backup is now place to insert right before null_node

            if (comp_(val, backup_of_current->n_val_))
                backup_of_current->left_ = x;
            else
                backup_of_current->right_ = x;
            x->parent_ = backup_of_current;

            update_null_node();
            rebalance_after_insert(x); //rebalance
            return ft::make_pair(x, true);
        }

        bool	delete_node(const value_type& val)
        {
            node* x = find(val);
            return delete_node(x);
        }

        bool	delete_node(node* x) //returns false if we are deleting null node -recursive
        {

            if (x == null_node_)
                return false;

            node* next;
            if (x->left_ == null_node_ && x->right_ == null_node_){ // no children
                null_node_->parent_ = x->parent_;
                give_away_parent(x, null_node_);
                obliviate_Node(x);
            }
            else if (x->left_ != null_node_ && x->right_ != null_node_){ // both
                next = next_key_node(x); //find next key
                swap_node_no_value(x, next); //swap this and next
                delete_node(x); //recursion
            }
            else{ // one child
                next = (x->left_->is_null) ? x->right_ : x->left_;
                give_away_parent(x, next);
                next->color_ = black;
                obliviate_Node(x);
            }
            update_null_node();
            return true;
        }

        node* get_root() const
        {
            return root_;
        }
    };
    //===========================end public functions===========================
}
#endif //BINARY_TREE_HPP
