/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhiid <mmouhiid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 22:25:13 by mmouhiid          #+#    #+#             */
/*   Updated: 2024/01/21 10:44:34 by mmouhiid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	add_el_process(char **tmp_nums, t_list **stack_a, int *num, int i)
{
	if (is_valid_int(tmp_nums[i]))
	{
		num = (int *)malloc(sizeof(int));
		*num = ft_atoi(tmp_nums[i]);
		ft_lstadd_front(stack_a, ft_lstnew(num));
	}
	else
		exit_handler(1);
}

void	iterate_through_args(int argc, char **argv, t_list **stack_a)
{
	int		i;
	int		*num;
	char	**tmp_nums;

	num = NULL;
	while (argc-- > 1)
	{
		tmp_nums = ft_split(argv[argc], ' ');
		if (!tmp_nums || !*tmp_nums)
			exit_handler(1);
		i = 0;
		while (tmp_nums[i])
			i++;
		while (i--)
			add_el_process(tmp_nums, stack_a, num, i);
		i = 0;
		while (tmp_nums[i])
			free(tmp_nums[i++]);
		free(tmp_nums);
	}
}
