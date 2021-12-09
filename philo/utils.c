/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedouard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 15:28:21 by aedouard          #+#    #+#             */
/*   Updated: 2021/12/09 19:28:32 by aedouard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_action(t_philosopher *philosopher, char *action)
{
	struct timeval	time;

	pthread_mutex_lock(philosopher->write_lock);
	if (!(*philosopher->one_dead))
	{
		gettimeofday(&time, NULL);
		printf("%08ld %d %s\n",
			(((time.tv_sec * 1000) + (time.tv_usec / 1000))
				- philosopher->start_time), philosopher->id + 1, action);
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

int	ft_atoi_error(long int *ret, char *str)
{
	int	sign;
	int	i;

	i = 0;
	sign = 1;
	*ret = 0;
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
		*ret = *ret * 10 + str[i] - '0';
		i++;
		if ((*ret > 214748364 && str[i]) || (*ret == 214748364 && str[i] > '7'))
			return (0);
	}
	return (1);
}
