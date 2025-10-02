/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:59:06 by dabouab           #+#    #+#             */
/*   Updated: 2024/09/10 14:53:21 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_death(t_philo *philos, t_args *args)
{
	int	i;

	while (args->death == FALSE && check_meals(philos, args) == FALSE)
	{
		i = 0;
		while (i < args->philo_num)
		{
			pthread_mutex_lock(philos[i].args->death_mutex);
			pthread_mutex_lock(philos[i].meal_mutex);
			pthread_mutex_lock(philos[i].state_mutex);
			if (args->death == FALSE && philos[i].state != 'e'
				&& timestamp() - philos[i].last_meal >= args->die_time)
			{
				pthread_mutex_unlock(philos[i].state_mutex);
				args->death = TRUE;
				print_state(&philos[i], 'd');
			}
			else
				pthread_mutex_unlock(philos[i].state_mutex);
			pthread_mutex_unlock(philos[i].args->death_mutex);
			pthread_mutex_unlock(philos[i].meal_mutex);
			i++;
		}
	}
	return (TRUE);
}

int	check_meals(t_philo *philos, t_args *args)
{
	int		all_done;
	int		i;

	all_done = 1;
	i = 0;
	while (i < args->philo_num)
		if (!philo_ate(&philos[i++]))
			all_done = 0;
	if (all_done == 1)
	{
		pthread_mutex_lock(args->meal_mutex);
		args->meal_done += 1;
		pthread_mutex_unlock(args->meal_mutex);
	}
	if (args->meal_num == -1)
		return (FALSE);
	if (args->meal_done == args->meal_num)
	{
		pthread_mutex_lock(args->print_mutex);
		printf(RED "All philosophers ate %d times\n" RESET, args->meal_num);
		pthread_mutex_unlock(args->print_mutex);
		return (TRUE);
	}
	return (FALSE);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->fork1->mutex);
	pthread_mutex_lock(philo->fork2->mutex);
	if (philo->fork1->used == FALSE && philo->fork2->used == FALSE)
	{
		philo->fork1->used = TRUE;
		change_state(philo, 'f', philo->args);
		philo->fork2->used = TRUE;
		change_state(philo, 'f', philo->args);
		change_state(philo, 'e', philo->args);
		philo->fork1->used = FALSE;
		philo->fork2->used = FALSE;
		pthread_mutex_unlock(philo->fork2->mutex);
		pthread_mutex_unlock(philo->fork1->mutex);
		change_state(philo, 's', philo->args);
		change_state(philo, 't', philo->args);
	}
	else
	{
		pthread_mutex_unlock(philo->fork2->mutex);
		pthread_mutex_unlock(philo->fork1->mutex);
	}
}

void	*life(void *params)
{
	t_philo	*philo;

	philo = (t_philo *)params;
	while (keep_running(philo))
	{
		if (!philo_ate(philo))
			eat(philo);
	}
	return (NULL);
}

void	table_routine(t_philo *philos, t_args *args)
{
	int	i;

	i = 0;
	while (i < args->philo_num)
	{
		pthread_create(philos[i].thread, NULL, &life, (void *) &philos[i]);
		i++;
	}
	check_death(&philos[0], args);
	kill_threads(philos);
}
