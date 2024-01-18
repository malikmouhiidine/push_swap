/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhiid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 02:12:21 by mmouhiid          #+#    #+#             */
/*   Updated: 2024/01/18 02:20:59 by mmouhiid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_list	*find_closest_min(t_list *node, t_list **stack_a)
{
	t_list	*closest;
	t_list	*tmp;
	int		min;

	tmp = *stack_a;
	min = INT_MAX;
	closest = NULL;
	while (tmp)
	{
		if (*(int *)node->content > *(int *)tmp->content
			&& *(int *)node->content - *(int *)tmp->content < min)
		{
			min = *(int *)node->content - *(int *)tmp->content;
			closest = tmp;
		}
		tmp = tmp->next;
	}
	return (closest);
}

t_list	*find_closest_bigger(t_list *node, t_list **stack_a)
{
	t_list	*closest;
	t_list	*tmp;
	int		min;

	tmp = *stack_a;
	min = INT_MAX;
	closest = NULL;
	while (tmp)
	{
		if (*(int *)node->content < *(int *)tmp->content
			&& *(int *)tmp->content - *(int *)node->content < min)
		{
			min = *(int *)tmp->content - *(int *)node->content;
			closest = tmp;
		}
		tmp = tmp->next;
	}
	return (closest);
}

t_list	*find_max(t_list *stack_a)
{
	t_list	*tmp;
	t_list	*target;
	int		max;

	tmp = stack_a;
	max = *(int *)tmp->content;
	target = tmp;
	while (tmp)
	{
		if (*(int *)tmp->content > max)
		{
			max = *(int *)tmp->content;
			target = tmp;
		}
		tmp = tmp->next;
	}
	return (target);
}

t_list	*find_min(t_list *stack_a)
{
	t_list	*tmp;
	t_list	*target;
	int		min;

	tmp = stack_a;
	min = *(int *)tmp->content;
	target = tmp;
	while (tmp)
	{
		if (*(int *)tmp->content < min)
		{
			min = *(int *)tmp->content;
			target = tmp;
		}
		tmp = tmp->next;
	}
	return (target);
}

int	get_index(t_list *stack, t_list *node)
{
	int		index;
	t_list	*tmp;

	index = 0;
	tmp = stack;
	while (tmp)
	{
		if (tmp == node)
			return (index);
		index++;
		tmp = tmp->next;
	}
	return (-1);
}
