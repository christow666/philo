/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperron <cperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 17:15:18 by cperron           #+#    #+#             */
/*   Updated: 2023/05/25 20:59:16 by cperron          ###   ########.fr       */
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

void	init_param(char **argv, t_philo *philo)
{
	philo->number_of_philosophers = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->number_of_times_each_philosopher_must_eat = atoi(argv[5]);
}

void	*philo_life(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	philo->last_time_ate = get_time();
	if ((philo->id % 2 == 0) && philo->number_of_philosophers != 1)
	{
		printf("%d %d is thinking\n", get_time(), philo->id);
		usleep((philo->time_to_eat * 1000) / 2);
	}
	while (is_dead(philo) == 0)
	{
		if (philo->nb_eat == 1
			&& philo->number_of_times_each_philosopher_must_eat == 0)
			return (NULL);
		fork_logic(philo);
		if (philo->nb_eat == 1)
			philo->number_of_times_each_philosopher_must_eat--;
		if (philo->nb_eat == 1
			&& philo->number_of_times_each_philosopher_must_eat == 0)
			return (NULL);
		philo_sleep(philo);
	}
	return (NULL);
}

void	simulation(char **argv, t_philo *philo)
{
	int			i;
	t_philo		philos[200];
	pthread_t	thread[200];
	t_mutex		mutex;
	int			is_dead;

	i = 0;
	is_dead = 0;
	init_mutex(argv, philo, &mutex);
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

int	check_arg(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
		return (write(2, RED"wrong number of arg\n"RESET, 27));
	if (ft_atoi(argv[1]) > 200)
		return (write(2, RED"too much philo\n"RESET, 22));
	while (i < 6)
	{
		if (i != 1 && ft_atoi(argv[i]) > INT_MAX)
			return (write(2, RED"bad arg\n"RESET, 15));
		if (check_argv(argv[i]) == 1 || ft_atoi(argv[i]) <= 0)
			return (write(2, RED"bad arg\n"RESET, 15));
		i++;
		if (i == 5 && argc != 6)
			return (0);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	philo;

	if (check_arg(argc, argv) != 0)
		return (1);
	init_param(argv, &philo);
	simulation(argv, &philo);
	return (0);
}
