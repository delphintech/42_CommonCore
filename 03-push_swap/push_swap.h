/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:41:36 by dabouab           #+#    #+#             */
/*   Updated: 2024/06/26 12:22:43 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "./libft/libft.h"
# include <limits.h>
# include <stdlib.h>

typedef struct s_stack{
	int				nb;
	int				place;
	struct s_stack	*prev;
	struct s_stack	*next;
}					t_stack;

int		ft_stcsize(t_stack *stc);
t_stack	*ft_stclast(t_stack *stc);
t_stack	*ft_stcnew(int nb);
void	ft_stcadd_back(t_stack **stc, t_stack *new);
void	ft_stcadd_front(t_stack **stc, t_stack *new);
void	clean_tab(char **tab);
int		ft_isspace(char c);
int		check_atoi(char *str);
int		check_args(int argc, char **argv);
t_stack	**to_stack(int argc, char **argv);
int		check_stack(t_stack	**stack);
void	clean_stack(t_stack **stack);
void	add_place(t_stack **stack, int place);
int		check_sorted(t_stack **stack);
t_stack	*find_min(t_stack **stack);
t_stack	*find_max(t_stack **stack);
void	ft_s(t_stack **stack, char print);
void	ft_ss(t_stack **stack, t_stack **b, char print);
void	ft_p(t_stack **st1, t_stack **st2, char print);
void	ft_r(t_stack **stack, char print);
void	ft_rr(t_stack **stack, char print);
void	smart_rotate(t_stack **stack, int place, char stc);
void	sort_three(t_stack **stc);
void	sort_five(t_stack **sta, t_stack **stb);

void	print_stacks(t_stack **stack, t_stack **b);

#endif