/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhiid <mmouhiid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 22:25:13 by mmouhiid          #+#    #+#             */
/*   Updated: 2024/01/20 02:35:36 by mmouhiid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../get_next_line/get_next_line.h"
#include <limits.h>

typedef struct s_indices
{
	int		node_index;
	int		target_index;
	int		stack_b_size;
	int		stack_a_size;
}				t_indices;

int		ft_strcmp(char *s1, char *s2);
int		is_valid_int(char *str);
int		is_valid_operation(char *operation);
int		is_sorted(t_list *stack);
void	exit_handler(int code);

t_list	*get_operations(void);
t_list	*swap(t_list *stack);
void	push(t_list **stack_a, t_list **stack_b);
t_list	*rotate(t_list *stack);
t_list	*reverse_rotate(t_list *stack);

void	iterate_through_args(int argc, char **argv, t_list **stack_a);

void	apply_swap_push(t_list **stack_a, t_list **stack_b, t_list *operations);
void	apply_rotate_reverse(t_list **stack_a, t_list **stack_b,
			t_list *operations);
void	apply_operations(t_list **stack_a, t_list **stack_b,
			t_list *operations);

t_list	*sort_3_numbers(t_list	**stack_a);
void	sort_4_numbers(t_list **stack_a, t_list **stack_b, t_list **operations);
void	turk_sort_numbers(t_list **stack_a, t_list **stack_b,
			t_list **operations);

t_list	*push_node_target_totop(t_list **stack_b, t_list **stack_a,
			t_list *node, t_list *target);
t_list	*make_min_on_top_ops(t_list **stack_a);
t_list	*find_target(t_list *node, t_list **stack, int closest_bigger);
t_list	*get_to_sort_operations(t_list **stack_a, t_list **stack_b);

t_list	*find_closest_min(t_list *node, t_list **stack_a);
t_list	*find_closest_bigger(t_list *node, t_list **stack_a);
t_list	*find_max(t_list *stack_a);
t_list	*find_min(t_list *stack_a);
int		get_index(t_list *stack, t_list *node);

void	add_operation(t_list **operations, char *operation);
void	apply_and_add_operation(t_list **stack_a, t_list **stack_b,
			t_list **operations, char *operation);
void	add_operations(t_list **operations, char *operation1, char *operation2);
void	push_and_add_operations(t_list **stack_a,
			t_list **stack_b, t_list **operations);
void	apply_operations_based_on_median(t_list **stack_a,
			t_list **stack_b, t_list **operations, long long median);

void	handle_lower_half(t_list **operations, t_indices *indices);
void	handle_upper_half(t_list **operations, t_indices *indices);
void	handle_mixed_case(t_list **operations, t_indices *indices);