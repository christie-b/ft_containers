/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:11:16 by cboutier          #+#    #+#             */
/*   Updated: 2022/02/24 14:50:39 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft
{
	template <class T1, class T2>
	struct pair
	{
		typedef T1	first_type;
		typedef T2	second_type;

		first_type	first;
		second_type	second;

		/* DEFAULT CONSTRUCTOR */
		pair()
		: first(), second()
		{};

		/* INITIALIZATION CONSTRUCTOR */
		pair(const first_type &a, const second_type &b)
		: first(a), second(b)
		{};

		/* COPY CONSTRUCTOR */
		template <class U, class V>
		pair(const pair<U, V> &pr)
		: first(pr.first), second(pr.second)
		{};

		pair(const pair &c)
		: first(c.first), second(c.second)
		{};

		pair &operator=(const pair &pr)
		{
			if (this != &pr)
			{
				first = pr.first;
				second = pr.second;
			}
			return (*this);
		};

		~pair()
		{};
	};

	/* RELATIONAL OPERATORS */
	// https://www.cplusplus.com/reference/utility/pair/operators/

	template <class T1, class T2>
	bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	};

	template <class T1, class T2>
	bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (!(lhs == rhs));
	};

	template <class T1, class T2>
	bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second));
	};

	template <class T1, class T2>
	bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (!(rhs < lhs));
	};

	template <class T1, class T2>
	bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (rhs < lhs);
	};

	template <class T1, class T2>
	bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (!(lhs < rhs));
	};

	// https://www.cplusplus.com/reference/utility/make_pair/
	template <class T1, class T2>
	pair<T1, T2> make_pair(T1 x, T2 y)
	{
		return (pair<T1, T2>(x, y));
	};
}

#endif
