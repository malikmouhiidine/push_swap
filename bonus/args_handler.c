/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhiid <mmouhiid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 22:25:13 by mmouhiid          #+#    #+#             */
/*   Updated: 2024/01/20 00:46:30 by mmouhiid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	process_arg(char *arg, t_list **stack_a)
{
	int		i;
	int		*num;
	char	**tmp_nums;

	tmp_nums = ft_split(arg, ' ');
	if (!tmp_nums || !*tmp_nums)
		exit_handler(1);
	i = 0;
	while (tmp_nums[i])
		i++;
	while (i--)
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
	i = 0;
	while (tmp_nums[i])
		free(tmp_nums[i++]);
	free(tmp_nums);
}

void	iterate_through_args(int argc, char **argv, t_list **stack_a)
{
	while (argc-- > 1)
	{
		process_arg(argv[argc], stack_a);
	}
}
