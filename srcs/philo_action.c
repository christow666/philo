/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperron <cperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:51:05 by cperron           #+#    #+#             */
/*   Updated: 2023/05/17 00:40:26 by cperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_eat(t_philo *philo)
{
	int		time;
	time = get_time();
	if (*philo->is_dead == 0)
	{
		printf("%d %d is eating\n", get_time(), philo->id);
		// printf(YELLOW"%d calcul %d\n"RESET, philo->id, time - philo->last_time_ate);
		check_death(philo);
		philo->last_time_ate = get_time();
		usleep(philo->time_to_eat * 1000);
	}
}

void	philo_sleep(t_philo *philo)
{
	if (*philo->is_dead == 0)
	{
		if (*philo->is_dead == 0)
			printf("%d %d is sleeping\n", get_time(), philo->id);
		usleep(philo->time_to_sleep * 1000);
		if (*philo->is_dead == 0)
			printf("%d %d is thinking\n", get_time(), philo->id);
	}
}

int		philo_have_forks(t_philo *philo)
{
	if ((philo->number_of_philosophers % 2) == 0)
		even_logic(philo);
	// else
	// 	odd_logic(philo);
	return (1);
}

void	philo_die(t_philo *philo, int time)
{
	(void)time;
	// pthread_mutex_lock(&philo->write_lock);
	printf(RED "%d %d has died\n"RESET, get_time(), philo->id);
	// printf("%d", (5 % 2));
	// pthread_mutex_unlock(&philo->write_lock);
}