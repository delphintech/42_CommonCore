/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:08:10 by dabouab           #+#    #+#             */
/*   Updated: 2024/06/26 12:17:23 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	clean_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	ft_isspace(char c)
{
	if (c == '\f' || c == '\n' || c == '\r'
		|| c == '\t' || c == '\v' || c == ' ')
		return (1);
	return (0);
}

int	check_atoi(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]) == 1)
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (ft_isdigit(str[i]) == 0)
		return (0);
	return (1);
}

int	check_args(int argc, char **argv)
{
	int		i;
	int		j;
	char	**tab;
	long	num;

	i = 0;
	while (++i < argc)
	{
		tab = ft_split(argv[1], ' ');
		j = 0;
		while (tab[j])
		{
			num = ft_atoi(argv[i]);
			if (num < INT_MIN || num > INT_MAX)
				return (clean_tab(tab), 0);
			if (num == 0)
			{
				if (check_atoi(argv[i]) == 0)
					return (clean_tab(tab), 0);
			}
			j++;
		}
		clean_tab(tab);
	}
	return (1);
}

void	print_stacks(t_stack **stack, t_stack **b)
{
	t_stack	*node;

	ft_printf("A: ");
	node = *stack;
	while (node)
	{
		ft_printf("%d ", node->nb);
		node = node ->next;
	}
	ft_printf("\nB: ");
	node = *b;
	while (node)
	{
		ft_printf("%d ", node->nb);
		node = node ->next;
	}
	ft_printf("\n\n");
}
