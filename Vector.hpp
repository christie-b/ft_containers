/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 09:37:04 by cboutier          #+#    #+#             */
/*   Updated: 2022/02/17 15:07:35 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <exception>
# include <memory>
# include "Compare.hpp"
# include "is_integral.hpp"
# include "Iterator_traits.hpp"
# include "random_access_iterator.hpp"
# include "reverse_iterator.hpp"

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
		public :
			typedef T												value_type;
			typedef Alloc											allocator_type;
			typedef size_t											size_type;
			typedef ptrdiff_t										difference_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;

			typedef random_access_iterator<value_type> 				iterator;
			typedef random_access_iterator<const value_type>		const_iterator;
			typedef reverse_iterator<const_iterator>				const_reverse_iterator;
			typedef reverse_iterator<iterator>						reverse_iterator;

		private :

			Alloc		_alloc;
			pointer 	_start;
			size_type	_size;
			size_type 	_capacity;

		public:

			/* CONSTRUCTORS */
			// DEFAULT: Constructs an empty container
			explicit vector(const allocator_type &alloc = allocator_type())
				: _alloc(alloc), _start(0), _size(0), _capacity(0)
			{
				_start = _alloc.allocate(0);
			};


			// FILL: Constructs a container with n elements. Each element is a copy of val.
			explicit vector(size_type n, const value_type &val = value_type(),
				const allocator_type &alloc = allocator_type())
				: _alloc(alloc), _start(NULL), _size(n), _capacity(n)
			{
				_start = _alloc.allocate(n);
				for (size_type i = 0; i < n; i++)
				{
					_alloc.construct(&_start[i], val);
				}
			}


			//  explicit vector(size_type n, const value_type & val = value_type(), const allocator_type & alloc = allocator_type())
            // {
            //     size_type i;

            //     _alloc = alloc;
            //     _start = _alloc.allocate(n);
            //     _size = n;
            //     _capacity = n;
            //     i = 0;
            //     while (i < n)
            //     {
            //         _alloc.construct(_start + i, val);
            //         i++;
            //     }
            // };


			// RANGE CONSTRUCTOR
			template <class InputIterator>
			vector(InputIterator first, InputIterator last,
					const allocator_type &alloc = allocator_type(),
					typename
					ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
				: _alloc(alloc), _start(0), _size(0), _capacity(0)
			{
				size_type n = 0;
				size_type i = 0;
				for (InputIterator it = first; it != last; it++)
					n++;
				reserve(n);
				for (InputIterator it = first; it != last; it++, i++)
					_alloc.construct(&_start[i], *it);
				_size = n;
			}

			// COPY CONSTRUCTOR
			vector(const vector &x)
			: _alloc(x._alloc), _start(NULL), _size(x._size), _capacity(x._size)
			{
				size_type	i;

				_start = _alloc.allocate(_capacity);
				i = 0;
				while (i < _size)
				{
					_alloc.construct(_start + i, x._start[i]);
					i++;
				}
			}

			/* ASSIGNATION OPERATOR OVERLOAD */
			vector &operator=(vector const &x)
			{
                if (this != &x)
                {
					clear();
					if (_capacity < x._size)
						reserve(x._size);
					_size = x._size;
					if (_start)
						_alloc.deallocate(_start, _size);
					if (x._start)
					{
						_start = _alloc.allocate(_capacity);
						for (size_type i = 0; i < _size; i++)
							_alloc.construct(_start + i, x._start[i]);
					}
					else
					{
						_start = NULL;
					}
                }
                return (*this);
			}

			/* DESTRUCTOR */
			~vector()
			{
				clear();
				_alloc.deallocate(_start, _capacity);
			}


			/* ITERATORS */
			// Returns an iterator pointing to the first element in the vector.
			iterator begin()
			{
				return (iterator(_start));
			}

			const_iterator begin() const
			{
				return (const_iterator(_start));
			}

			// Returns an iterator referring to the past-the-end element in the vector container.
			iterator end()
			{
				return (iterator(_start + _size));
			}

			const_iterator end() const
			{
				return (const_iterator(_start + _size));
			}

			// Returns a reverse iterator pointing to the last element in the vector.
			reverse_iterator rbegin()
			{
				return (reverse_iterator(end()));
			}

			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator(end()));
			}

			// Returns a reverse iterator pointing to the theoretical element preceding the first element in the vector (which is considered its reverse end).
			reverse_iterator rend()
			{
				return (reverse_iterator(begin()));
			}

			const_reverse_iterator rend() const
			{
				return (const_reverse_iterator(begin()));
			}

			/* CAPACITY */
			// Returns the number of elements in the vector.
			size_type size() const
			{
				return (_size);
			}

			// Returns the maximum number of elements that the vector can hold.
			size_type max_size() const
			{
				return (_alloc.max_size());
			}

			/*
			Resizes the container so that it contains n elements.
			- If n is smaller than the current container size,
			the content is reduced to its first n elements, removing those beyond
			(and destroying them).
			- If n is greater than the current container size,
			the content is expanded by inserting at the end as many elements as needed to reach a size of n.
			If val is specified, the new elements are initialized as copies of val, otherwise, they are value-initialized.
			- If n is also greater than the current container capacity, an automatic reallocation of the allocated storage space takes place.
			Notice that this function changes the actual content of the container by inserting or erasing elements from it.
			*/
			void resize (size_type n, value_type val = value_type())
			{
				size_type	i;

				if (n <= _size)
				{
					i = _size;
					while (i > n)
					{
						pop_back();
						i--;
					}
				}
				else if (n > _size)
				{
					insert(end(), n - _size, val);
				}
				_size = n;
			}

			// Returns the size of the storage space currently allocated for the vector, expressed in terms of elements.
			// This capacity is not necessarily equal to the vector size.
			// It can be equal or greater, with the extra space allowing to accommodate for growth without the need to reallocate on each insertion.
			size_type capacity() const
			{
				return (_capacity);
			}

			void	reserve(size_t n)
			{
				if (n > _alloc.max_size())
					throw std::length_error("vector: new capacity cannot be greater than max_size");
				if (n > _capacity)
				{
					pointer tmp;
					tmp = _alloc.allocate(n);
					for (size_type i = 0; i < _size; i++)
					{
						_alloc.construct(tmp + i, _start[i]);
						_alloc.destroy(_start + i);
					}
					_alloc.deallocate(_start, _capacity);
					_start = tmp;
					_capacity = n;
				}
			}

			// Test whether vector is empty.
			bool empty() const
			{
				if (_size == 0)
					return (true);
				return (false);
			}

			/* ELEMENT ACCESS */
			reference	operator[](size_type n)
			{
				return (_start[n]);
			}

			const_reference	operator[](size_type n) const
			{
				return (_start[n]);
			}

			reference at(size_type n)
			{
				if (n >= _size)
					throw std::out_of_range("vector: Out of range exception");
				return (_start[n]);
			}

			const_reference at(size_type n) const
			{
				if (n >= _size)
					throw std::out_of_range("vector: Out of range exception");
				return (_start[n]);
			}

			// Returns a reference to the first element in the vector.
			reference front()
			{
				return (_start[0]);
			}

			const_reference front() const
			{
				return (_start[0]);
			}

			// Returns a reference to the last element in the vector.
			reference back()
			{
				return _start[_size - 1];
			}

			const_reference back() const
			{
				return _start[_size - 1];
			}

			/* MODIFIERS */
			// ASSIGN
			// Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly.
			// 1. RANGE
			template <class InputIterator>
			void assign (InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
			{
				size_type	dist = 0;
				InputIterator	it = first;
				while (it != last)
				{
					dist++;
					it++;
				}
				reserve(dist);
				resize(dist);

				size_type	i = 0;
				while (i < dist && i < _size)
				{
					_alloc.destroy(_start + i);
					i++;
				}
				i = 0;
				it = first;
				while (it != last)
				{
					_alloc.construct(_start + i, *it);
					it++;
					i++;
				}
				if (dist > _size)
					_size = dist;
			}

			// 2. FILL
			void assign (size_type n, const value_type &val)
			{
				size_type	i;

				resize(n);
				i = 0;
				while (i < n && i < _size)
				{
					_alloc.destroy(_start + i);
					i++;
				}
				i = 0;
				while (i < n)
				{
					// _alloc.destroy(_start + i); //
					_alloc.construct(_start + i, val);
					i++;
				}
				if (n > _size)
					_size = n;
			}

			// Add element at the end.
			void push_back (const value_type& val)
			{
				if (_size == _capacity)
				{
					if (_size == 0)
						reserve(1);
					else if (_size + 1 > _capacity)
						reserve(_size * 2);
				}
				_size++;
				_alloc.construct(&back(), val);
			}

			// Removes the last element in the vector, reducing the container size by one.
			// This destroys the removed element.
			void pop_back()
			{
				_alloc.destroy(&back());
				_size--;
			}

			// INSERT
			// https://www.cplusplus.com/reference/vector/vector/insert/
			// 1. SINGLE ELEMENT
			iterator insert(iterator position, const value_type& val)
			{
				difference_type index;
				index = position - begin();
				insert(position, 1, val);
				return iterator(begin() + index);
			}

			// 2. FILL
			void insert (iterator position, size_type n, const value_type& val)
			{
				if (n == 0)
					return ;
				if (n > max_size())
					throw std::length_error("vector: new capacity cannot be greater than max_size");

				size_type pos_index = 0;
				iterator it = begin();
				while (it != position)
				{
					pos_index++;
					it++;
				}

				size_type end_pos = 0;
				while (it != end())
				{
					end_pos++;
					it++;
				}
				if (_size + n > _capacity)
				{
					if (_size + n < _capacity * 2)
						reserve(_capacity * 2);
					else
						reserve(_size + n);
				}
				size_type i = 0;
				while (i < end_pos)
				{
					_alloc.construct(_start + pos_index + n + end_pos - i - 1, _start[pos_index + end_pos - i - 1]);
					_alloc.destroy(_start + pos_index + end_pos - i - 1);
					i++;
				}
				i = 0;
				while (i < n)
				{
					_alloc.construct(_start + pos_index + i, val);
					i++;
				}
				_size += n;
			}

			// 3. RANGE
			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
			{
				size_type range = 0;
				size_type pos_index = 0;
				size_type end_pos = 0;

				for (InputIterator it = first; it != last; it++)
					range++;
				iterator it = begin();
				while (it != position)
				{
					pos_index++;
					it++;
				}
				while (it != end())
				{
					end_pos++;
					it++;
				}

				if (_size + range > _capacity)
				{
					if (_size + range < _capacity * 2)
					{
						reserve(_capacity * 2);
					}
					else
					{
						reserve(_size + range);
					}
				}
				size_type i = 0;
				while (i < end_pos)
				{
					_alloc.construct(_start + pos_index + range + end_pos - i - 1, _start[pos_index + end_pos - i - 1]);
					_alloc.destroy(_start + pos_index + end_pos - i - 1);
					i++;
				}
				i = 0;
				InputIterator it2 = first;
				while (i < range)
				{
					_alloc.construct(_start + pos_index + i, *it2);
					it2++;
					i++;
				}
				_size += range;
			}

			// Removes from the vector a single element
			iterator erase(iterator position)
			{
				pointer		save;
				size_type	i;
				size_type	index;

				index = position - begin();
				save = &(*position);
				if (position + 1 == end())
					pop_back();
				else
				{
					i = 0;
					while (i < index)
						i++;
					_alloc.destroy(_start + i);
					while (i < _size - 1)
					{
						_alloc.construct(_start + i, *(_start + i + 1));
						_alloc.destroy(_start + i + 1);
						i++;
					}
					_size--;
				}
				return (iterator(save));
			}

			// Removes from the vector a range of elements
			iterator erase (iterator first, iterator last)
			{
				size_type	i;
				size_type	index_first;
				size_type	index_last;
				size_type	range;

				index_first = first - iterator(_start);
				index_last = last - iterator(_start);
				range = last - first;
				i = 0;
				while (i < index_first)
					i++;
				while (i < size() - range)
				{
					_alloc.construct(_start + i, *(_start + i + range));
					_alloc.destroy(_start + i + range);
					i++;
				}
				_size -= static_cast<size_type>(range);
				resize(_size);
				return (iterator(first));
			}

			void swap (vector& x)
			{
				pointer	tmp_start = x._start;
				size_type	tmp_capacity = x._capacity;
				size_type	tmp_size = x._size;
				allocator_type	tmp_alloc = x._alloc;

				if (x != *this)
				{
					x._start = _start;
					x._capacity = _capacity;
					x._alloc = _alloc;
					x._size = _size;

					_start = tmp_start;
					_capacity = tmp_capacity;
					_alloc = tmp_alloc;
					_size = tmp_size;
				}
			}

			// Removes all elements from the vector (which are destroyed), leaving the container with a size of 0.
			void	clear()
			{
				if (_start)
				{
					size_type i = 0;
					while (i < _size)
					{
						_alloc.destroy(_start + i);
						i++;
					}
				}
				_size = 0;
			}

			/* ALLOCATOR */
			allocator_type get_allocator() const
			{
				return (_alloc);
			}

		private:
			template <class InputIterator>
			difference_type	distance(InputIterator first, InputIterator last)
			{
				difference_type	counter;

				counter = 0;
				while (first != last)
				{
					counter++;
					first++;
				}
				return (counter);
			}
	};

	/* NON MEMBER FUNCTION OVERLOADS */
	template <class T, class Alloc>
	bool operator==(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
				return (false);

		typename ft::vector<T>::const_iterator	it_lhs = lhs.begin();
		typename ft::vector<T>::const_iterator	it_rhs = rhs.begin();
		while (it_lhs != lhs.end() && it_rhs != rhs.end() &&
				*it_lhs == *it_rhs)
		{
			it_lhs++;
			it_rhs++;
		}
		return (it_lhs == lhs.end() && it_rhs == rhs.end());
	}

	template <class T, class Alloc>
	bool operator!=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool operator<(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool operator<=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
	{
		if (lhs == rhs)
			return (true);
		return (lhs < rhs);
	}

	template <class T, class Alloc>
	bool operator>(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
	{
		if (lhs == rhs)
			return (false);
		return (!(lhs < rhs));
	}

	template <class T, class Alloc>
	bool operator>=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
	{
		if (lhs == rhs)
			return (true);
		return (!(lhs < rhs));
	}

	// the containers exchange references to their data, without actually performing 
	// any element copy or movement
	template <class T, class Alloc>
	void swap(ft::vector<T,Alloc> &x, ft::vector<T,Alloc> &y)
	{
		if (x != y)
			x.swap(y);
	}
}

#endif
