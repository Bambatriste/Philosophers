/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedouard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 15:27:01 by aedouard          #+#    #+#             */
/*   Updated: 2021/12/08 14:09:14 by aedouard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* todo :

timestamp in one value (clean)
lock -> read -> unlock
no mutex lock at end of main routine


*/

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

	if (check_args(ac, av) == -1)
		return (1);
	philo_data = init_philo_data(ac, av);
	fork = init_mutexes(philo_data.nb_philo);
	rlock = init_mutexes(philo_data.nb_philo);
	if (!fork)
		return (1);
	pthread_mutex_init(&wlock, NULL);
	philosophers = init_philosophers(philo_data, fork, &wlock, rlock);
	if (!philosophers)
		return (1);
	if (start_threads(philosophers, philo_data.nb_philo) != 0)
		return (1);
	free_mutexes(fork, philo_data.nb_philo);
	return (0);
}
