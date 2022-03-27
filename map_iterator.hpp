/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 09:54:02 by cboutier          #+#    #+#             */
/*   Updated: 2022/02/24 14:49:54 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

# include "Map.hpp"

namespace ft
{
	template<class T, class node_ptr>
	class map_iterator
	{
		public :

			typedef T								value_type;
			typedef value_type						*pointer;
			typedef value_type						&reference;
			typedef ptrdiff_t						difference_type;
			typedef ft::bidirectional_iterator_tag	iterator_category;

		protected :

			node_ptr _ptr;

		public :

			map_iterator()
				: _ptr(NULL)
			{};

			map_iterator(node_ptr ptr)
				: _ptr(ptr)
			{};

			map_iterator(map_iterator const &rhs)
				: _ptr(rhs._ptr)
			{};

			map_iterator &operator=(map_iterator const &rhs)
			{
				if (this != &rhs)
					_ptr = rhs._ptr;
				return (*this);
			}

			~map_iterator()
			{};

			map_iterator &operator++(void)
			{
				if (_ptr->_right_node)
				{
					_ptr = _ptr->_right_node;
					while (_ptr->_left_node)
						_ptr = _ptr->_left_node;
				}
				else
				{
					/*
						   parent
							/
						 _ptr
						 /  \
						A    B
					*/
					node_ptr tmp = _ptr;
					_ptr = _ptr->_parent_node;
					/* incrementation of _ptr
						   _ptr
							/
						 tmp
						 / \
						A   B
					*/

					/* LOOP
						parent                               parent         		 			 parent                         	_ptr (parent) 4
						 /      	                          /             		 			   /                       	             /
						A                                    A              		 	    _ptr (pointe sur A)                 tmp (pointe sur A) 1
					   /  \                                 / \             		             / \			           	           /  \
					  B    C                        	   B   _ptr (pointe sur C)             B  tmp (pointe sur C)		          C    C 2
					 /      \                             /     \                              /	 \			                     /      \
					D        _ptr (pointe sur E)  		 D       tmp (pointe sur E)           D 	  E			            	    D        E 3
					*/
					while (_ptr->_left_node != tmp)
					{
						tmp = _ptr;
						_ptr = _ptr->_parent_node;
					}
				}
				return (*this);
			}

			map_iterator operator++(int)
			{
				map_iterator it = *this;
				++(*this);
				return it;
			}

			map_iterator &operator--(void)
			{
				if (_ptr->_left_node)
				{
					_ptr = _ptr->_left_node;
					while (_ptr->_right_node)
						_ptr = _ptr->_right_node;
				}
				else
				{
					node_ptr tmp = _ptr;
					_ptr = _ptr->_parent_node;
					while (_ptr->_right_node != tmp)
					{
						tmp = _ptr;
						_ptr = _ptr->_parent_node;
					}
				}
				return (*this);
			}

			map_iterator operator--(int)
			{
				map_iterator it = *this;
				--(*this);
				return it;
			}

			reference	operator*() const
			{
				return (_ptr->_value);
			}

			pointer operator->() const
			{
				return &(operator*());
			}

			node_ptr get_ptr()
			{
				return _ptr;
			}

			node_ptr get_ptr() const
			{
				return _ptr;
			}

			// const cast
			operator map_iterator<const T, node_ptr>() const
			{
				return map_iterator<const T, node_ptr>(_ptr);
			}

			template<class Iterator>
			bool operator==(const map_iterator<Iterator, node_ptr> &b) const
			{
				return _ptr == b.get_ptr();
			}

			template<class Iterator>
			bool operator!=(const map_iterator<Iterator, node_ptr> &b) const
			{
				return !(_ptr == b.get_ptr());
			}
	};
}

#endif
