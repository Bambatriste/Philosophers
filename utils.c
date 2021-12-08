/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedouard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 15:28:21 by aedouard          #+#    #+#             */
/*   Updated: 2021/12/08 00:07:00 by aedouard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_action(struct timeval time,
			t_philosopher *philosopher, char *action)
{
	pthread_mutex_lock(philosopher->write_lock);
	if (!(*philosopher->one_dead))
	{
		printf("%08ld %d %s\n",
			(time.tv_sec * 1000) + (time.tv_usec / 1000), philosopher->id + 1, action);
	}
	pthread_mutex_unlock(philosopher->write_lock);
}

int	ft_is_space(char c)
{
	if (c == '\f' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\v' || c == ' ')
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c < 48 || c > 57)
		return (0);
	return (1);
}

int	ft_is_only_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	i;
	int	returned_int;

	i = 0;
	returned_int = 0;
	sign = 1;
	while (ft_is_space(str[i]) && str[i])
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (ft_isdigit(str[i]) && (str[i]))
	{
		returned_int = returned_int * 10 + str[i] - '0';
		i++;
	}
	return (returned_int * sign);
}
