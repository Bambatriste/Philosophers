/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedouard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 15:27:18 by aedouard          #+#    #+#             */
/*   Updated: 2021/12/07 23:28:48 by aedouard         ###   ########.fr       */
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
		if ((*philosophers)->eat_left != 0)
			return (0);
		philosophers++;
	}
	return (1);
}

int	can_continue(t_philosopher *philosoper)
{
	if ((*philosoper->one_dead))
		return (0);
	if (philosoper->eat_left == 0)
		return (0);
	return (1);
}
