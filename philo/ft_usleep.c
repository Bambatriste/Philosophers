/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedouard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 16:34:49 by aedouard          #+#    #+#             */
/*   Updated: 2021/12/09 16:34:53 by aedouard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time(void)
{
	struct timeval	tp;
	long			milliseconds;

	gettimeofday(&tp, NULL);
	milliseconds = tp.tv_sec * 1000;
	milliseconds += tp.tv_usec / 1000;
	return (milliseconds);
}

void	ft_usleep(long value, t_philosopher *philo)
{
	long int	start_time;
	long int	time;
	long int	n;

	start_time = get_time();
	time = get_time();
	n = 2;
	while (time - start_time - value < 0)
	{
		pthread_mutex_lock(philo->write_lock);
		if (*(philo->one_dead))
		{
			pthread_mutex_unlock(philo->write_lock);
			break ;
		}
		pthread_mutex_unlock(philo->write_lock);
		usleep(value / n);
		time = get_time();
		n++;
	}
}
