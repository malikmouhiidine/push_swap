/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhiid <mmouhiid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 22:25:13 by mmouhiid          #+#    #+#             */
/*   Updated: 2023/12/24 06:12:45 by mmouhiid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdio.h>

int	is_valid_int(char *str)
{
	if (*str == '-')
		str++;
	if (!*str || *str == '0')
		return (0);
	while (*str)
	{
		if (*str < '0' || *str++ > '9')
			return (0);
	}
	return (1);
}

void	exit_handler(void)
{
	ft_putstr_fd("Error\n", 1);
	exit(1);
}

int	main(int argc, char **argv)
{
	int		i;
	char	**tmp_nums;
	t_list	*stack_a;
	t_list	*stack_b;

	if (argc < 2)
		return (0);
	stack_a = NULL;
	stack_b = NULL;
	while (argc-- > 1)
	{
		tmp_nums = ft_split(argv[argc], ' ');
		if (!tmp_nums || !*tmp_nums)
			exit_handler();
		i = 0;
		while (tmp_nums[i])
			i++;
		while (i--)
		{
			if (is_valid_int(tmp_nums[i]))
				ft_lstadd_front(&stack_a, ft_lstnew(tmp_nums[i]));
			else
				exit_handler();
		}
	}
	while (stack_a && stack_a->content)
	{
		ft_putstr_fd((char *)stack_a->content, 1);
		ft_putstr_fd("\n", 1);
		stack_a = stack_a->next;
	}
	return (0);
}
