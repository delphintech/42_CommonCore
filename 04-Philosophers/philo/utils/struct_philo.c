/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:08:29 by dabouab           #+#    #+#             */
/*   Updated: 2024/09/09 17:06:05 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_philo	new_philo(int id, suseconds_t last_meal, t_args *args)
{
	t_philo	new;

	new.thread = malloc(sizeof(pthread_t));
	new.id_mutex = malloc(sizeof(pthread_mutex_t));
	new.meal_mutex = malloc(sizeof(pthread_mutex_t));
	new.state_mutex = malloc(sizeof(pthread_mutex_t));
	if (!new.thread || !new.meal_mutex || !new.state_mutex)
	{
		new.id = 0;
		return (new);
	}
	pthread_mutex_init(new.meal_mutex, NULL);
	pthread_mutex_init(new.id_mutex, NULL);
	pthread_mutex_init(new.state_mutex, NULL);
	new.id = id;
	new.args = args;
	new.last_meal = last_meal;
	new.meal_done = 0;
	new.state = 't';
	return (new);
}

void	clear_philos(t_philo *philos)
{
	int	i;
	int	num;

	num = philos[0].args->philo_num;
	i = 0;
	while (i < num)
	{
		pthread_mutex_destroy(philos[i].id_mutex);
		pthread_mutex_destroy(philos[i].meal_mutex);
		pthread_mutex_destroy(philos[i].state_mutex);
		free(philos[i].id_mutex);
		free(philos[i].meal_mutex);
		free(philos[i].state_mutex);
		free(philos[i].thread);
		i++;
	}
}
