/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 09:54:10 by cboutier          #+#    #+#             */
/*   Updated: 2022/02/24 09:54:12 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "Vector.hpp"

namespace ft
{
	template < class T, class Container = ft::vector<T> >
	class stack
	{
		public:
			/* MEMBER TYPES */
			typedef Container							container_type;
			typedef typename Container::value_type		value_type;
			typedef typename Container::size_type		size_type;
			typedef typename Container::reference		reference;
			typedef typename Container::const_reference	const_reference;

			/* CONSTRUCTOR */
			explicit stack(const container_type & ctnr = container_type())
			: c(ctnr)
			{};

			stack<T>(stack<T> const &rhs)
			{
				*this = rhs;
			}

			stack<T> &operator=(stack<T> const &rhs)
			{
				c = rhs.c;
				return (*this);
			}

			~stack()
			{};

			/* ELEMENT ACCESS */
			reference		top()
			{
				return (c.back());
			}

			const_reference	top() const
			{
				return (c.back());
			}

			/* CAPACITY */
			bool			empty() const
			{
				return (c.empty());
			}

			size_type		size() const
			{
				return (c.size());
			}

			/* MODIFIERS */
			void			push(const value_type &value)
			{
				c.push_back(value);
			}

			void			pop()
			{
				c.pop_back();
			}

			/* PROTOTYPES */
			template<class T1, class Container1> friend bool operator==(const stack<T1, Container1> &lhs, const stack<T1, Container1> &rhs);
			template<class T1, class Container1> friend bool operator!=(const stack<T1, Container1> &lhs, const stack<T1, Container1> &rhs);
			template<class T1, class Container1> friend bool operator<(const stack<T1, Container1> &lhs, const stack<T1, Container1> &rhs);
			template<class T1, class Container1> friend bool operator<=(const stack<T1, Container1> &lhs, const stack<T1, Container1> &rhs);
			template<class T1, class Container1> friend bool operator>(const stack<T1, Container1> &lhs, const stack<T1, Container1> &rhs);
			template<class T1, class Container1> friend bool operator>=(const stack<T1, Container1> &lhs, const stack<T1, Container1> &rhs);

		protected:
		/* MEMBER OBJECTS */
			Container	c;
	};
	
	/* OPERATORS */
	template <class T1, class Container1>
	bool operator==(const stack<T1, Container1> &lhs, const stack<T1, Container1> &rhs)
	{
		return (lhs.c == rhs.c);
	}

	template <class T1, class Container1>
	bool operator!=(const stack<T1, Container1> &lhs, const stack<T1, Container1> &rhs)
	{
		return (lhs.c != rhs.c);
	}

	template <class T1, class Container1>
	bool operator<(const stack<T1, Container1> &lhs, const stack<T1, Container1> &rhs)
	{
		return (lhs.c < rhs.c);
	}

	template <class T1, class Container1>
	bool operator<=(const stack<T1, Container1> &lhs, const stack<T1, Container1> &rhs)
	{
		return (lhs.c <= rhs.c);
	}

	template <class T1, class Container1>
	bool operator>(const stack<T1, Container1> &lhs, const stack<T1, Container1> &rhs)
	{
		return (lhs.c > rhs.c);
	}

	template <class T1, class Container1>
	bool operator>=(const stack<T1, Container1> &lhs, const stack<T1, Container1> &rhs)
	{
		return (lhs.c >= rhs.c);
	}
};

#endif
