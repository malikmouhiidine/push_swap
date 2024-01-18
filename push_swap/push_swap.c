/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhiid <mmouhiid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 00:24:00 by mmouhiid          #+#    #+#             */
/*   Updated: 2024/01/18 23:11:33 by mmouhiid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	check_forduplicates(t_list *stack_a)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = stack_a;
	while (tmp)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (*(int *)tmp->content == *(int *)tmp2->content)
				exit_handler();
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}

int	main(int argc, char **argv)
{
	t_list	*operations;
	t_list	*stack_a;
	t_list	*stack_b;

	if (argc < 2)
		return (0);
	stack_a = NULL;
	stack_b = NULL;
	iterate_through_args(argc, argv, &stack_a);
	check_forduplicates(stack_a);
	operations = get_to_sort_operations(&stack_a, &stack_b);
	while (operations)
	{
		ft_putstr_fd(operations->content, 1);
		operations = operations->next;
	}
	return (0);
}
