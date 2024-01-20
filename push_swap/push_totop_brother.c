/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_totop_brother.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhiid <mmouhiid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 02:14:44 by mmouhiid          #+#    #+#             */
/*   Updated: 2024/01/20 02:35:44 by mmouhiid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_list	*push_node_target_totop(t_list **stack_b, t_list **stack_a,
			t_list *node, t_list *target)
{
	t_list		*operations;
	t_indices	indices;

	operations = NULL;
	indices.node_index = get_index(*stack_b, node);
	indices.target_index = get_index(*stack_a, target);
	indices.stack_b_size = ft_lstsize(*stack_b);
	indices.stack_a_size = ft_lstsize(*stack_a);
	if (indices.node_index < (float)indices.stack_b_size / 2.0
		&& indices.target_index < (float)indices.stack_a_size / 2.0)
		handle_lower_half(&operations, &indices);
	else if (indices.node_index >= (float)indices.stack_b_size / 2.0
		&& indices.target_index >= (float)indices.stack_a_size / 2.0)
		handle_upper_half(&operations, &indices);
	else
		handle_mixed_case(&operations, &indices);
	return (operations);
}
