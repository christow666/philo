/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperron <cperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:51:05 by cperron           #+#    #+#             */
/*   Updated: 2023/05/25 23:18:31 by cperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	custom_sleep(t_philo *philo, int duration)
{
	int	time;

	time = get_time();
	while ((get_time() - time) * 1000 < duration)
	{
		check_death(philo);
		usleep(1000);
	}
}

void	philo_eat(t_philo *philo)
{
	int		time;

	time = get_time();
	pthread_mutex_lock(philo->write_lock);
	if (is_dead(philo) == 0)
		printf("%d %d is eating\n", time, philo->id);
	pthread_mutex_unlock(philo->write_lock);
	check_death(philo);
	philo->last_time_ate = get_time();
	custom_sleep(philo, philo->time_to_eat * 1000);
}

void	fork_logic(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(philo->write_lock);
	if (is_dead(philo) == 0)
		printf("%d %d has taken a fork\n", get_time(), philo->id);
	pthread_mutex_unlock(philo->write_lock);
	if (philo->number_of_philosophers == 1)
	{
		while (is_dead(philo) == 0)
			check_death(philo);
		return ;
	}
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(philo->write_lock);
	if (is_dead(philo) == 0)
		printf("%d %d has taken a fork\n", get_time(), philo->id);
	pthread_mutex_unlock(philo->write_lock);
	check_death(philo);
	philo_eat(philo);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->write_lock);
	if (is_dead(philo) == 0)
		printf("%d %d is sleeping\n", get_time(), philo->id);
	pthread_mutex_unlock(philo->write_lock);
	custom_sleep(philo, philo->time_to_sleep * 1000);
	pthread_mutex_lock(philo->write_lock);
	if (is_dead(philo) == 0)
		printf("%d %d is thinking\n", get_time(), philo->id);
	pthread_mutex_unlock(philo->write_lock);
	custom_sleep(philo, (philo->time_to_eat - philo->time_to_sleep) * 1000);
}
