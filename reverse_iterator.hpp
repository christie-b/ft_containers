/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 09:50:32 by cboutier          #+#    #+#             */
/*   Updated: 2022/02/24 15:16:19 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REV_ITERATOR
# define REV_ITERATOR

# include "Iterator_traits.hpp"

namespace ft
{
	template <class Iterator>
	class reverse_iterator
	{
		public:
			// https://www.cplusplus.com/reference/iterator/reverse_iterator/
			typedef Iterator												iterator_type;
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename iterator_traits<Iterator>::value_type			value_type;
			typedef typename iterator_traits<Iterator>::pointer				pointer;
			typedef typename iterator_traits<Iterator>::reference			reference;
			typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;

		private:
			iterator_type	_base; //the underlying iterator (refers to the element that is next)

		public:
			/* CONSTRUCTORS */
			// https://www.cplusplus.com/reference/iterator/reverse_iterator/reverse_iterator/
			/*
			1) Default constructor.
			Constructs a reverse iterator that points to no object.
			The internal base iterator is value-initialized.
				cf line 776 du code source :
			_GLIBCXX_CONSTEXPR __normal_iterator() _GLIBCXX_NOEXCEPT
			: _M_current(_Iterator()) { }

			Calls the constructor of the iterator type that is called when creating this reverse_iterator.
			Ex: ft::reverse_iterator<map_iter> rev_end (numbers.begin());
			In this example, the map_iter constructor is called.
			*/
			reverse_iterator()
			: _base(iterator_type())
			{}

			/*
			(2) Initalization constructor
			Constructs a reverse iterator from some original iterator it.
			The behavior of the constructed object replicates the original,
			except that it iterates through its pointed elements in the reverse order.
			*/
			explicit reverse_iterator(iterator_type it)
			: _base(it)
			{}

			/*
			(3) Copy constructor
			Constructs a reverse iterator from some other reverse iterator.
			The constructed object keeps the same sense of iteration as rev_it.
			*/
			template <class Iter>
			reverse_iterator (const reverse_iterator<Iter>& rev_it)
			: _base(rev_it.base())
			{}

			// https://www.cplusplus.com/reference/iterator/reverse_iterator/base/
			// Returns a copy of the base iterator.
			iterator_type base() const
			{
				return (_base);
			}

			// https://en.cppreference.com/w/cpp/iterator/reverse_iterator/operator*
			// Returns a reference or pointer to the element previous to current.
			// Internally, the function decreases a copy of its base iterator and returns the result of dereferencing it.
			// https://devblogs.microsoft.com/oldnewthing/20211112-00/?p=105908
			reference	operator*()const
			{
				iterator_type tmp = _base;
				return (*--tmp);
			}

			// Returns an iterator pointing to the element n positions away.
			reverse_iterator	operator+(const difference_type n) const
			{
				return (reverse_iterator(_base - n));
			}

			// Returns an iterator pointing to the element n positions before the currently pointed one.
			reverse_iterator	operator-(const difference_type n) const
			{
				return (reverse_iterator(_base + n));
			}

			// Pre increment operator
			reverse_iterator &operator++()
			{
				--_base;
				return (*this);
			}

			// Post increment operator
			reverse_iterator operator++(int)
			{
				reverse_iterator tmp = *this;
				++(*this); //calls pre increment operator
				return (tmp);
			}

			// Pre decrement operator
			reverse_iterator &operator--()
			{
				++_base;
				return (*this);
			}

			// Post decrement operator
			reverse_iterator operator--(int)
			{
				reverse_iterator tmp = *this;
				--(*this); //calls pre increment operator
				return (tmp);
			}

			// Advances the reverse_iterator by n element positions.
			reverse_iterator &operator+=(difference_type n)
			{
				_base -= n;
				return (*this);
			}

			reverse_iterator &operator-=(difference_type n)
			{
				_base += n;
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

			pointer operator->() const
			{
				return &(operator*());
			}

			// Accesses the element located n positions away
			// from the element currently pointed to by the iterator, but reverse so -n
			reference operator[] (difference_type n) const
			{
				return (_base[-n - 1]);
			}

			// Implicit conversion from iterator to const_iterator
			// https://bytes.com/topic/c/answers/503867-implementing-const_iterator-iterator
			// https://www.cplusplus.com/forum/beginner/259040/

			operator reverse_iterator<iterator_type const>() const
			{
				return (reverse_iterator<iterator_type const>(_base));
			}
	};

	// NON MEMBER FUNCTION OVERLOADS

	// https://en.cppreference.com/w/cpp/iterator/reverse_iterator/operator_cmp
	// https://www.cplusplus.com/reference/iterator/reverse_iterator/operators/
	template <class Iterator>
	bool operator==(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator==(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class Iterator>
	bool operator!=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator!=(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class Iterator>
	bool operator<(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator<(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class Iterator>
	bool operator>(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator>(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class Iterator>
	bool operator<=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator<=(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator>
	bool operator>=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator>=(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	/* NON MEMBER OPERATORS */

	// Returns a reverse iterator pointing to the element located n positions away
	// from the element pointed to by rev_it.
	// Calling the member + operator
	template <class Iterator>
	reverse_iterator<Iterator>
	operator+(typename reverse_iterator<Iterator>::difference_type n,
				const reverse_iterator<Iterator> &rev_it)
	{
		return (rev_it + n);
	}

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type
	operator-(const reverse_iterator<Iterator> &lhs,
			  const reverse_iterator<Iterator> &rhs)
	{
		return (rhs.base() - lhs.base());
	}

	/* For iterator - const_iterator */
	template <class Iterator1, typename Iterator2>
	typename reverse_iterator<Iterator1>::difference_type
	operator-(const reverse_iterator<Iterator1> &lhs,
			  const reverse_iterator<Iterator2> &rhs)
	{
		return (rhs.base() - lhs.base());
	}
}

#endif
