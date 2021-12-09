/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedouard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 15:26:34 by aedouard          #+#    #+#             */
/*   Updated: 2021/12/09 15:19:01 by aedouard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

pthread_mutex_t	*fork_to_pick(t_philosopher *philo, int fork_value)
{
	pthread_mutex_t	*fork;

	if (fork_value == LEFT_FORK)
	{
		if (philo->id & 1)
			fork = philo->left_fork;
		else
			fork = philo->right_fork;
	}
	else
	{
		if (philo->id & 1)
			fork = philo->right_fork;
		else
			fork = philo->left_fork;
	}
	return (fork);
}

int	take_fork(t_philosopher *philosopher, int fork_value)
{
	pthread_mutex_t	*fork;

	if (philosopher->left_fork == philosopher->right_fork
		&& fork_value == RIGHT_FORK)
	{
		pthread_mutex_unlock(philosopher->left_fork);
		return (-1);
	}
	fork = fork_to_pick(philosopher, fork_value);
	pthread_mutex_lock(fork);
	pthread_mutex_lock(philosopher->write_lock);
	if (*(philosopher->one_dead))
	{
		if (fork_value == RIGHT_FORK)
			pthread_mutex_unlock((fork_to_pick(philosopher, RIGHT_FORK)));
		pthread_mutex_unlock((fork_to_pick(philosopher, LEFT_FORK)));
		pthread_mutex_unlock(philosopher->write_lock);
		return (-1);
	}
	pthread_mutex_unlock(philosopher->write_lock);
	print_action(philosopher, TAKE);
	return (0);
}

int	eat(t_philosopher *philosopher)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	pthread_mutex_lock(philosopher->read_lock);
	philosopher->last_eat_usec = current_time.tv_usec;
	philosopher->last_eat_sec = current_time.tv_sec;
	pthread_mutex_unlock(philosopher->read_lock);
	print_action(philosopher, EAT);
	ft_usleep(philosopher->time_to_eat, philosopher);
	pthread_mutex_lock(philosopher->read_lock);
	if (philosopher->eat_left != -1)
		philosopher->eat_left--;
	pthread_mutex_unlock(philosopher->read_lock);
	if (*(philosopher->one_dead))
	{
		pthread_mutex_unlock((fork_to_pick(philosopher, LEFT_FORK)));
		pthread_mutex_unlock((fork_to_pick(philosopher, RIGHT_FORK)));
		return (-1);
	}
	return (0);
}

int	philo_sleep(t_philosopher *philosopher)
{
	print_action(philosopher, SLEEP);
	pthread_mutex_unlock(philosopher->left_fork);
	pthread_mutex_unlock(philosopher->right_fork);
	pthread_mutex_lock(philosopher->write_lock);
	if (*(philosopher->one_dead))
	{
		pthread_mutex_unlock(philosopher->write_lock);
		return (-1);
	}
	pthread_mutex_unlock(philosopher->write_lock);
	ft_usleep(philosopher->time_to_sleep, philosopher);
	return (0);
}

int	think(t_philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->write_lock);
	if (*(philosopher->one_dead))
	{
		pthread_mutex_unlock(philosopher->write_lock);
		return (-1);
	}
	pthread_mutex_unlock(philosopher->write_lock);
	print_action(philosopher, THINK);
	if (philosopher->nb_philo & 1)
		ft_usleep(philosopher->time_to_eat / 2, philosopher);
	return (0);
}
