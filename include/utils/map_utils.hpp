#ifndef MAP_UTILS_HPP
# define MAP_UTILS_HPP

# include <cstdlib>
# include <iostream>
# include "utils.hpp"


namespace ft
{

//Map tree declaration

# define DEFAULT 0
# define FIRST 1
# define LAST 2

template <class value_type, class Compare>
class tree_node
{
    public:
        value_type      data;
        tree_node      *parent;
        tree_node      *left;
        tree_node      *right;
        int             balance;
        int             pos;

        typedef typename    value_type::first_type  key_type;
        typedef typename    value_type::second_type mapped_type;

        tree_node(value_type src = value_type(), int position = DEFAULT):
            data(src),
            parent(NULL),
            left(NULL),
            right(NULL),
            balance(0),
            pos(position)
        {}
        tree_node(const tree_node& src):
            data(src.data),
            parent(src.parent),
            left(src.left),
            right(src.right),
            balance(src.balance),
            pos(src.pos)
        {}
        ~tree_node()
        {}

        tree_node&     operator=(const tree_node& rhs)
        {
            data = rhs.data;
            left = rhs.left;
            right = rhs.right;
            balance = rhs.balance;
            pos = rhs.pos;
            return (*this);
        }

        bool            is_left_child()
        {
            if (parent)
            {
                if (parent->left && parent->left == this)
                    return (true);
            }
            return (false);
        }

        tree_node*      node_min()
        {
            tree_node* tmp = this;

            while (tmp->left && tmp->left->pos == DEFAULT)
                tmp = tmp->left;
            return (tmp);
        }

        tree_node*      node_max()
        {
            tree_node* tmp = this;
            while (tmp->right && tmp->right->pos == DEFAULT)
            {
                tmp = tmp->right;
            }
            return (tmp);
        }

        tree_node*      successor() 
        {
            tree_node *node = this;

            if (node->right)
                return (node->right->node_min());
            
            tree_node *tmp = node->parent;
            while (tmp && node == tmp->right)
            {
                node = tmp;
                tmp = tmp->parent;
            }
            return (tmp);
        }

        tree_node*      predecessor()
        {
            tree_node *node = this;

            if (node->left)
                return (node->left->node_max());
            
            tree_node *tmp = node->parent;
            while (tmp && node == tmp->left)
            {
                node = tmp;
                tmp = tmp->parent;
            }
            return (tmp);
        }

        key_type        getKey() const
        { return (data.first); }

        mapped_type     getValue() const
        { return (data.second); }
    
    private:

        bool            compare_keys(key_type a, key_type b)
        { Compare comp; return (comp(a, b)); }

};

template <class value_type, class Compare>
class AVLTree
{
    public:
    
        typedef AVLTree<value_type, Compare>             tree_t;
        typedef tree_node<value_type, Compare>          node;
        typedef node*                                   node_ptr;
        typedef typename node::key_type                 key_type;

    public:
        AVLTree(node_ptr data = NULL): root(data)
        {
            init_tree();
        }
        AVLTree(const AVLTree& src): root(src.root)
        {}
        ~AVLTree()
        {
            tree_destroy(root);
            return ;
        }

        AVLTree&          operator=(const AVLTree& rhs)
        { root = rhs.root; return (*this); }

        int              erase(key_type key)
        {
            node_ptr    tmp = search(key);
    
		/*	std::cout << "key " << key << std::endl;
			if (root)
			{
				std::cout << "root " << root->getKey();
				if (root->left)
					std::cout << " left " << root->left->getKey();
				if (root->right)
					std::cout << " right " << root->right->getKey();
				std::cout << std::endl;
			}*/
            if (!tmp || (tmp && (tmp->pos != DEFAULT || tmp->getKey() != key)))
                return (0);
            tree_deletion(tmp);
            return (1);
        }

        void            insert(value_type   data)
        {
            if (root->pos != DEFAULT)
            {
                insert_empty_tree(data);
                return ;
            }
            
            node_ptr tmp = search(data.first);
            if (tmp->getKey() == data.first)
                return ;
            node_ptr new_node = new node(data);
				
            new_node->parent = tmp;
            node_ptr    last_node = NULL; // Past the end node or node before the first one

            if (compare_nodes(new_node, tmp))
            {
                if (tmp->left)
                {
                    last_node = tmp->left;
                    last_node->parent = new_node;
                }
                tmp->left = new_node;
                new_node->left = last_node;
            }
            else
            {
                if (tmp->right)
                {
                    last_node = tmp->right;
                    last_node->parent = new_node;
                }
                tmp->right = new_node;
                new_node->right = last_node;
            }
            balance_tree(new_node);
            
        }
        
