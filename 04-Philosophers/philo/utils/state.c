/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:27:39 by dabouab           #+#    #+#             */
/*   Updated: 2024/09/10 14:31:06 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	timestamp(void)
{
	struct timeval		timestamp;
	long				micro;

	gettimeofday(&timestamp, NULL);
	micro = timestamp.tv_sec * 1000 + timestamp.tv_usec / 1000;
	return (micro);
}

void	print_state(t_philo	*philo, char state)
{
	pthread_mutex_lock(philo->id_mutex);
	pthread_mutex_lock(philo->args->print_mutex);
	if (state == 'f')
	{
		printf(YELLOW "%ld %d has taken a fork\n" RESET,
			timestamp(), philo->id);
		usleep(1000);
	}
	if (state == 'e')
		printf(GREEN "%ld %d is eating\n" RESET, timestamp(), philo->id);
	if (state == 's')
	{
		printf(BLUE "%ld %d is sleeping\n" RESET, timestamp(), philo->id);
		usleep(philo->args->sleep_time * 1000);
	}
	if (state == 't')
	{
		printf(PURPLE "%ld %d is thinking\n" RESET, timestamp(), philo->id);
		usleep(1000);
	}
	if (state == 'd')
		printf(RED "%ld %d has died\n" RESET, timestamp(), philo->id);
	pthread_mutex_unlock(philo->args->print_mutex);
	pthread_mutex_unlock(philo->id_mutex);
}

void	change_state(t_philo *philo, char state, t_args *args)
{
	if (keep_running(philo))
	{
		if (state == 't' || state == 'e' || state == 's')
		{
			pthread_mutex_lock(philo->state_mutex);
			philo->state = state;
			pthread_mutex_unlock(philo->state_mutex);
		}
		if (state == 't')
			print_state(philo, 't');
		if (state == 'f')
			print_state(philo, 'f');
		if (state == 'e')
		{
			print_state(philo, 'e');
			pthread_mutex_lock(philo->meal_mutex);
			philo->meal_done += 1;
			philo->last_meal = timestamp();
			pthread_mutex_unlock(philo->meal_mutex);
			usleep(args->eat_time * 1000);
		}
		if (state == 's')
			print_state(philo, 's');
	}
}
