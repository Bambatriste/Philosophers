/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedouard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 15:27:01 by aedouard          #+#    #+#             */
/*   Updated: 2021/12/08 19:28:01 by aedouard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*remember :
lock -> read -> unlock
*/


/* todo :

norme
*/

static void
	free_mutexes(pthread_mutex_t **mutex, int n)
{
	while (n-- > 0)
		free(mutex[n]);
	free(mutex);
}





long    get_time(void)
{
    struct timeval  tp;
    long            milliseconds;

    gettimeofday(&tp, NULL);
    milliseconds = tp.tv_sec * 1000;
    milliseconds += tp.tv_usec / 1000;
    return (milliseconds);
}


void	ft_usleep(long value)
{

	long start_time = get_time();
	long time = get_time();
	long n = 2;

	while (time - start_time - value < 0)
	{
		usleep(value / n);
		time = get_time();
		n++;
	}
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

	/*int i;
	long time = get_time();

	i = 0;

	while (1)
	{
		printf("%ld\n", get_time() - time);
		ft_usleep(200 );
		i++;
	}
		while (1)
	{
		printf("%ld\n", get_time() - time);
		ft_usleep(200 * 1000);
		i++;
	}*/




	return (0);
}
