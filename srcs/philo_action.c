/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperron <cperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:51:05 by cperron           #+#    #+#             */
/*   Updated: 2023/05/01 16:51:35 by cperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_eat(t_philo *philo)
{
	printf("%d %d is eating\n", get_time(), philo->number_of_philosophers);
	usleep(philo->time_to_eat);
}

void	philo_sleep(t_philo *philo)
{
	printf("%d %d is sleeping\n", get_time(), philo->number_of_philosophers);
	usleep(philo->time_to_sleep);
}

int		philo_have_forks(t_philo *philo)
{
	printf("%d %d has taken a fork\n", get_time(), philo->number_of_philosophers);
	printf("%d %d has taken a fork\n", get_time(), philo->number_of_philosophers);
	return (1);
}

void	philo_die(t_philo *philo)
{
	printf("%d %d died\n", get_time(), philo->number_of_philosophers);
	exit(1);
}