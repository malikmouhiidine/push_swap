/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhiid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 08:48:06 by mmouhiid          #+#    #+#             */
/*   Updated: 2024/01/21 09:52:33 by mmouhiid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	mixed_case(t_data *d, t_list **operations)
{
	if (d->node_index < (float)d->stack_b_size / 2.0)
		while (d->node_index > 0)
			(ft_lstadd_back(operations,
					ft_lstnew("rb\n")), d->node_index--);
	else
		while (d->node_index < d->stack_b_size)
			(ft_lstadd_back(operations,
					ft_lstnew("rrb\n")), d->node_index++);
	if (d->target_index < (float)d->stack_a_size / 2.0)
		while (d->target_index > 0)
			(ft_lstadd_back(operations,
					ft_lstnew("ra\n")), d->target_index--);
	else
		while (d->target_index < d->stack_a_size)
			(ft_lstadd_back(operations,
					ft_lstnew("rra\n")), d->target_index++);
}

void	upper_case(t_data *d, t_list **operations)
{
	while (d->node_index > 0 && d->target_index > 0)
		(ft_lstadd_back(operations,
				ft_lstnew("rr\n")), d->node_index--, d->target_index--);
	while (d->node_index > 0)
		(ft_lstadd_back(operations, ft_lstnew("rb\n")), d->node_index--);
	while (d->target_index > 0)
		(ft_lstadd_back(operations, ft_lstnew("ra\n")), d->target_index--);
}

void	lower_case(t_data *d, t_list **operations)
{
	while (d->node_index < d->stack_b_size && d->target_index < d->stack_a_size)
		(ft_lstadd_back(operations,
				ft_lstnew("rrr\n")), d->node_index++, d->target_index++);
	while (d->node_index < d->stack_b_size)
		(ft_lstadd_back(operations, ft_lstnew("rrb\n")), d->node_index++);
	while (d->target_index < d->stack_a_size)
		(ft_lstadd_back(operations, ft_lstnew("rra\n")), d->target_index++);
}

t_list	*push_node_target_totop(t_list **stack_b, t_list **stack_a,
			t_list *node, t_list *target)
{
	t_list	*operations;
	t_data	d;

	operations = NULL;
	d.node_index = get_index(*stack_b, node);
	d.target_index = get_index(*stack_a, target);
	d.stack_b_size = ft_lstsize(*stack_b);
	d.stack_a_size = ft_lstsize(*stack_a);
	if (d.node_index < (float)d.stack_b_size / 2.0
		&& d.target_index < (float)d.stack_a_size / 2.0)
		upper_case(&d, &operations);
	else if (d.node_index >= (float)d.stack_b_size / 2.0
		&& d.target_index >= (float)d.stack_a_size / 2.0)
		lower_case(&d, &operations);
	else
		mixed_case(&d, &operations);
	return (operations);
}
