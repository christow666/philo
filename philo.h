/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperron <cperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 17:16:02 by cperron           #+#    #+#             */
/*   Updated: 2023/05/24 02:08:52 by cperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define PURPLE "\033[1;35m"
# define CYAN "\033[1;36m"
# define WHITE "\033[1;37m"
# define RESET "\033[0m"

typedef struct mutex
{
	int				is_dead;
	int				nb_eat;
	pthread_mutex_t	fork[200];
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
}	t_mutex;

typedef struct philo
{
	int					number_of_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_times_each_philosopher_must_eat;
	int					id;
	int					last_time_ate;
	int					*is_dead;
	int					nb_eat;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*write_lock;
	pthread_mutex_t		*dead_lock;
}	t_philo;

//utils_1
int		ft_isdigit(int c);
double		ft_atoi(const char *str);
void	check_death(t_philo *philo);
int		is_dead(t_philo *philo);

//utils_2
int		get_time(void);
int		check_argv(char *str);
int		sign_nazi(char *str);

//philo_action
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
int		philo_have_forks(t_philo *philo);
void	fork_logic(t_philo *philo);

//init_param
void	init_philo(char **argv, t_philo *philo, t_mutex *mutex, int *is_dead);
void	init_mutex(char **argv, t_philo *philo, t_mutex *mutex);

#endif