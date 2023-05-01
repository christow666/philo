/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperron <cperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 17:35:00 by cperron           #+#    #+#             */
/*   Updated: 2023/05/01 17:10:36 by cperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int				i;
	int				a;
	int				p;

	i = 0;
	p = 1;
	a = 0;
	if (!str)
		return (0);
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\n' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			p = p * -1;
		i++;
	}
	while (ft_isdigit(str[i]) != 0)
	{
		a = a * 10 + (str[i] - 48);
		i++;
	}
	return (a * p);
}

int 	get_time(void)
{
	static struct timeval	start_time = {-1, -1};
	struct timeval			current_time;

	if (start_time.tv_sec == -1)
		gettimeofday(&start_time, 0);
	gettimeofday(&current_time, 0);
	return ((current_time.tv_sec - start_time.tv_sec) * 1000
		+ (current_time.tv_usec - start_time.tv_usec) / 1000);
}

void	print_param(t_philo *philo)
{
	printf("number_of_philosophers: %d\n", philo->number_of_philosophers);
	printf("time_to_die: %d\n", philo->time_to_die);
	printf("time_to_eat: %d\n", philo->time_to_eat);
	printf("time_to_sleep: %d\n", philo->time_to_sleep);
	printf("number_of_times_each_philosopher_must_eat: %d\n",
		philo->number_of_times_each_philosopher_must_eat);
}
