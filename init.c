/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedouard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 15:27:38 by aedouard          #+#    #+#             */
/*   Updated: 2021/12/08 13:55:56 by aedouard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_args(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (!ft_is_only_digits(av[i]))
			return (-1);
		i++;
	}
	return (1);
}

t_philo_data	init_philo_data(int ac, char **av)
{
	t_philo_data	philo_data;
	int				i;

	i = 0;
	philo_data.nb_philo = ft_atoi(av[1]);
	philo_data.time_to_die = (long int)ft_atoi(av[2]);
	philo_data.time_to_eat = (long int)ft_atoi(av[3]);
	philo_data.time_to_sleep = (long int)ft_atoi(av[4]);
	philo_data.min_eat = -1;
	philo_data.one_dead = 0;
	if (ac == 6)
		philo_data.min_eat = ft_atoi(av[5]);
	return (philo_data);
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
