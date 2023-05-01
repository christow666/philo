/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperron <cperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 17:16:02 by cperron           #+#    #+#             */
/*   Updated: 2023/05/01 16:54:11 by cperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define PURPLE "\033[1;35m"
# define CYAN "\033[1;36m"
# define WHITE "\033[1;37m"
# define RESET "\033[0m"

typedef struct philo
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
	int	time_0;
} t_philo;

//utils
int		ft_atoi(const char *str);
int 	get_time(void);
void	print_param(t_philo *philo);
void	init_param(char **argv, t_philo *philo);

//philo_action
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
int		philo_have_forks(t_philo *philo);
void	philo_die(t_philo *philo);

#endif