/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperron <cperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 17:35:00 by cperron           #+#    #+#             */
/*   Updated: 2023/05/25 23:02:19 by cperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

double	ft_atoi(const char *str)
{
	int				i;
	double			a;
	int				p;

	i = 0;
	p = 1;
	a = 0;
	if (!str)
		return (0);
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\n' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			p = p * -1;
		i++;
	}
	while (ft_isdigit(str[i]) != 0)
	{
		a = a * 10 + (str[i] - 48);
		i++;
	}
	return (a * p);
}

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->is_dead == 0)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (0);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (1);
}

void	check_death(t_philo *philo)
{
	int	time;

	time = get_time();
	if (time - philo->last_time_ate >= philo->time_to_die
		&& is_dead(philo) == 0)
	{
		pthread_mutex_lock(philo->write_lock);
		pthread_mutex_lock(philo->dead_lock);
		if (*philo->is_dead == 0)
		{
			*philo->is_dead = 1;
		}
		else
		{
			pthread_mutex_unlock(philo->dead_lock);
			pthread_mutex_unlock(philo->write_lock);
			return ;
		}
		printf(RED "%d %d has died\n"RESET, get_time(), philo->id);
		pthread_mutex_unlock(philo->dead_lock);
		pthread_mutex_unlock(philo->write_lock);
	}
}
