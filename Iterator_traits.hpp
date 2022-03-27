/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:09:21 by cboutier          #+#    #+#             */
/*   Updated: 2022/02/17 10:24:19 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

# include <cstddef>
# include "random_access_iterator.hpp"

// https://en.cppreference.com/w/cpp/iterator/iterator_traits
// https://www.cplusplus.com/reference/iterator/iterator_traits/

/*
Traits class defining properties of iterators.
Standard algorithms determine certain properties of the iterators passed to them and the range
they represent by using the members of the corresponding iterator_traits instantiation.
*/

namespace ft
{
	template <class Iterator>
	class iterator_traits
	{
		public:
			typedef typename Iterator::difference_type		difference_type;
			typedef typename Iterator::value_type			value_type;
			typedef typename Iterator::pointer				pointer;
			typedef typename Iterator::reference			reference;
			typedef typename Iterator::iterator_category	iterator_category;
	};

	template <class T>
	class iterator_traits<T *>
	{
		public:
			typedef ptrdiff_t						difference_type;
			typedef T								value_type;
			typedef T								*pointer;
			typedef T								&reference;
			typedef random_access_iterator_tag		iterator_category;
	};

	template <class T>
	class iterator_traits<const T *>
	{
		public:
			typedef ptrdiff_t						difference_type;
			typedef T								value_type;
			typedef const T							*pointer;
			typedef const T							&reference;
			typedef random_access_iterator_tag		iterator_category;
	};
}

#endif
