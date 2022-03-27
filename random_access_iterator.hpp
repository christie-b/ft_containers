/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 13:40:56 by cboutier          #+#    #+#             */
/*   Updated: 2022/02/24 15:16:58 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

# include <iostream>

namespace ft
{
	/* ITERATOR TAGS */
	// https://en.cppreference.com/w/cpp/iterator/iterator_tags
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	template <class T>
	class random_access_iterator
	{
		public :
			typedef ptrdiff_t					difference_type;
			typedef T							value_type;
			typedef T*							pointer;
			typedef T&							reference;
			typedef random_access_iterator_tag	iterator_category;

		private :
			T	*_base;

		public :
			/* CONSTRUCTORS */
			// 1. Default Constructor : points to NULL
			random_access_iterator()
			: _base(NULL)
			{}

			// 2. Constructor from pointer : points to the arg passed in
			explicit random_access_iterator(pointer base)
			: _base(base)
			{}

			// 3. Copy Constructor : copy the pointer which points to the element from rhs to this
			random_access_iterator(const random_access_iterator &rhs)
			: _base(rhs._base)
			{}

			// 4. Assignment Operator Overload
			random_access_iterator &operator=(const random_access_iterator &rhs)
			{
				if (this != &rhs)
					_base = rhs._base;
				return (*this);
			}

			virtual ~random_access_iterator()
			{}

			// Implicit conversion from iterator to const_iterator
			// https://bytes.com/topic/c/answers/503867-implementing-const_iterator-iterator
			// https://www.cplusplus.com/forum/beginner/259040/

			operator random_access_iterator<T const>() const
			{
				return (random_access_iterator<T const>(_base));
			}

			reference	operator*() const
			{
				return (*_base);
			}

			// X + n
			random_access_iterator	operator+(const difference_type &n) const
			{
				return random_access_iterator(_base + n);
			}

			random_access_iterator	operator-(const difference_type &n) const
			{
				return random_access_iterator(_base - n);
			}

			// Pre increment operator
			random_access_iterator &operator++()
			{
				++_base;
				return (*this);
			}

			/* INCREMENT OPERATORS */
			// Post increment operator
			random_access_iterator operator++(int)
			{
				random_access_iterator tmp = *this;
				++(*this); // calls pre increment operator
				return (tmp);
			}

			// Pre decrement operator
			random_access_iterator &operator--()
			{
				--_base;
				return (*this);
			}

			// Post decrement operator
			random_access_iterator operator--(int)
			{
				random_access_iterator tmp = *this;
				--(*this); //calls pre increment operator
				return (tmp);
			}

			// Advances the iterator by n element positions
			random_access_iterator &operator+=(difference_type n)
			{
				_base += n;
				return (*this);
			}

			random_access_iterator &operator-=(difference_type n)
			{
				_base -= n;
				return (*this);
			}

			//https://stackoverflow.com/questions/8777845/overloading-member-access-operators
			/*
			it must return a pointer that can be used to select what the pointer dereference operator arrow is pointing at.
			The extra functionality is provided for convenience, so you do not have to call
			a->->func();
			You can simply do:
			a->func();
			*/

			pointer	operator->() const
			{
				return (&(operator*()));
			}

			reference operator[](difference_type n) const
			{
				return (_base[n]);
			}

			pointer	base() const
			{
				return (_base);
			}
	};

	// NON MEMBER FUNCTION OVERLOADS
	template <class T>
	bool operator==(const ft::random_access_iterator<T> &lhs,
				const ft::random_access_iterator<T> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	// when comparing iterator with const iterator
	template <class T1, class T2>
	bool operator==(const ft::random_access_iterator<T1> &lhs,
				const ft::random_access_iterator<T2> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class T>
	bool operator!=(const ft::random_access_iterator<T> &lhs,
				const ft::random_access_iterator<T> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class T1, class T2>
	bool operator!=(const ft::random_access_iterator<T1> &lhs,
				const ft::random_access_iterator<T2> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class T>
	bool operator<(const ft::random_access_iterator <T> &lhs,
				const ft::random_access_iterator <T> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class T1, class T2>
	bool operator<(const ft::random_access_iterator <T1> &lhs,
				const ft::random_access_iterator <T2> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class T>
	bool operator>(const ft::random_access_iterator <T> &lhs,
				const ft::random_access_iterator <T> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class T1, class T2>
	bool operator>(const ft::random_access_iterator <T1> &lhs,
				const ft::random_access_iterator <T2> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class T>
	bool operator<=(const ft::random_access_iterator<T> &lhs,
				const ft::random_access_iterator<T> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <class T1, class T2>
	bool operator<=(const ft::random_access_iterator<T1> &lhs,
				const ft::random_access_iterator<T2> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <class T>
	bool operator>=(const ft::random_access_iterator<T> &lhs,
				const ft::random_access_iterator<T> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <class T1, class T2>
	bool operator>=(const ft::random_access_iterator<T1> &lhs,
				const ft::random_access_iterator<T2> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	// n + X, calls member operator+
	template <class T>
	random_access_iterator<T>
	operator+(typename ft::random_access_iterator<T>::difference_type n,
				typename ft::random_access_iterator<T> &it)
	{
		return (it + n);
	}

	template <class T>
	typename random_access_iterator<T>::difference_type
	operator-(const random_access_iterator<T> &lhs,
			const random_access_iterator<T> &rhs)
	{
		return (lhs.base() - rhs.base());
	}

	// To substract iterator and const iterator or the reverse
	template <class T1, class T2>
	typename random_access_iterator<T1>::difference_type
	operator-(const random_access_iterator<T1> &lhs,
			const random_access_iterator<T2> &rhs)
	{
		return (lhs.base() - rhs.base());
	}
}

#endif
