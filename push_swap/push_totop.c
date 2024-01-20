/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_totop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhiid <mmouhiid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 01:48:53 by mmouhiid          #+#    #+#             */
/*   Updated: 2024/01/20 02:33:45 by mmouhiid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	add_operations_toto(t_list **operations, char *operation,
		int *index, int condition)
{
	while (*index > 0 && condition)
	{
		ft_lstadd_back(operations, ft_lstnew(operation));
		(*index)--;
	}
}

void	add_reverse_operations(t_list **operations, char *operation,
		int *index, int size)
{
	while (*index < size)
	{
		ft_lstadd_back(operations, ft_lstnew(operation));
		(*index)++;
	}
}

void	handle_lower_half(t_list **operations, t_indices *indices)
{
	add_operations_toto(operations, "rr\n",
		&(indices->node_index), indices->target_index > 0);
	add_operations_toto(operations, "rb\n", &(indices->node_index), 1);
	add_operations_toto(operations, "ra\n", &(indices->target_index), 1);
}

void	handle_upper_half(t_list **operations, t_indices *indices)
{
	add_reverse_operations(operations, "rrr\n",
		&(indices->node_index), indices->stack_b_size);
	add_reverse_operations(operations, "rrb\n",
		&(indices->node_index), indices->stack_b_size);
	add_reverse_operations(operations, "rra\n",
		&(indices->target_index), indices->stack_a_size);
}

void	handle_mixed_case(t_list **operations, t_indices *indices)
{
	add_operations_toto(operations, "rb\n", &(indices->node_index),
		indices->node_index < (float)indices->stack_b_size / 2.0);
	add_reverse_operations(operations, "rrb\n", &(indices->node_index),
		indices->node_index >= (float)indices->stack_b_size / 2.0);
	add_operations_toto(operations, "ra\n", &(indices->target_index),
		indices->target_index < (float)indices->stack_a_size / 2.0);
	add_reverse_operations(operations, "rra\n", &(indices->target_index),
		indices->target_index >= (float)indices->stack_a_size / 2.0);
}
