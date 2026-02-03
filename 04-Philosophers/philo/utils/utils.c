/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:48:44 by dabouab           #+#    #+#             */
/*   Updated: 2024/09/09 16:29:25 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	keep_running(t_philo *philo)
{
	pthread_mutex_lock(philo->args->meal_mutex);
	pthread_mutex_lock(philo->args->death_mutex);
	if (philo->args->philo_num == 1)
	{
		pthread_mutex_unlock(philo->args->meal_mutex);
		pthread_mutex_unlock(philo->args->death_mutex);
		return (FALSE);
	}
	else if (philo->args->death == FALSE
		&& (philo->args->meal_done < philo->args->meal_num
			|| philo->args->meal_num == -1))
	{
		pthread_mutex_unlock(philo->args->meal_mutex);
		pthread_mutex_unlock(philo->args->death_mutex);
		return (TRUE);
	}
	pthread_mutex_unlock(philo->args->meal_mutex);
	pthread_mutex_unlock(philo->args->death_mutex);
	return (FALSE);
}

int	philo_ate(t_philo *philo)
{
	pthread_mutex_lock(philo->args->meal_mutex);
	pthread_mutex_lock(philo->meal_mutex);
	if (philo->meal_done < philo->args->meal_done + 1)
	{
		pthread_mutex_unlock(philo->args->meal_mutex);
		pthread_mutex_unlock(philo->meal_mutex);
		return (FALSE);
	}
	pthread_mutex_unlock(philo->args->meal_mutex);
	pthread_mutex_unlock(philo->meal_mutex);
	return (TRUE);
}

void	kill_threads(t_philo *philos)
{
	int	i;
	int	num;

	num = philos[0].args->philo_num;
	i = 0;
	while (i < num)
	{
		pthread_join(*(philos[i].thread), NULL);
		i++;
	}
}

void	clear(char *msg, t_philo *philos, t_fork *forks)
{
	if (philos)
		clear_philos(philos);
	if (forks)
		clear_forks(forks, philos[0].args->philo_num);
	if (msg)
		printf("%s\n", msg);
}
