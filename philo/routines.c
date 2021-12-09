/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: aedouard <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2021/12/05 15:28:08 by aedouard		  #+#	#+#			 */
/*   Updated: 2021/12/09 16:19:08 by aedouard         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "philosophers.h"

int	philo_starved(struct timeval time, t_philosopher *philo)
{
	long int	last_eat_sec;
	long int	last_eat_usec;

	pthread_mutex_lock(philo->read_lock);
	last_eat_sec = philo->last_eat_sec;
	last_eat_usec = philo->last_eat_usec;
	pthread_mutex_unlock(philo->read_lock);
	pthread_mutex_lock(philo->write_lock);
	if ((((time.tv_usec - (last_eat_usec)) / 1000))
		+ (((time.tv_sec - (last_eat_sec)) * 1000))
		- philo->time_to_die > 0)
	{
		(*philo->one_dead) = 1;
		printf("%08ld %d %s\n", ((time.tv_sec * 1000)
				+ (time.tv_usec / 1000))
			- philo->start_time, philo->id + 1, DIE);
		pthread_mutex_unlock(philo->write_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->write_lock);
	return (0);
}

void	free_philo(t_philosopher **philosophers)
{
	t_philosopher	**index;

	index = philosophers;
	while (*philosophers)
	{
		free(*philosophers);
		philosophers++;
	}
	free(index);
}

int	check_philo_death(t_philosopher **philosophers)
{
	struct timeval	time;

	--philosophers;
	while (*(++philosophers))
	{
		gettimeofday(&time, NULL);
		if (philo_starved(time, *philosophers))
		{
			return (1);
		}
	}
	return (0);
}

void	*main_routine(void *arg)
{
	t_philosopher	**philosophers;

	philosophers = (t_philosopher **)arg;
	while (!all_eat(philosophers))
	{
		usleep(10);
		if (check_philo_death(philosophers))
			break ;
	}
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)arg;
	philosopher->ready = 1;
	if (!(philosopher->nb_philo & 1))
	{
		if (!(philosopher->id & 1))
			usleep(philosopher->time_to_eat >> 1);
	}
	while (can_continue(philosopher))
	{
		if (take_fork(philosopher, LEFT_FORK) == -1)
			break ;
		if (take_fork(philosopher, RIGHT_FORK) == -1)
			break ;
		if (eat(philosopher) == -1)
			break ;
		if (philo_sleep(philosopher) == -1)
			break ;
		if (think(philosopher) == -1)
			break ;
	}
	return (NULL);
}