        node_ptr        find(key_type key) const
        {
            node_ptr tmp = root;
            
            while (tmp)
            {
                if (compare_keys(key, tmp->getKey()))
                {
                    if (!tmp->left || tmp->left->pos == FIRST)
                        return (end());
                    tmp = tmp->left;
                }
                else if (key == tmp->getKey())
                    return (tmp);
                else
                {
                    if (!tmp->right || tmp->right->pos == LAST)
                        return (end());
                    tmp = tmp->right;
                }
            }
            return (end());
        }

        bool            count(key_type key) const
        {
            node_ptr tmp = root;
            
            while (tmp)
            {
                if (compare_keys(key, tmp->getKey()))
                {
                    if (!tmp->left || tmp->left->pos == FIRST)
                        return (false);
                    tmp = tmp->left;
                }
                else if (key == tmp->getKey())
                    return (true);
                else
                {
                    if (!tmp->right || tmp->right->pos == LAST)
                        return (false);
                    tmp = tmp->right;
                }
            }
            return (false);
        }

        node_ptr        search(key_type key) const
        {
            node_ptr    tmp = root;

            while (tmp)
            {
                if (compare_keys(key, tmp->getKey()))
                {
                    if (!tmp->left || tmp->left->pos == FIRST)
                        break ;
                    tmp = tmp->left;
                }
                else if (key == tmp->getKey())
                    break;
                else
                {
                    if (!tmp->right || tmp->right->pos == LAST)
                        break ;
                    tmp = tmp->right;
                }
            }
            return (tmp);
        }

        void            clear()
        { tree_destroy(root); init_tree(); }


        node_ptr        minimum() const
        {
            if (!root)
                return (NULL);
            if (root->pos != DEFAULT)
                return (end());
            return (root->node_min());
        }

        node_ptr       maximum() const
        {
            if (!root)
                return (NULL);
            return (root->node_max());
        }

        node_ptr        end() const
        {
            if (root->pos == LAST)
                return (root);
            return (maximum()->right);
        }


        node_ptr        rend() const
        { return (minimum()->left); }

        void            swap(tree_t& src)
        {
            if (src.root == root)
                return ;
            node_ptr tmp = src.root;
            src.root = root;
            root = tmp;
        }

    private:

        void            init_tree()
        {
            root = new node(value_type(), LAST);
            root->left = new node(value_type(), FIRST);
            root->left->parent = root;
        }

        void            tree_deletion(node_ptr node)
        {
            int side = 0;
            node_ptr ancestor = node->parent;
 
            if (node->left == NULL && node->right == NULL)
            {
                if (node->is_left_child())
                {
                    node->parent->left = NULL;
                    side = 1;
                }
                else if (node->parent)
                {
                    node->parent->right = NULL;
                    side = -1;
                }
                delete node;
                node = NULL;
            }
            else if (node->left == NULL)
            {
                node_ptr tmp = node;
                node_ptr parent = node->parent;

                node = node->right;
                node->parent = parent;
                if (tmp->is_left_child())
                {
                    parent->left = node;
                    side = 1;
                }
                else if (node->parent)
                {
                    parent->right = node;
                    side = -1;
                }
                delete tmp;
            }
            else if (node->right == NULL)
            {
                node_ptr tmp = node;
                node_ptr parent = node->parent;

                node = node->left;
                node->parent = parent;
                if (tmp->is_left_child())
                {
                    parent->left = node;
                    side = 1;
                }
                else if (node->parent)
                {
                    parent->right = node;
                    side = -1;
                }
                delete tmp;
            }
            else
            {
                node_ptr tmp;
                if (node->right->pos != DEFAULT)        // right child of node is end node
                    tmp = node->left;
                else
                    tmp = node->right->node_min();
				if (tmp->parent == node)
					ancestor = tmp;
				else
                	ancestor = tmp->parent;
                if (tmp->is_left_child())
                    side = 1;
                else if (node->parent)
                    side = -1;
                node = change_node_data(node, tmp);
                if (!node->parent)
                    root = node;
            }
            if (ancestor)
                ancestor->balance += side;
            balance_tree(ancestor);
        }

