#ifndef BSTREE_HPP
# define BSTREE_HPP

# include <cstdlib>
# include <utility>
# include <functional>
# include <iostream>

# define BLACK	0
# define RED	1

template <class Key, class T>
class Node
{
	typedef	std::pair<const Key, T>					value_type;

	public:
		Node():
			_value(value_type()),
			_color(BLACK),
			_left(NULL),
			_right(NULL),
			_parent(NULL)
		{}
		Node(Node& src) { *this = src; }
	
		Node(value_type val, bool color, Node* left = NULL, Node* right = NULL,Node* parent = NULL):
			_value(val),
			_color(color),
			_left(left),
			_right(right),
			_parent(parent)
		{}
		~Node() 
		{ 
			if (_left)
			{
				std::cout << "Left\n";
				delete _left;
			}
			if (_right)
			{
				std::cout << "Right\n";
				delete _right;
			}
		}

	Node&		operator=(Node& rhs)
	{
		_value = rhs._data;
		_left = rhs._left;
		_right = rhs._right;
		_parent = rhs._parent;
		_color = rhs._color;
		return (*this);
	}

	Key				getKey() const { return (this->_value.first); }
	Node*			getLeft() const { return (this->_left); }
	Node*			getRight() const { return (this->_right); }
	Node*			getParent() const { return (this->_parent); }
	bool			getColor()	const { return (this->_color); }

	void			setLeft(Node*	src) { _left = src; }
	void			setRight(Node*	src) { _right = src; }
	void			setParent(Node* src) { _parent = src; }
	void			setColor(bool	src) { _color = src; }

	void	display(Node* root)
	{
		if (!root)
			return ;
		root->display(root->_left);
		std::cout << "[" << root->_value.first << "]: " << root->_value.second << std::endl;
		root->display(root->_right);;
	}

	public:
		value_type	_value;
		bool		_color;
		Node*		_left;
		Node*		_right;
		Node*		_parent;
};

template <	class Key,
			class T,
			class Compare = std::less<Key>,
			class Allocator = std::allocator<std::pair<const Key, T> >
			>
class	BSTree
{

	typedef	BSTree*									pointer;
	typedef	BSTree&									reference;
	typedef	Key							 			key_type;
	typedef	std::pair<const Key, T>					value_type;
	typedef	T										mapped_type;
	typedef	Compare									key_compare;
	typedef	Allocator								allocator_type;
	typedef	Node<Key, T>							node_type;
	typedef	node_type*								node_pointer;


	public:
		BSTree():
			_root(NULL),
			_comp(Compare()),
			_alloc(Allocator())
		{
			initTNULL();
		}
		BSTree(BSTree& src):
			_root(src._root),
			_comp(src._comp),
			_alloc(src._alloc)
		{
			initTNULL();
		}
		BSTree(key_compare comp, allocator_type alloc):
			_root(NULL),
			_comp(comp),
			_alloc(alloc)
		{
			initTNULL();
		}
		~BSTree()
		{
			if (_root)
				delete _root;
		};

	/*reference			operator=(reference src)
	{ 
		_key = src._key;
		_value = src._value;
		_left = src._left;
		_right = src._right;
		_comp = src._comp;
		_alloc = src._alloc;
		return (*this);
	}*/

	void				deleteNode(key_type&	key)
	{
		deleteNodeHelper(this->_root, key);
	}

	void				insert(node_pointer root, const value_type& val)
	{
		node_pointer	node = new node_type(val, RED);

		node_pointer	y = NULL;
		node_pointer	x = _root;
	
		while (x != _TNULL)
		{
			y = x;
			if (_comp(node->getKey(), x->getKey()))
				x = x->getLeft();
			else
				x = x->getRight();
		}
		if (!y)
			root = node;
		else if (_comp(node->getKey(), y->getKey()))
			y->setLeft(node);
		else
			y->setRight(node);
		
		if (!node->getParent())
		{
			node->setColor(BLACK);
			return ;
		}
		if (!node->getParent()->getParent())
			return ;
		fixInsert(node);
	/*	if (!root)
			return (new node_type(val));
		if (_comp(key, root->getKey()))
			root->setLeft(insert(root->getLeft(), key, value));
		else
			root->setRight(insert(root->getRight(), key, value));
		return (root);

		while (root)
		{
			if (_comp(key, root->getKey()))
				return insert(root->getLeft(), key, value);
			else
				return insert(root->getRight(), key, value);
		}
		root = new node_type(key, value));
		return std::pair<iterator, bool>(iterator(root), true);*/
	}

		void						display() { _root->display(_root); }

		node_pointer				getRoot() const { return (_root); }
		void						setRoot(node_pointer src) { _root = src; }

		void						rightRotate(node_pointer k)
		{
			node_pointer tmp = k->_left;

			k->_left = tmp->_right;
			if (tmp->_right)
				tmp->_right->_parent = k;
			tmp->_parent = k->_parent;
			if (k->_parent == NULL)
				this->_root = tmp;
			else if (k == k->_parent->_right)
				k->_parent->_right = tmp;
			else
				k->_parent->_left = tmp;
			tmp->_right = k;
			k->_parent = tmp;
		}

