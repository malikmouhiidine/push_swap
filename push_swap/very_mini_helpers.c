/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   very_mini_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhiid <mmouhiid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:21:06 by mmouhiid          #+#    #+#             */
/*   Updated: 2024/01/20 18:21:07 by mmouhiid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	is_sorted(t_list *stack)
{
	while (stack && stack->next)
	{
		if (stack->next && (*(int *)stack->next->content
				< *(int *)stack->content))
			return (0);
		stack = stack->next;
	}
	return (1);
}

void	exit_handler(int code)
{
	if (code == 1)
	{
		ft_putstr_fd("Error\n", 2);
		exit(1);
	}
	exit(0);
}
