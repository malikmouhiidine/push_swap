/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhiid <mmouhiid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 22:25:13 by mmouhiid          #+#    #+#             */
/*   Updated: 2024/01/20 00:47:20 by mmouhiid         ###   ########.fr       */
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
				exit_handler(1);
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}

int	main(int argc, char **argv)
{
	int		size_diff;
	t_list	*operations;
	t_list	*stack_a;
	t_list	*stack_b;

	if (argc < 2)
		return (0);
	stack_a = NULL;
	stack_b = NULL;
	iterate_through_args(argc, argv, &stack_a);
	check_forduplicates(stack_a);
	operations = get_operations();
	size_diff = ft_lstsize(stack_a);
	stack_a = apply_operations(stack_a, stack_b, operations);
	size_diff = ft_lstsize(stack_a) - size_diff;
	if (is_sorted(stack_a) && size_diff == 0)
		ft_putstr_fd("OK\n", 1);
	else
		ft_putstr_fd("KO\n", 1);
	exit_handler(0);
	return (0);
}
