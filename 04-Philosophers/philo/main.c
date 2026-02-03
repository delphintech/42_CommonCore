/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 10:35:57 by dabouab           #+#    #+#             */
/*   Updated: 2024/09/10 14:40:54 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clear_args(t_args *args)
{
	pthread_mutex_destroy(args->meal_mutex);
	pthread_mutex_destroy(args->print_mutex);
	pthread_mutex_destroy(args->death_mutex);
	free(args->meal_mutex);
	free(args->print_mutex);
	free(args->death_mutex);
}

int	check_args(int ac, char **av, t_args *args)
{
	if (ac < 5)
		return (clear("Not enough arguments", NULL, NULL), EXIT_FAILURE);
	if (ac > 6)
		return (clear("Too many arguments", NULL, NULL), EXIT_FAILURE);
	args->philo_num = ft_atoi(av[1]);
	args->die_time = ft_atoi(av[2]);
	args->eat_time = ft_atoi(av[3]);
	args->sleep_time = ft_atoi(av[4]);
	args->death = FALSE;
	args->meal_done = 0;
	if (ac == 6)
		args->meal_num = ft_atoi(av[5]);
	else
		args->meal_num = -1;
	if (args->philo_num < 0 || args->philo_num > 200
		|| args->die_time < 0 || args->eat_time < 0
		|| args->sleep_time < 0 || (ac == 6 && args->meal_num < 0))
		return (clear("Invalid arguments", NULL, NULL), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	initialize(t_args *args, t_philo *philos, t_fork *forks)
{
	int		i;

	i = 0;
	while (i < args->philo_num)
	{
		philos[i] = new_philo(i + 1, timestamp(), args);
		forks[i] = new_fork(i + 1);
		if (philos[i].id == 0 || forks[i].id == 0)
			return (clear("Malloc failed", &philos[0], &forks[0]),
				EXIT_FAILURE);
		i++;
	}
	add_forks_to_philos(&forks[0], &philos[0]);
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	t_args	args;
	t_philo	philos[200];
	t_fork	forks[200];

	if (check_args(ac, av, &args) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (initialize(&args, &philos[0], &forks[0]) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	args.meal_mutex = malloc(sizeof(pthread_mutex_t));
	args.print_mutex = malloc(sizeof(pthread_mutex_t));
	args.death_mutex = malloc(sizeof(pthread_mutex_t));
	if (!args.meal_mutex || !args.death_mutex || !args.print_mutex)
		return (EXIT_FAILURE);
	pthread_mutex_init(args.meal_mutex, NULL);
	pthread_mutex_init(args.print_mutex, NULL);
	pthread_mutex_init(args.death_mutex, NULL);
	table_routine(&philos[0], &args);
	clear_args(&args);
	clear(NULL, &philos[0], &forks[0]);
	return (EXIT_SUCCESS);
}
