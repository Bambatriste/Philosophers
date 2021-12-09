/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedouard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 15:27:18 by aedouard          #+#    #+#             */
/*   Updated: 2021/12/09 16:19:25 by aedouard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	all_ready(t_philosopher **philosophers)
{
	while (*philosophers)
	{
		if ((*philosophers)->ready == 0)
			return (0);
		philosophers++;
	}
	return (1);
}

int	all_eat(t_philosopher **philosophers)
{
	while (*philosophers)
	{
		pthread_mutex_lock((*philosophers)->read_lock);
		if ((*philosophers)->eat_left != 0)
		{
			pthread_mutex_unlock((*philosophers)->read_lock);
			return (0);
		}
		pthread_mutex_unlock((*philosophers)->read_lock);
		philosophers++;
	}
	return (1);
}

int	can_continue(t_philosopher *philosoper)
{
	pthread_mutex_lock(philosoper->write_lock);
	if ((*philosoper->one_dead))
	{
		pthread_mutex_unlock(philosoper->write_lock);
		return (0);
	}
	if (philosoper->eat_left == 0)
	{
		pthread_mutex_unlock(philosoper->write_lock);
		return (0);
	}
	pthread_mutex_unlock(philosoper->write_lock);
	return (1);
}
