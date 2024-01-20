/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhiid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 01:44:44 by mmouhiid          #+#    #+#             */
/*   Updated: 2024/01/20 01:45:46 by mmouhiid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	is_valid_number(char *str, int sign, unsigned long long *num)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		if (*num > ULLONG_MAX / 10 || (*num == ULLONG_MAX
				/ 10 && (*str - '0') > (int)(ULLONG_MAX % 10)))
			return (0);
		*num = *num * 10 + (*str++ - '0');
		if (sign == 1 && *num > INT_MAX)
			return (0);
		if (sign == -1 && *num > (unsigned long long)INT_MAX + 1)
			return (0);
	}
	return (1);
}

int	is_valid_int(char *str)
{
	int					sign;
	unsigned long long	num;

	sign = 1;
	num = 0;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		++str;
	}
	if (!*str)
		return (0);
	return (is_valid_number(str, sign, &num));
}
