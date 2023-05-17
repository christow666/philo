/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_param.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperron <cperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:10:20 by cperron           #+#    #+#             */
/*   Updated: 2023/05/17 00:49:58 by cperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_param(char **argv, t_philo *philo)
{
	philo->number_of_philosophers = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->number_of_times_each_philosopher_must_eat = atoi(argv[5]);	
}

void	init_mutex(t_philo *philo, t_mutex *mutex)
{
	int i;
	
	i = 0;
	(void)philo;
	while(i < philo->number_of_philosophers)
	{
		pthread_mutex_init(&mutex->fork[i], NULL);
		// pthread_mutex_init(&mutex->meal_lock[i], NULL);
		// printf(YELLOW"%d fork init %p\n"RESET, philo->id, &mutex->fork[i]);
		i++;
	}
	// pthread_mutex_init(&mutex->meal_lock_e, NULL);
	// pthread_mutex_init(&mutex->meal_lock_o, NULL);
	pthread_mutex_init(&mutex->meal_lock, NULL);
	pthread_mutex_init(&mutex->write_lock, NULL);
	pthread_mutex_init(&mutex->dead_lock, NULL);
	mutex->even_eat = 0;
	mutex->num_eat = philo->number_of_philosophers / 2;
}

void	init_philo(char ** argv, t_philo *philo, t_mutex *mutex, int *is_dead)
{
	static int i;
	
	philo->id = i;
	philo->number_of_philosophers = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (i == 0)
	{
		// printf(YELLOW"%d fork init philo %p\n"RESET, philo->id, &mutex->fork[i]);
		philo->l_fork = &mutex->fork[philo->number_of_philosophers - 1];
		philo->r_fork = &mutex->fork[i];
		// printf(YELLOW"%d l_fork init %p\n"RESET, philo->id, philo->l_fork);
	}
	else
	{
		philo->l_fork = &mutex->fork[i - 1];
		philo->r_fork = &mutex->fork[i];
	}
	// if (i == 0 || i % 2 == 0)
	// 	philo->meal_lock = mutex->meal_lock_e;
	// else
	// 	philo->meal_lock = mutex->meal_lock_o;
	philo->meal_lock_e = mutex->meal_lock_e;
	philo->meal_lock_o = mutex->meal_lock_o;
	philo->is_dead = is_dead;
	// philo->odd_eat = &mutex->odd_eat;
	philo->write_lock = mutex->write_lock;
	philo->dead_lock = mutex->dead_lock;
	philo->mutex = mutex;
	// printf(YELLOW"%d\n"RESET, philo->mutex->num_eat);
	// philo->meal_lock = mutex->meal_lock[i];
	i++;
}
