/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhiid <mmouhiid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 22:25:13 by mmouhiid          #+#    #+#             */
/*   Updated: 2024/01/20 18:07:02 by mmouhiid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	if (!s1 || !s2)
		return (-1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	is_digit_and_within_range(char *str, unsigned long long *num, int sign)
{
	if (*str < '0' || *str > '9')
		return (0);
	if (*num > ULLONG_MAX / 10 || (*num == ULLONG_MAX / 10
			&& (*str - '0') > (int)(ULLONG_MAX % 10)))
		return (0);
	*num = *num * 10 + (*str - '0');
	if (sign == 1 && *num > INT_MAX)
		return (0);
	if (sign == -1 && *num > (unsigned long long)INT_MAX + 1)
		return (0);
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
	while (*str)
	{
		if (!is_digit_and_within_range(str, &num, sign))
			return (0);
		str++;
	}
	return (1);
}

int	is_valid_operation(char *operation)
{
	if (!ft_strcmp(operation, "sa\n"))
		return (1);
	else if (!ft_strcmp(operation, "sb\n"))
		return (1);
	else if (!ft_strcmp(operation, "ss\n"))
		return (1);
	else if (!ft_strcmp(operation, "pa\n"))
		return (1);
	else if (!ft_strcmp(operation, "pb\n"))
		return (1);
	else if (!ft_strcmp(operation, "ra\n"))
		return (1);
	else if (!ft_strcmp(operation, "rb\n"))
		return (1);
	else if (!ft_strcmp(operation, "rr\n"))
		return (1);
	else if (!ft_strcmp(operation, "rra\n"))
		return (1);
	else if (!ft_strcmp(operation, "rrb\n"))
		return (1);
	else if (!ft_strcmp(operation, "rrr\n"))
		return (1);
	return (0);
}
