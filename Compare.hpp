/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Compare.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 11:19:24 by cboutier          #+#    #+#             */
/*   Updated: 2022/02/11 13:02:56 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPARE_HPP
# define COMPARE_HPP
#include "is_integral.hpp"

namespace ft
{
	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return (false);
			else if (*first1 < *first2)
				return (true);
			++first1;
			++first2;
		}
		return (first2 != last2);
	}

	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2, Compare comp, typename ft::enable_if<!ft::is_integral<InputIterator1>::value, InputIterator1>::type* = NULL)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || comp(*first2, *first1))
				return (false);
			else if (comp(*first1, *first2))
				return (true);
			first1++;
			first2++;
		}
		return (first2 != last2);
	}

	template <class InputIterator1, class InputIterator2>
	bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1 != last1)
		{
			if (!(*first1 == *first2))
				return (false);
			first1++;
			first2++;
		}
		return (true);
	}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate p, typename ft::enable_if<!ft::is_integral<InputIterator1>::value, InputIterator1>::type* = NULL)
	{
		while (first1 != last1)
		{
			if (!p(*first1, *first2))
				return (false);
			++first1;
			++first2;
		}
		return (true);
	}
}

#endif
