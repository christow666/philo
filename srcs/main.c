/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperron <cperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 17:15:18 by cperron           #+#    #+#             */
/*   Updated: 2023/05/01 17:10:59 by cperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*philo_life(void *ptr)
{
	t_philo	*philo;
	int	last_time_ate;
	
	philo = (t_philo *)ptr;
	while (1)
	{
		if (philo_have_forks(philo))
		{
			last_time_ate = get_time();
			if (get_time() > last_time_ate + philo->time_to_die)
			{
				philo_die(philo);
				break;
			}
			else
			{
				philo_eat(philo);
				philo_sleep(philo);
			}
		}
	}
	return(NULL);
}

void	init_pthread(t_philo *philo)
{
	pthread_t *thread;
	int	i;
	
	i = 0;
	thread = malloc(philo->number_of_philosophers * sizeof(pthread_t));
	while (i < philo->number_of_philosophers)
	{
		pthread_create(&thread[i], NULL, philo_life, philo);
		i++;
	}
	while (i >= 0)
	{
		pthread_join(thread[i], NULL);
		i--;
	}
}

void	ft_simulation(t_philo *philo)
{
	init_pthread(philo);
	
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
	// print_param(&philo);
	ft_simulation(&philo);
	return (0);
}