        void            balance_tree(node_ptr node)
        {
            if (!node)
                return ;
            if (node->balance < -1 || node->balance > 1)
            {
                rebalance(node);
                return ;
            }
            if (node->parent)
            {
                if (node == node->parent->left)
                    node->parent->balance--;

                if (node == node->parent->right)
                    node->parent->balance++;

                if (node->parent->balance != 0)
                    balance_tree(node->parent);
            }
        }

        void            rebalance(node_ptr  node)
        {
            if (node->balance > 0)
            {
                if (node->right->balance < 0 && node->right->pos == DEFAULT)
                {
                    right_rotate(node->right);
                    left_rotate(node);
                }
                else
                    left_rotate(node);
            }
            else if (node->balance < 0)
            {
                if (node->left->balance > 0 && node->left->pos == DEFAULT)
                {
                    left_rotate(node->left);
                    right_rotate(node);
                }
                else
                    right_rotate(node);
            }
        }

        void            right_rotate(node_ptr node)
        {
            node_ptr y = node->left;
            node->left = y->right;

            if (y->right != NULL)
                y->right->parent = node;

            y->parent = node->parent;
            if (node->parent == NULL)
                root = y;
            else if (node == node->parent->right)
                node->parent->right = y;
            else
                node->parent->left = y;
            y->right = node;
            node->parent = y;

            node->balance = node->balance + 1 - min(0, y->balance);
            y->balance = y->balance + 1 + max(0, node->balance);
        }

        void            left_rotate(node_ptr node)
        {
            node_ptr y = node->right;
            node->right = y->left;

            if (y->left != NULL)
                y->left->parent = node;
            
            y->parent = node->parent;
            if (node->parent == NULL)
                root = y;
            else if (node == node->parent->left)
                node->parent->left = y;
            else
                node->parent->right = y;
            y->left = node;
            node->parent = y;

            node->balance = node->balance - 1 - max(0, y->balance);
            y->balance = y->balance - 1 + min(0, node->balance);
        }

        void            tree_destroy(node_ptr node)
        {
            if (!node)
                return ;

            tree_destroy(node->left);
            tree_destroy(node->right);

            delete node;
            node = NULL;
        }

        void            insert_empty_tree(value_type data)
        {
            node_ptr tmp = new node(data);

            if (root->pos == FIRST)
            {
                tmp->left = root;
                root->parent = tmp;
                tmp->right = root->right;
                root->right = NULL;
                root = tmp;
                return ;
            }
            tmp->right = root;
            root->parent = tmp;
            tmp->left = root->left;
            root->left = NULL;
            root = tmp;
            return ;
        
        }

        node_ptr       change_node_data(node_ptr old, node_ptr dst)
        {
            if (dst->is_left_child())
            {
                dst->parent->left = dst->left;
            }
            else if (dst->parent)
                dst->parent->right = dst->right;
            
            dst->parent = old->parent;
            if (old->is_left_child())
                old->parent->left = dst;
            else if (old->parent)
                old->parent->right = dst;

            dst->left = old->left;
            dst->right = old->right;
            if (dst->left)
                dst->left->parent = dst;
            if (dst->right)
                dst->right->parent = dst;
			dst->balance = old->balance;
            delete old;
            return (dst);
        }

        bool            compare_nodes(node_ptr a, node_ptr b) const
        { Compare comp; return (comp(a->getKey(), b->getKey())); }

        bool            compare_keys(key_type a, key_type b) const
        { Compare comp; return (comp(a, b)); }


        node_ptr            root;
};


// Map utils functions


template <class Iterator>
bool	is_inferior(Iterator first1, Iterator last1, Iterator first2, Iterator last2)
{
	while (first1 != last1 && first2 != last2 && *first1 == *first2)
	{
		first1++;
		first2++;
	}
	if (first1 == last1)
		return (first2 != last2);
	else if (first2 == last2)
		return (false);
	return (*first1 < *first2);
}

}
#endif