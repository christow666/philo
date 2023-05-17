/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperron <cperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 00:33:44 by cperron           #+#    #+#             */
/*   Updated: 2023/05/17 01:08:33 by cperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// void	odd_logic(t_philo *philo)
// {
	
// }

// printf(YELLOW"%d has taken a l_fork %p\n"RESET, philo->id, philo->l_fork);
// printf(YELLOW"%d has taken a r_fork %p\n"RESET, philo->id, philo->r_fork);
// printf(YELLOW"%d has dropped fork %p\n"RESET, philo->id, philo->r_fork);
// printf(YELLOW"%d has dropped fork %p\n"RESET, philo->id, philo->l_fork);
// printf(YELLOW"philo id %d\n"RESET, philo->id);
// printf(YELLOW"%d l_fork init %p\n"RESET, philo->id, philo->r_fork);

void	even_logic_2(t_philo *philo)
{
	if (*philo->is_dead == 0)
	{
		if ((philo->id == 0 || philo->id % 2 == 0))
		{
			pthread_mutex_lock(&philo->mutex->meal_lock);
			while (philo->mutex->even_eat == 0)
				usleep(10);
		}
	}
}


void even_logic(t_philo *philo)
{
	if (*philo->is_dead == 0)
	{
		if ((philo->id == 0 || philo->id % 2 == 0))
		{
			if (philo->mutex->even_eat == 0)
			{
				philo->mutex->even_eat = 1;
				pthread_mutex_lock(&philo->mutex->meal_lock);
			}
			else if (philo->mutex->even_eat == 2)
			{
				pthread_mutex_lock(&philo->mutex->meal_lock);
				// usleep(1000);
			}
		}
		else
		{
			pthread_mutex_lock(&philo->mutex->meal_lock);
			// usleep(1000);
		}
		// usleep(4000);
		pthread_mutex_lock(philo->l_fork);
		if (*philo->is_dead == 0)
			printf("%d %d has taken a fork\n", get_time(), philo->id);
		pthread_mutex_lock(philo->r_fork);
		if (*philo->is_dead == 0)
			printf("%d %d has taken a fork\n", get_time(), philo->id);
		philo_eat(philo);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		philo->mutex->num_eat--;
	}
printf(YELLOW"%d num eat %d\n"RESET, philo->id, philo->mutex->num_eat);
printf(YELLOW"%d\n"RESET, philo->mutex->even_eat);
	pthread_mutex_lock(&philo->mutex->write_lock);
	if (philo->mutex->num_eat <= 0 && philo->mutex->even_eat == 1)
	{
		pthread_mutex_unlock(&philo->mutex->meal_lock);
		philo->mutex->even_eat = 2;
		philo->mutex->num_eat = philo->number_of_philosophers / 2;
	}
	pthread_mutex_unlock(&philo->mutex->write_lock);
	if (philo->mutex->num_eat <= 0 && philo->mutex->even_eat == 2)
	{
		pthread_mutex_unlock(&philo->mutex->meal_lock);
		philo->mutex->even_eat = 1;
		philo->mutex->num_eat = philo->number_of_philosophers / 2;
	}
}