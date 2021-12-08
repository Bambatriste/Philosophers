/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: aedouard <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2021/12/05 15:27:29 by aedouard		  #+#	#+#			 */
/*   Updated: 2021/12/07 23:31:27 by aedouard         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "philosophers.h"

int	create_thread(t_philosopher *philosopher)
{
	if (pthread_create(&philosopher->thread, NULL,
			&philo_routine, philosopher) != 0)
	{
		return (-1);
	}
	return (0);
}

int	start_threads(t_philosopher **philosophers, int n)
{
	int			i;
	pthread_t	monitor_t;

	i = 0;
	while (i < n)
	{
		if (create_thread(philosophers[i]) != 0)
			return (-1);
		i++;
	}
	i = 0;
	pthread_create(&monitor_t, NULL, &main_routine, philosophers);
	while (i < n)
	{
		pthread_join(philosophers[i]->thread, NULL);
		i++;
	}
	pthread_join(monitor_t, NULL);
	free_philo(philosophers);
	return (0);
}
