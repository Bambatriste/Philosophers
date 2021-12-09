/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedouard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:23:06 by aedouard          #+#    #+#             */
/*   Updated: 2021/12/09 15:26:06 by aedouard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void
	free_mutexes(pthread_mutex_t **mutex, int n)
{
	while (n-- > 0)
		free(mutex[n]);
	free(mutex);
}

int	main(int ac, char **av)
{
	t_philo_data	philo_data;
	t_philosopher	**philosophers;
	pthread_mutex_t	**fork;
	pthread_mutex_t	wlock;
	pthread_mutex_t	**rlock;

	if (!check_args(ac, av))
		return (1);
	if (!init_philo_data(ac, av, &philo_data))
		return (1);
	fork = init_mutexes(philo_data.nb_philo);
	rlock = init_mutexes(philo_data.nb_philo);
	if (!fork || !rlock)
		return (1);
	pthread_mutex_init(&wlock, NULL);
	philosophers = init_philosophers(philo_data, fork, &wlock, rlock);
	if (!philosophers)
		return (1);
	if (start_threads(philosophers, philo_data.nb_philo) != 0)
		return (1);
	free_mutexes(fork, philo_data.nb_philo);
	free_mutexes(rlock, philo_data.nb_philo);
	return (0);
}