		void						leftRotate(node_pointer k)
		{
			node_pointer tmp = k->_right;

			k->_right = tmp->_left;
			if (tmp->_left)
				tmp->_left->_parent = k;
			tmp->_parent = k->_parent;
			if (k->_parent == NULL)
				this->_root = tmp;
			else if (k == k->_parent->_left)
				k->_parent->_left = tmp;
			else
				k->_parent->_right = tmp;
			tmp->_left = k;
			k->_parent = tmp;
		}

	private:

		node_pointer				minimum(node_pointer	node)
		{
			while (node->_left != _TNULL)
				node = node->_left;
			return (node);
		}

		void						rbTransplant(node_pointer u, node_pointer v)
		{
			if (u->_parent == NULL)
				_root = v;
			else if (u == u->_parent->_left)
				u->_parent->_left = v;
			else
				u->_parent->_right = v;
			v->_parent = u->_parent;
		}

		void						fixDelete(node_pointer x)
		{
			node_pointer s;
			while (x != _root && x->_color == BLACK)
			{
				if (x == x->_parent->_left)
				{
					s = x->_parent->_right;
					if (s->_color == RED)
					{
						s->_color = BLACK;
						x->_parent->_color = RED;
						leftRotate(x->_parent);
						s = x->_parent->_right;
					}
					if (s->_left->_color == BLACK && s->_right->_color == BLACK)
					{
						s->_color = RED;
						x = x->_parent;
					}
					else
					{
						if (s->_right->_color == BLACK)
						{
							s->_left->_color = BLACK;
							s->_color = RED;
							rightRotate(s);
							s = x->_parent->_right;
						}
						s->_color = x->_parent->_color;
						x->_parent->_color = BLACK;
						s->_right->_color = BLACK;
						leftRotate(x->_parent);
						x = _root;
					}
				}
				else
				{
					s = x->_parent->_left;
					if (s->_color == RED)
					{
						s->_color = BLACK;
						x->_parent->_color = RED;
						rightRotate(x->_parent);
						s = x->_parent->_left;
					}
					if (s->_right->_color == BLACK && s->_right->_color == BLACK)
					{
						s->_color = RED;
						x = x->_parent;
					}
					else
					{
						if (s->_left->_color == BLACK)
						{
							s->_right->_color = BLACK;
							s->_color = RED;
							leftRotate(s);
							s = x->_parent->_left;
						}
						s->_color = x->_parent->_color;
						x->_parent->_color = BLACK;
						s->left->_color = BLACK;
						rightRotate(x->_parent);
						x = _root;
					}
				}
			}
			x->_color = BLACK;
		}

		void						deleteNodeHelper(node_pointer node, key_type key)
		{
			node_pointer z = _TNULL;
			node_pointer x, y;
			
			while (node != _TNULL)
			{
				if (node->getKey() == key)
					z = node;
				if (node->getKey() <= key)
					node = node->_right;
				else
					node = node->_left;
			}

			if (z == _TNULL)
				return ;
			y = z;
			bool	color = y->_color;
			if (z->_left == _TNULL)
			{
				x = z->_right;
				rbTransplant(z, z->_right);
			}
			else if (z->_right == _TNULL)
			{
				x = z->_left;
				rbTransplant(z, z->_left);
			}
			else
			{
				y = minimum(z->_right);
				color = y->_color;
				x = y->_right;
				if (y->_parent == z)
					x->_parent = y;
				else
				{
					rbTransplant(y, y->_right);
					y->_right = z->_right;
					y->_right->_parent = y;
				}
				rbTransplant(z, y);
				y->_left = z->_left;
				y->_left->_parent = y;
				y->_color = z->_color;
			}
			delete z;
			if (color == BLACK)
				fixDelete(x);
		}

		void						fixInsert(node_pointer k)
		{
			node_pointer	u;
		
			while (k->_parent->_color == RED)
			{
				if (k->_parent == k->_parent->_parent->_right)
				{
					u = k->_parent->_parent->_right;
					if (u->_color == RED)
					{
						u->_color = BLACK;
						k->_parent->_color = BLACK;
						k->_parent->_parent->_color = RED;
						k = k->_parent->_parent;
					}
					else
					{
						if (k == k->_parent->_left)
						{
							k = k->_parent;
							rightRotate(k);
						}
						k->_parent->_color = BLACK;
						k->_parent->_parent->_color = RED;
						leftRotate(k->_parent->_parent);
					}
				}
				else
				{
					u = k->_parent->_parent->_right;

					if (u->_color == RED)
					{
						u->_color = BLACK;
						k->_parent->_color = BLACK;
						k->_parent->_parent->_color = RED;
						k = k->_parent->_parent;
					}
					else
					{
						if (k == k->_parent->_right)
						{
							k = k->_parent;
							leftRotate(k);
						}
						k->_parent->_color = BLACK;
						k->_parent->_parent->_color = RED;
						rightRotate(k->_parent->_parent);
					}
				}
				if (k == _root)
					break;
			}
			_root->_color = 0;
		}

		void					initTNULL()
		{
			_TNULL = new node_type();
			_TNULL->setLeft(NULL);
			_TNULL->setRight(NULL);
			_TNULL->setColor(BLACK);
			_root = _TNULL;
		}

		node_pointer		_root;
		node_pointer		_TNULL;
		key_compare			_comp;
		allocator_type		_alloc;
};
#endif