/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedouard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 15:27:38 by aedouard          #+#    #+#             */
/*   Updated: 2021/12/09 15:20:35 by aedouard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_args(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac < 5 || ac > 6)
		return (0);
	while (i < ac)
	{
		if (!av[i])
			return (0);
		if (!av[1][0])
			return (0);
		if (!ft_is_only_digits(av[i]))
			return (0);
		i++;
	}
	return (1);
}

int	init_philo_data(int ac, char **av, t_philo_data	*philo_data)
{
	if (!ft_atoi_error(&philo_data->nb_philo, av[1]))
		return (0);
	if (!ft_atoi_error(&philo_data->time_to_die, av[2]))
		return (0);
	if (!ft_atoi_error(&philo_data->time_to_eat, av[3]))
		return (0);
	if (!ft_atoi_error(&philo_data->time_to_sleep, av[4]))
		return (0);
	philo_data->min_eat = -1;
	philo_data->one_dead = 0;
	if (ac == 6)
	{
		if (!ft_atoi_error(&philo_data->min_eat, av[5]))
			return (0);
	}
	return (1);
}

pthread_mutex_t	**init_mutexes(int n)
{
	pthread_mutex_t	**mutexes;
	int				i;

	i = 0;
	mutexes = malloc(sizeof(*mutexes) * n);
	if (!mutexes)
		return (NULL);
	while (i < n)
	{
		mutexes[i] = malloc(sizeof(**mutexes));
		if (!mutexes[i])
			return (NULL);
		i++;
	}
	i = 0;
	while (i < n)
	{
		if (pthread_mutex_init(mutexes[i], NULL) != 0)
			return (NULL);
		i++;
	}
	return (mutexes);
}

void	philo_data_init(t_philosopher *philosopher, t_philo_data data,
			int i, struct timeval time)
{
	philosopher->id = i;
	philosopher->alive = 1;
	philosopher->time_to_die = data.time_to_die;
	philosopher->time_to_eat = data.time_to_eat;
	philosopher->eat_left = data.min_eat;
	philosopher->time_to_sleep = data.time_to_sleep;
	philosopher->ready = 0;
	philosopher->nb_philo = data.nb_philo;
	philosopher->last_eat_sec = time.tv_sec;
	philosopher->last_eat_usec = time.tv_usec;
	philosopher->start_time = (time.tv_sec * 1000 + time.tv_usec / 1000);
}

t_philosopher
	**init_philosophers(t_philo_data data, pthread_mutex_t **fork,
		pthread_mutex_t *wlock, pthread_mutex_t **rlock)
{
	t_philosopher	**philosophers;
	int				i;
	struct timeval	time;

	i = 0;
	gettimeofday(&time, NULL);
	philosophers = malloc(sizeof(*philosophers) * (data.nb_philo + 1));
	if (!philosophers)
		return (NULL);
	while (i < data.nb_philo)
	{
		philosophers[i] = malloc(sizeof(**philosophers));
		if (!philosophers[i])
			return (NULL);
		philo_data_init(philosophers[i], data, i, time);
		philosophers[i]->left_fork = fork[i];
		philosophers[i]->right_fork = fork[(i + 1) % data.nb_philo];
		philosophers[i]->write_lock = wlock;
		philosophers[i]->read_lock = rlock[i];
		philosophers[i]->one_dead = &data.one_dead;
		i++;
	}
	philosophers[i] = NULL;
	return (philosophers);
}
