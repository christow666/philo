/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_param.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperron <cperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:10:20 by cperron           #+#    #+#             */
/*   Updated: 2023/05/24 01:20:12 by cperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_mutex(char **argv, t_philo *philo, t_mutex *mutex)
{
	int	i;

	i = 0;
	if (argv[5])
		mutex->nb_eat = 1;
	while (i < philo->number_of_philosophers)
	{
		pthread_mutex_init(&mutex->fork[i], NULL);
		i++;
	}
	pthread_mutex_init(&mutex->write_lock, NULL);
	pthread_mutex_init(&mutex->dead_lock, NULL);
}

void	init_philo(char **argv, t_philo *philo, t_mutex *mutex, int *is_dead)
{
	static int	i;

	philo->id = i;
	philo->number_of_philosophers = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	philo->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	if (i == 0)
	{
		philo->l_fork = &mutex->fork[philo->number_of_philosophers - 1];
		philo->r_fork = &mutex->fork[i];
	}
	else
	{
		philo->l_fork = &mutex->fork[i - 1];
		philo->r_fork = &mutex->fork[i];
	}
	philo->is_dead = is_dead;
	philo->nb_eat = mutex->nb_eat;
	philo->write_lock = &mutex->write_lock;
	philo->dead_lock = &mutex->dead_lock;
	i++;
}
