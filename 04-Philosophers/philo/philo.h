/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 10:36:22 by dabouab           #+#    #+#             */
/*   Updated: 2024/09/10 14:28:31 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

# define TRUE 1
# define FALSE 0

# define RESET "\x1b[0m"
# define BLUE "\x1b[34m"
# define RED "\x1b[31m"
# define PURPLE "\x1b[35m"
# define GREEN "\x1b[32m"
# define BLACK "\x1b[30m"
# define YELLOW "\x1b[33m"
# define CYAN "\x1b[36m"
# define WHITE "\x1b[37m"

typedef struct s_args
{
	pthread_mutex_t	*meal_mutex;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*death_mutex;
	int				philo_num;
	int				die_time;
	int				death;
	int				eat_time;
	int				sleep_time;
	int				meal_num;
	int				meal_done;
}	t_args;

typedef struct s_fork
{
	pthread_mutex_t	*mutex;
	int				id;
	int				used;
}	t_fork;

typedef struct s_philo
{
	pthread_t		*thread;
	pthread_mutex_t	*id_mutex;
	pthread_mutex_t	*meal_mutex;
	pthread_mutex_t	*state_mutex;
	t_args			*args;
	int				id;
	long			last_meal;
	int				meal_done;
	char			state;
	int				death_time;
	t_fork			*fork1;
	t_fork			*fork2;
}	t_philo;

// ft_atoi
int		ft_isdigit(int c);
int		ft_isspace(char c);
int		ft_atoi(const char *nptr);

// life
int		check_death(t_philo *philos, t_args *args);
int		check_meals(t_philo *philos, t_args *args);
void	eat(t_philo *philo);
void	*life(void *params);
void	table_routine(t_philo *philos, t_args *args);

// state
long	timestamp(void);
void	print_state(t_philo	*philo, char state);
void	change_state(t_philo *philo, char state, t_args *args);

// struct_fork
t_fork	new_fork(int id);
void	add_forks_to_philos(t_fork *forks, t_philo	*philos);
void	clear_forks(t_fork *forks, int num);

// struct_philo
t_philo	new_philo(int id, suseconds_t last_meal, t_args *args);
void	clear_philos(t_philo *philos);

// utils
int		keep_running(t_philo *philo);
int		philo_ate(t_philo *philo);
void	kill_threads(t_philo *philos);
void	clear(char *msg, t_philo *philos, t_fork *forks);

#endif
