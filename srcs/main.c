/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperron <cperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 17:15:18 by cperron           #+#    #+#             */
/*   Updated: 2023/05/16 23:59:38 by cperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
			// printf(YELLOW"%d l_fork %p\n"RESET, philo->id, philo->l_fork);
			// printf(YELLOW"%d r_fork %p\n"RESET, philo->id, philo->r_fork);
			// printf(YELLOW"%d is_dead %d\n"RESET, philo->id, *philo->is_dead);
			// printf(YELLOW"%d time %d\n"RESET, philo->id, time);
			// printf(YELLOW"%d last_time_ate %d\n"RESET, philo->id, philo->last_time_ate);
			// printf(YELLOW"%d time_to_die %d\n"RESET, philo->id, philo->time_to_die);
			// printf(YELLOW"%d calcul %d\n"RESET, philo->id, time - philo->last_time_ate);
			// if (time - philo->last_time_ate >= philo->time_to_die && *philo->is_dead == 0)

void	*philo_life(void *ptr)
{
	t_philo	*philo;
	
	philo = (t_philo *)ptr;
	philo->last_time_ate = get_time();
	while (1)
	{
		check_death(philo);
		if (*philo->is_dead == 1)
			return(NULL);
		philo_have_forks(philo);
		if (*philo->is_dead == 1)
			return(NULL);
		check_death(philo);
		philo_sleep(philo);
	}
	return(NULL);
}

void	simulation(char ** argv, t_philo *philo)
{
	int			i;
	t_philo		philos[200];
	pthread_t 	thread[200];
	t_mutex 	mutex;
	int			is_dead;
	
	i = 0;
	is_dead = 0;
	init_mutex(philo, &mutex);
	while (i < philo->number_of_philosophers)
	{
		init_philo(argv, &philos[i], &mutex, &is_dead);
		i++;
	}
	i = 0;
	while (i < philo->number_of_philosophers)
	{
		pthread_create(&thread[i], NULL, philo_life, &philos[i]);
		i++;
	}
	while (i >= 0)
	{
		pthread_join(thread[i], NULL);
		i--;
	}
}

int	main(int argc, char **argv)
{
	t_philo philo;
	
	if (argc < 4 || argc > 6)
	{
		write(2, RED"wrong number of arg\n"RESET, 27);
		return (1);
	}
	init_param(argv, &philo);
	simulation(argv, &philo);
	return (0);
}


// int		philo_have_forks(t_philo *philo)
// {
// 	if (*philo->is_dead == 0)
// 	{
// 		pthread_mutex_lock(&philo->write_lock);
// 		if (pthread_mutex_lock(philo->l_fork) == 0)
// 			pthread_mutex_lock(philo->r_fork);
// 		printf("%d %d has taken a fork\n", get_time(), philo->id);
// 		// printf(YELLOW"%d l_fork init %p\n"RESET, philo->id, philo->l_fork);
// 		printf("%d %d has taken a fork\n", get_time(), philo->id);
// 		// printf(YELLOW"%d l_fork init %p\n"RESET, philo->id, philo->r_fork);
// 		pthread_mutex_unlock(&philo->write_lock);
// 		philo_eat(philo);
// 		pthread_mutex_unlock(philo->r_fork);
// 		// printf(YELLOW"%d has dropped fork %p\n"RESET, philo->id, philo->r_fork);
// 		pthread_mutex_unlock(philo->l_fork);
// 		// printf(YELLOW"%d has dropped fork %p\n"RESET, philo->id, philo->l_fork);
// 	}
// 	return (1);
// }