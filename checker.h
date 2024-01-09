/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhiid <mmouhiid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 22:25:13 by mmouhiid          #+#    #+#             */
/*   Updated: 2024/01/08 15:45:50 by mmouhiid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "get_next_line/get_next_line.h"

// Helpers helpers.c
int		ft_strcmp(char *s1, char *s2);
int		is_valid_int(char *str);
int		is_valid_operation(char *operation);
int		is_sorted(t_list *stack);
void	exit_handler(void);

// Operations operations.c
t_list	*get_operations(void);
t_list	*swap(t_list *stack);
void	push(t_list **stack_a, t_list **stack_b);
t_list	*rotate(t_list *stack);
t_list	*reverse_rotate(t_list *stack);
