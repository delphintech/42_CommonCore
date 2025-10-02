/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:08:29 by dabouab           #+#    #+#             */
/*   Updated: 2024/09/09 16:51:19 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_fork	new_fork(int id)
{
	t_fork	new;

	new.mutex = malloc(sizeof(pthread_mutex_t));
	if (!new.mutex)
	{
		new.id = 0;
		return (new);
	}
	pthread_mutex_init(new.mutex, NULL);
	new.id = id;
	new.used = FALSE;
	return (new);
}

void	add_forks_to_philos(t_fork *forks, t_philo	*philos)
{
	int	i;
	int	philo_num;

	philo_num = philos[0].args->philo_num;
	i = 0;
	while (i < philo_num)
	{
		if (philos[i].id % 2 != 0 && philos[i].id != philo_num)
		{
			philos[i].fork1 = &forks[i];
			philos[i].fork2 = &forks[i + 1];
		}
		else if (philos[i].id != philo_num)
		{
			philos[i].fork1 = &forks[i + 1];
			philos[i].fork2 = &forks[i];
		}
		else
		{
			philos[i].fork1 = &forks[0];
			philos[i].fork2 = &forks[i];
		}
		i++;
	}
}

void	clear_forks(t_fork *forks, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pthread_mutex_destroy(forks[i].mutex);
		free(forks[i].mutex);
		i++;
	}
}
