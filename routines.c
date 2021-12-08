/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: aedouard <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2021/12/05 15:28:08 by aedouard		  #+#	#+#			 */
/*   Updated: 2021/12/08 00:00:10 by aedouard         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "philosophers.h"

int	philo_starved(struct timeval time, t_philosopher *philo)
{
	int ret;

	ret =  0;
	pthread_mutex_lock(philo->write_lock);
		if (timetodie - last_time_eat > 0)
			ret = 1;
	pthread_mutex_unlock(philo->write_lock);
	return (ret);
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

	while (*philosophers)
	{
		gettimeofday(&time, NULL);
		if ((((time.tv_usec - ((*philosophers)->last_eat_usec)) / 1000))
			+ (((time.tv_sec - ((*philosophers)->last_eat_sec)) * 1000))
			- (*philosophers)->time_to_die > 0)
		{
			*(*philosophers)->one_dead = 1;
			printf("%03d %d %s\n", 
				time.tv_usec / 1000, (*philosophers)->id + 1, DIE);
			return (1);
		}
		philosophers++;
	}
	return (0);
}

void	*main_routine(void *arg)
{
	t_philosopher	**philosophers;

	philosophers = (t_philosopher **)arg;
	while (!all_ready(philosophers))
		;
	while (!all_eat(philosophers))
	{
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
	if (philosopher->id % 2)
		usleep(philosopher->time_to_eat * 1000 / 2);
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
