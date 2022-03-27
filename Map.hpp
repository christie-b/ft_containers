/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 14:54:03 by cboutier          #+#    #+#             */
/*   Updated: 2022/02/24 15:24:05 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>

# include "Compare.hpp"
# include "is_integral.hpp"
# include "Iterator_traits.hpp"
# include "random_access_iterator.hpp"
# include "reverse_iterator.hpp"
# include "map_iterator.hpp"
# include "Pair.hpp"


namespace ft
{
	// https://www.cplusplus.com/reference/functional/less/
	// Binary function object class whose call returns whether first argument compares less than the second (as returned by operator <).
	template <class T>
	struct less : std::binary_function<T, T, bool>
	{
		bool operator()(const T &x, const T &y) const
		{
			return x < y;
		}
	};

	/* TNODE STRUCT */
	template <class T>
	struct Tnode
	{
		T		_value;
		Tnode	*_left_node;
		Tnode	*_right_node;
		Tnode	*_parent_node;
		bool	_last_node;
		int		_height;

		Tnode(T value, Tnode *left_node, Tnode *right_node, Tnode* parent_node, bool last)
			: _value(value), _left_node(left_node), _right_node(right_node), _parent_node(parent_node), _last_node(last)
		{};
		~Tnode()
		{};
	};

	/* MAP CLASS */
	// https://www.cplusplus.com/reference/map/map/?kw=map
	template < class Key,
				class T,
				class Compare = ft::less<Key>,
				class Alloc = std::allocator< ft::pair<const Key,T> > >
	class map
	{
		public:

			typedef Key															key_type;
			typedef T															mapped_type;
			typedef pair<const key_type, mapped_type>							value_type;
			typedef Compare														key_compare;
			typedef Tnode<value_type>											node_type;
			typedef Alloc														allocator_type;
			typedef typename allocator_type::template rebind<node_type>::other	node_allocator;
			typedef typename allocator_type::reference							reference;
			typedef typename allocator_type::const_reference					const_reference;
			typedef typename allocator_type::pointer							pointer;
			typedef typename allocator_type::const_pointer						const_pointer;
			typedef typename allocator_type::difference_type					difference_type;
			typedef typename allocator_type::size_type							size_type;
			typedef map_iterator<value_type, node_type*>						iterator;
			typedef map_iterator<const value_type, node_type*>					const_iterator;
			typedef ft::reverse_iterator<iterator>								reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;

		protected :

			node_allocator							_alloc;
			key_compare								_compare;
			size_type								_size;
			node_type								*_root;
			node_type								*_last_inserted_node;

		public :

			/* MEMBER CLASS */
			// https://www.cplusplus.com/reference/map/map/value_comp/
			// template <class Key, class T, class Compare, class Alloc>
			class value_compare
			{	// in C++98, it is required to inherit binary_function<value_type,value_type,bool>
				friend class map; // in case of calling the protected constructor

				protected:

					Compare comp;
					value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object

				public:

					typedef bool		result_type;
					typedef value_type	first_argument_type;
					typedef value_type	second_argument_type;
					bool operator() (const value_type &x, const value_type &y) const
					{
						return comp(x.first, y.first);
					}
			};

			/* CONSTRUCTORS */
			// 1. Default
			explicit map (const key_compare & comp = key_compare(),
				const allocator_type & alloc = allocator_type())
				: _alloc(alloc), _compare(comp), _size(0), _root(NULL), _last_inserted_node(NULL)
				{
					insert(value_type(key_type(), mapped_type())); //insert empty node
					_root->_last_node = true;
					_size--;
				}

			// 2. Range
			template <class InputIterator>
			map (typename ft::enable_if<!ft::is_integral<InputIterator>::value,
				InputIterator>::type first, InputIterator last,
				const key_compare & comp = key_compare(),
				const allocator_type & alloc = allocator_type())
				: _alloc(alloc), _compare(comp), _size(0), _root(NULL), _last_inserted_node(NULL)
				{
					insert(first, last);
				}

			// 3. Copy
			map (const map &x)
			: _alloc(x._alloc), _compare(x._compare), _size(0), _root(NULL), _last_inserted_node(NULL)
			{
				*this = x;
			}

			/* DESTRUCTOR */
			~map()
			{
				delete_nodes_from(_root);
			}

			/* ASSIGNATION OPERATOR OVERLOAD */
			map & operator=(const map &x)
			{
				if (this != &x)
				{
					delete_nodes_from(_root);
					insert(x.begin(), x.end());
				}
				return (*this);
			}

			/* ITERATORS */
			iterator	begin()
			{
				node_type	*node;

				if (_size == 0)
					return (iterator(_root));
				node = _root;
				while (node && node->_left_node)
					node = node->_left_node;
				return (iterator(node));
			}

			const_iterator	begin() const
			{
				node_type	*node;

				if (_size == 0)
					return (const_iterator(_root));
				node = _root;
				while (node && node->_left_node)
					node = node->_left_node;
				return (const_iterator(node));
			}

			iterator	end()
			{
				node_type	*node;

				if (_size == 0)
					return (iterator(_root));
				node = _root;
				while (node && !node->_last_node)
					node = node->_right_node;
				return (iterator(node));
			}

			const_iterator	end() const
			{
				node_type	*node;

				if (_size == 0)
					return (const_iterator(_root));
				node = _root;
				while (node && !node->_last_node)
					node = node->_right_node;
				return (const_iterator(node));
			}

			reverse_iterator	rbegin()
			{
				return (reverse_iterator(end()--));
			}

			const_reverse_iterator	rbegin() const
			{
				return (const_reverse_iterator(end()--));
			}

			reverse_iterator	rend()
			{
				return (reverse_iterator(begin()));
			}

			const_reverse_iterator	rend() const
			{
				return (const_reverse_iterator(begin()));
			}

			/* CAPACITY */
			bool empty() const
			{
				if (_size == 0)
					return (true);
				return (false);
			}

			size_type size() const
			{
				return (_size);
			}

			size_type max_size() const
			{
				return (_alloc.max_size());
			}

			/* ELEMENT ACCESS */
			mapped_type &at (const key_type &k)
			{
				return (this[k]);
			}

			const mapped_type &at (const key_type &k) const
			{
				node_type	*curr;

				curr = get_node_const(_root, k);
				if (curr)
					return curr->_value.second;
				insert(value_type(k, mapped_type()));
				return (get_node_const(_root, k)->_value.second);
			}

			mapped_type &operator[] (const key_type &k)
			{
				node_type *curr;

				curr = get_node(_root, k);
				if (curr)
					return curr->_value.second;
				insert(value_type(k, mapped_type()));
				return (get_node(_root, k)->_value.second);
			}

			/* MODIFIERS */
			// 1. SINGLE ELEMENT
			pair<iterator, bool>	insert (const value_type &val)
			{
				size_t		initial_size;
				bool		inserted;

				initial_size = _size;
				inserted = false;
				_root = insert_node(val, _root, NULL);
				if (size() != initial_size) // inserted successfully
					inserted = true;
				_last_inserted_node = NULL;

				return (pair<iterator, bool>(get_node(_root, val.first), inserted));
			}

			// 2. HINT
			iterator	insert (iterator position, const value_type &val)
			{
				(void)position;
				insert(val);
				return (get_node(_root, val.first));
			}

			// 3. RANGE
			template <class InputIterator>
			void	insert (InputIterator first, InputIterator last,
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
			{
				while (first != last)
				{
					insert(*first++);
				}
			}

			// 1. DELETE 1 ELEM
			void	erase (iterator position)
			{
				erase(position->first);
			};

			// 2. RETURNS NB OF NODES DELETED
			size_type	erase (const key_type &k)
			{
				size_t	initial_size;

				initial_size = _size;
				_root = search_del_node(_root, k);
				if (initial_size == size()) //didn't erase anything
					return (0);
				return (1);
			}

			// 3. RANGE
			void	erase (iterator first, iterator last)
			{
				while (first != last)
				{
					erase(first++);
				}
			}

			void	swap (map &x)
			{
				node_type		*tmp_root = _root;
				size_type		tmp_size = _size;
				node_allocator	tmp_alloc = _alloc;
				key_compare		tmp_cmp = _compare;

				_root = x._root;
				_size = x._size;
				_alloc = x._alloc;
				_compare = x._compare;

				x._root = tmp_root;
				x._size = tmp_size;
				x._alloc = tmp_alloc;
				x._compare = tmp_cmp;
			}

			void	clear()
			{
				delete_nodes_from(_root);
			}

			/* OBSERVERS */
			key_compare		key_comp() const
			{
				return (_compare);
			}

			value_compare	value_comp() const
			{
				// Returns an object of class value_compare,
				// constructed from the Compare parameter used to build the map (less by default)
				return (value_compare(key_compare()));
			}

			/* OPERATIONS */
			iterator	find (const key_type &k)
			{
				iterator	it;

				it = begin();
				while (it != end() && (*it).first != k)
					it++;
				if (it != end())
					return (it);
				return (end());
			}

			const_iterator	find (const key_type &k) const
			{
				const_iterator	it;

				it = begin();
				while (it != end() && (*it).first != k)
					it++;
				if (it != end())
					return (it);
				return (end());
			}

			size_type	count (const key_type &k) const
			{
				if (get_node_const(_root, k))
					return (1);
				return (0);
			}

			/*
				Returns an iterator pointing to the first element in the container
				whose key is not considered to go before k (i.e., >= k).
				The function uses its internal comparison object (key_comp) to determine this,
				returning an iterator to the first element for which key_comp(element_key,k) would return false.
			*/
			iterator	lower_bound (const key_type &k)
			{
				iterator	it = begin();
				iterator	ite = end();
				key_compare	key_cmp;

				key_cmp = key_comp();
				while (it != ite)
				{
					if (key_cmp((*it).first, k) == false)
						return (it);
					it++;
				}
				return (ite);
			}

			//https://www.cplusplus.com/reference/map/map/key_comp/
			const_iterator	lower_bound (const key_type &k) const
			{
				const_iterator	it = begin();
				const_iterator	ite = end();
				key_compare		key_cmp;

				key_cmp = key_comp();
				while (it != ite)
				{
					if (key_cmp((*it).first, k) == false)
						return (it);
					it++;
				}
				return (ite);
			}

			/*
				Returns an iterator pointing
				to the first element in the container whose key is considered to go after k.
				The function uses its internal comparison object (key_comp) to determine this,
				returning an iterator to the first element for which key_comp(k,element_key) would return true.
			*/
			iterator	upper_bound (const key_type &k)
			{
				iterator	it = begin();
				iterator	ite = end();
				key_compare		key_cmp;

				key_cmp = key_comp();
				while (it != ite)
				{
					if (key_cmp(k, (*it).first) == true)
						return (it);
					it++;
				}
				return (ite);
			}

			const_iterator	upper_bound (const key_type &k) const
			{
				const_iterator	it = begin();
				const_iterator	ite = end();
				key_compare		key_cmp;

				key_cmp = key_comp();
				while (it != ite)
				{
					if (key_cmp(k, (*it).first) == true)
						return (it);
					it++;
				}
				return (ite);
			}

			/*
				Returns the bounds of a range that includes all the elements in the container which have a key equivalent to k.
				Because the elements in a map container have unique keys, the range returned will contain a single element at most.
				If no matches are found, the range returned has a length of zero,
				with both iterators pointing to the first element that has a key considered to go after k according to the container's internal comparison object (key_comp).
				Two keys are considered equivalent if the container's comparison object returns false reflexively
				(i.e., no matter the order in which the keys are passed as arguments).
				The function returns a pair, whose member pair::first is the lower bound of the range (the same as lower_bound),
				and pair::second is the upper bound (the same as upper_bound).
			*/
			pair<iterator, iterator>	equal_range (const key_type &k)
			{
				return (pair<iterator, iterator>(lower_bound(k), upper_bound(k)));
			}

			pair<const_iterator, const_iterator>	equal_range (const key_type &k) const
			{
				return (pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k)));
			}

			// ALLOCATOR
			allocator_type	get_allocator() const
			{
				return (_alloc);
			}

		private :

			int get_height(node_type *node) const
			{
				if (node == NULL)
					return (0);
				return (node->_height);
			}

			// node height
			// height of the whole tree is always one more than one of the subtree heights
			void set_height(node_type *node)
			{
				node->_height = std::max(get_height(node->_left_node), get_height(node->_right_node)) + 1; // + 1 because we take the subtree height, so need to include the curr node
			}



			// -1, 0 or 1 | left subtree - right subtree
			int get_balance_factor(node_type *node) const
			{
				if (node == NULL)
					return (0);
				return (get_height(node->_left_node) - get_height(node->_right_node));
			}

			node_type *left_rotate(node_type *node)
			{
				/*
				  ex: left rotate D:
						20(B)                            40(D)
					   /     \                          /     \
					 10(A)  40(D)        ==>         20(B)   50(E)
							/  \                     /   \      \
				  		 30(C) 50(E)               10(A)  30(C)  60(F)
								 \
								60(F)
				*/
				node_type *new_parent = node->_right_node;
				/*
						20(B)                            20(B)/node
					   /     \                          /     \
					 10(A)  40(D)        ==>          10(A)  40(D)/new_parent
							/  \                     		/   \
						 30(C) 50(E)               		 30(C)  50(E)
								 \								  \
								60(F)							 60(F)
				*/
				new_parent->_parent_node = node->_parent_node; //assign D's parent to B's parent
				node->_parent_node = new_parent; // B's parent change to node D
				/*
				 											 40(D)
					  20(B)/node                          	 20(B)/node
					   /     \                         		/     \
					 10(A)  40(D)/new_parent     ==>      10(A)    40(D)/new_parent
							/  \                     	  		 /  \
						 30(C) 50(E)				          30(C)  50(E)
								 \									   \
								60(F)								  60(F)
				*/
				node->_right_node = new_parent->_left_node; // Change the right node of B from D to C
				if (new_parent->_left_node) // If D has a left node (C)?
					new_parent->_left_node->_parent_node = node; // change C's parent from D to B
				/*
				 	  40(D)									 40(D)/new_parent
					  20(B)/node                          	 20(B)/node   \(attached to D)
					   /     \                         		/     \		  50(E)
					 10(A)  40(D)/new_parent     ==>      10(A)   30(C)		\
							/  \                     	  		    		60(F)
						 30(C) 50(E)
								 \
								60(F)
				*/
				new_parent->_left_node = node; // The node to the left of D is B
				/*
				 			   40(D)/new_parent
							  /		\
						 20(B)/node  50(E)
                		   /   \	  \
					    10(A) 30(C)	  60(F)

				*/
				set_height(node);
				set_height(new_parent);
				return (new_parent);
			}

			node_type *right_rotate(node_type *node)
			{
				/*
				ex: right rotate C:
							50(E)                  		30(C)
						   /     \                     /    \
						30(C)  60(F)      ==>      20(B)   50(E)
						/  \                        /      /   \
					20(B)  40(D)                  10(A)  40(D) 60(F)
					/
				 10(A)

				*/
				node_type *new_parent = node->_left_node;
				/*
							50(E)                  		50(E)/node
						   /     \                     /          \
						30(C)  60(F)      ==>  30(C)/new_parent   60(F)
						/  \                        /	\
					20(B)  40(D)                 20(A)  40(D)
					/							  /
				 10(A)							10(A)

				*/
				new_parent->_parent_node = node->_parent_node; //assign C's parent to E's parent
				node->_parent_node = new_parent; // E's parent change to node C
				/*
				 										   30(C)
							50(E)/node                  50(E)/node
						   /     \                     /          \
				30(C)/new_parent  60(F)      ==>  30(C)/new_parent   60(F)
						/  \                        /	\
					20(B)  40(D)                 20(A)  40(D)
					/							  /
				 10(A)							10(A)

				*/
				node->_left_node = new_parent->_right_node; // Change the left node of E from C to D
				if (new_parent->_right_node) // If C has a right node (D)?
					new_parent->_right_node->_parent_node = node; // Change parent of D from C to E
				/*
				 			30(C)						30(C)			attached to C
							50(E)/node                  50(E)/node			/
						   /     \                     /          \		  20(B)
				30(C)/new_parent  60(F)      ==>  	40(D)   	 60(F)	  /
						/  \                        					10(A)
					20(B)  40(D)
					/
				 10(A)

				*/
				new_parent->_right_node = node; // Assign the right node of C to E
				/*
						  30(C)
			             /    \
					 20(B)   50(E)
					  /      /   \
					10(A)  40(D) 60(F)

				*/
				set_height(node);
				set_height(new_parent);
				return (new_parent);
			}

			node_type *left_right_rotate(node_type *node)
			{
				node->_left_node = this->left_rotate(node->_left_node);
				return (this->right_rotate(node));
			}

			node_type *right_left_rotate(node_type *node)
			{
				node->_right_node = this->right_rotate(node->_right_node);
				return (this->left_rotate(node));
			}

			node_type *rebalance_tree(node_type *node) ///////
			{
				// A balanced tree has a bf of -1, 0 or 1
				int	balance_factor = get_balance_factor(node);
				if (balance_factor > 1) // left heavy (left - right subtree)
				{
					if (get_balance_factor(node->_left_node) >= 0) // if left child is left heavy
						return (this->right_rotate(node));
					else
						return (this->left_right_rotate(node));
				}
				else if (balance_factor < -1) // right heavy
				{
					if (get_balance_factor(node->_right_node) <= 0)
						return (this->left_rotate(node));
					else
						return (this->right_left_rotate(node));
				}
				/* right - left rotation
				A(bf -2)			A(-2)			B(0)
					\				 \			   /   \
					 C(1)		->	 B(-1)	->	  A(0)  C(0)
					 /					\
					B(0)				C(0)
				Need the condition to check if the child is right heavy, otherwise it will only perform a left rotation
				A(bf -2)			C(2)
					\				 /
					 C(1)		->	A(-1)
					 /				 \
					B(0)			  B(0)
				*/
				return (node);
			}

			node_type	*create_new_node(const value_type &val, node_type *parent)
			{
				node_type *tmp = _alloc.allocate(1);
				_alloc.construct(tmp, node_type(val, NULL, NULL, parent, false));
				_size++;
				set_height(tmp);
				_last_inserted_node = tmp;
				return (tmp);
			}

			node_type	*get_node(node_type *curr, const key_type &key)
			{
				if (!curr || curr->_last_node)
					return (NULL);
				if (_compare(key, curr->_value.first))	// search for the node with the key
					return (get_node(curr->_left_node, key));
				else if (_compare(curr->_value.first, key))
					return (get_node(curr->_right_node, key));
				else
					return (curr);
			}

			node_type	*get_node_const(node_type *curr, const key_type &key) const
			{
				if (!curr || curr->_last_node)
					return (NULL);
				if (_compare(key, curr->_value.first))	// search for the node with the key
					return (get_node_const(curr->_left_node, key));
				else if (_compare(curr->_value.first, key))
					return (get_node_const(curr->_right_node, key));
				else
					return (curr);
			}

			node_type	*get_min_node(node_type *node)
			{
				node_type *curr = node;
				while (curr->_left_node != NULL)
					curr = curr->_left_node;
				return (curr);
			}

			node_type	*get_max_node(node_type *node)
			{
				node_type *curr = node;
				while (curr->_right_node != NULL)
					curr = curr->_right_node;
				return (curr);
			}

			node_type	*insert_node(const value_type &val, node_type *curr, node_type *parent)
			{
				if (!_root) // create root
				{
					node_type	*last_node;

					_root = create_new_node(val, NULL);
					last_node = create_new_node(value_type(key_type(), mapped_type()), _root);
					_size--;
					_root->_right_node = last_node;
					last_node->_last_node = true;
					return (_root);
				}
				if (_root->_last_node == true) // if there is only a root, to insert above the root
				{
					node_type	*new_root;

					new_root = create_new_node(val, NULL);
					_root->_parent_node = new_root;
					new_root->_right_node = _root;
					_root = new_root;
					return (_root);
				}
				if (!curr)
					return (create_new_node(val, parent));
				if (curr->_last_node == true) // if we want to insert above the last node
				{
					node_type	*to_insert;

					to_insert = create_new_node(val, parent);
					curr->_parent_node = to_insert;
					to_insert->_right_node = curr;
					curr = to_insert;
					set_height(curr);
					return (rebalance_tree(curr));
				}
				if (_compare(val.first, curr->_value.first)) // check if the value we want to insert is > or < to current value, to insert to the left or right
					curr->_left_node = insert_node(val, curr->_left_node, curr);
				else if (_compare(curr->_value.first, val.first))
					curr->_right_node = insert_node(val, curr->_right_node, curr);
				else
					return (_last_inserted_node = curr); // If they are the same, the map cannot be inserted, only writes to the last inserted node.
				set_height(curr);
				return (rebalance_tree(curr));
			}

			node_type	*search_del_node(node_type *curr, const key_type &key) // from curr, delete node with key
			{
				if (!curr || curr->_last_node == true)
					return (curr);
				if (_compare(key, curr->_value.first))		// search key on the left of curr
					curr->_left_node = search_del_node(curr->_left_node, key);
				else if (_compare(curr->_value.first, key))	// search key on the right of curr
					curr->_right_node = search_del_node(curr->_right_node, key);
				else
				{
					if (!curr->_left_node || !curr->_right_node)
					{
						node_type *tmp;
						if (curr->_left_node)	//save left or right node
							tmp = curr->_left_node;
						else
							tmp = curr->_right_node;
						if (!curr->_left_node && !curr->_right_node) // if no left or right nodes, delete curr
						{
							tmp = curr;
							_alloc.destroy(tmp);
							_alloc.deallocate(tmp, 1);
							curr = NULL;
							_size--;
						}
						else	// if there is 1 child
						{
							/*
								parent			parent
									\				\		tmp2 (curr) -> delete
									curr		   tmp (A)
									/
								tmp or A
							*/
							node_type	*tmp2;

							tmp2 = curr;
							tmp->_parent_node = curr->_parent_node;
							curr = tmp;
							_alloc.destroy(tmp2);
							_alloc.deallocate(tmp2, 1);
							_size--;
						}
					}
					else	// if there are 2 children
					{
						node_type *tmp;
						if (curr->_right_node->_last_node == false) //in case the null node is the right node, do not go there
							tmp = get_min_node(curr->_right_node);
						else
							tmp = curr->_left_node;
						/*
							if we don't have this condition:
							11(to delete)			NULL
						   /  \						/
						  5    NULL	 			  5
						*/
						/*
							  parent
								\
								curr
								/	\
							   A	 B
									/
								  tmp
						*/
						if (tmp != curr->_right_node)
						{
							tmp->_right_node = curr->_right_node;
							curr->_right_node->_parent_node = tmp;
						}
						/*
						  parent			   parent
							 \					  \
							 curr				 curr
							 /	\				 /	\
							A	 B      -->	    A	tmp
								/					  \
							  tmp					   B
						*/
						tmp->_left_node = curr->_left_node;
						curr->_left_node->_parent_node = tmp;
						tmp->_parent_node->_left_node = NULL;
						/*
						  parent			   parent
							 \					  \
							curr				  curr
							/	\					\
						   A    tmp      -->	   	tmp
								  \					/ \
								   B			   A   B
						*/
						tmp->_parent_node = curr->_parent_node;
						/*
						  parent			   parent
							 \					  \		curr
							 curr				  tmp
								\				  / \
								tmp      -->	 A	 B
								/  \
							   A    B
						*/
						if (_root == curr)
							_root = tmp;
						_alloc.destroy(curr);
						_alloc.deallocate(curr, 1);
						_size--;
						curr = tmp;
						/*
							parent
								\
								curr
								/ \
							   A   B
						*/
					}
				}
				return (curr);
			}

			void	delete_nodes_from(node_type *curr)
			{
				if (!curr)
					return ;
				delete_nodes_from(curr->_left_node);
				delete_nodes_from(curr->_right_node);
				_alloc.destroy(curr);
				_alloc.deallocate(curr, 1);
				if (_size > 0)
					_size--;
				if (curr == _root)
					_root = 0;
			}
	};

	// NON MEMBER OPERATORS OVERLOAD
	template<class Key, class T, class Compare, class Alloc>
	bool operator==(const ft::map<Key,T,Compare,Alloc> &lhs,
					const ft::map<Key,T,Compare,Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator!=(const ft::map<Key,T,Compare,Alloc> &lhs,
					const ft::map<Key,T,Compare,Alloc> &rhs)
	{
		return !(lhs == rhs);
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator<(const ft::map<Key,T,Compare,Alloc> &lhs,
					const ft::map<Key,T,Compare,Alloc> &rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator<=(const ft::map<Key,T,Compare,Alloc> &lhs,
					const ft::map<Key,T,Compare,Alloc> &rhs)
	{
		return (lhs < rhs || lhs == rhs);
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator>(const ft::map<Key,T,Compare,Alloc> &lhs,
					const ft::map<Key,T,Compare,Alloc> &rhs)
	{
		return (rhs < lhs);
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator>=(const ft::map<Key,T,Compare,Alloc> &lhs,
					const ft::map<Key,T,Compare,Alloc> &rhs)
	{
		return (lhs > rhs || lhs == rhs);
	}

	template<class Key, class T, class Compare, class Alloc>
	void swap(ft::map<Key,T,Compare,Alloc> &x,
				ft::map<Key,T,Compare,Alloc> &y)
	{
		x.swap(y);
	}
};

#endif
