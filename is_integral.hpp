/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 13:49:34 by cboutier          #+#    #+#             */
/*   Updated: 2022/02/24 15:17:34 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_INTEGRAL_HPP
# define IS_INTEGRAL_HPP

/* IS_INTEGRAL
https://www.cplusplus.com/reference/type_traits/is_integral/
- bool
- char
- wchar_t
- signed char
- short int
- int
- long int
- long long int
- unsigned char
- unsigned short int
- unsigned int
- unsigned long int
- unsigned long long int
*/

namespace ft
{
	template <class T>
	struct is_integral
	{
		static const bool value = false;
	};

	template <>
	struct is_integral<bool>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<char>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<signed char>
	{
		static const bool value = true;
	};
	
	template <>
	struct is_integral<wchar_t>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<short int>
	{
		static const bool value = true;
	};
	
	template <>
	struct is_integral<int>
	{
		static const bool value = true;
	};
	
	template <>
	struct is_integral<long int>
	{
		static const bool value = true;
	};
	
	template <>
	struct is_integral<long long int>
	{
		static const bool value = true;
	};
	
	template <>
	struct is_integral<unsigned char>
	{
		static const bool value = true;
	};
	
	template <>
	struct is_integral<unsigned short int>
	{
		static const bool value = true;
	};
	
	template <>
	struct is_integral<unsigned int>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<unsigned long int>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<unsigned long long int>
	{
		static const bool value = true;
	};


	/* ENABLE IF */
	// https://www.cplusplus.com/reference/type_traits/enable_if/
	template <bool Cond, class T = void>
	struct enable_if
	{};

	template <class T>
	struct enable_if<true, T>
	{
		typedef T	type;
	};
}

#endif
