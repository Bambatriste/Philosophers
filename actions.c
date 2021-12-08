/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedouard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 15:26:34 by aedouard          #+#    #+#             */
/*   Updated: 2021/12/08 13:55:22 by aedouard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

pthread_mutex_t *fork_to_pick(t_philosopher *philo, int fork_value)
{
	pthread_mutex_t *fork;

	if(fork_value == LEFT_FORK)
	{
		if (philo->id % 2)
			fork = philo->left_fork;
		else
			fork = philo->right_fork;
	}
	else
	{
		if (philo->id % 2)
			fork = philo->right_fork;
		else
			fork = philo->left_fork;
	}
	return (fork);
}

int	take_fork(t_philosopher *philosopher, int fork_value)
{
	struct timeval	current_time;
	pthread_mutex_t	*fork;

	gettimeofday(&current_time, NULL);
	if (philosopher->left_fork == philosopher->right_fork
		&& fork_value == RIGHT_FORK)
		return (-1);
	/*if (fork_value == LEFT_FORK)
		fork = philosopher->left_fork;
	else
		fork = philosopher->right_fork;*/
	fork = fork_to_pick(philosopher, fork_value);
	if (!*philosopher->one_dead)
		pthread_mutex_lock(fork);
	else
		return (-1);
	print_action(current_time, philosopher, TAKE);
	return (0);
}

int	eat(t_philosopher *philosopher)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	pthread_mutex_lock(philosopher->read_lock);
	philosopher->last_eat_usec = current_time.tv_usec;
	philosopher->last_eat_sec = current_time.tv_sec;
	if (*philosopher->one_dead)
	{
		pthread_mutex_unlock((fork_to_pick(philosopher, LEFT_FORK)));
		pthread_mutex_unlock((fork_to_pick(philosopher, RIGHT_FORK)));
		return (-1);
	}
	print_action(current_time, philosopher, EAT);
	usleep(philosopher->time_to_eat * 1000);
	if (philosopher->eat_left != -1)
		philosopher->eat_left--;
	pthread_mutex_unlock(philosopher->read_lock);
	return (0);
}

int	philo_sleep(t_philosopher *philosopher)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	pthread_mutex_unlock(philosopher->left_fork);
	pthread_mutex_unlock(philosopher->right_fork);
	if (*philosopher->one_dead)
		return (-1);
	print_action(current_time, philosopher, SLEEP);
	usleep(philosopher->time_to_sleep * 1000);
	return (0);
}

int	think(t_philosopher *philosopher)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	if (*philosopher->one_dead)
		return (-1);
	print_action(current_time, philosopher, THINK);
	return (0);
}
