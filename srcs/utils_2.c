/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperron <cperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 23:48:21 by cperron           #+#    #+#             */
/*   Updated: 2023/05/24 01:40:50 by cperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	get_time(void)
{
	static struct timeval	start_time = {-1, -1};
	struct timeval			current_time;

	if (start_time.tv_sec == -1)
		gettimeofday(&start_time, 0);
	gettimeofday(&current_time, 0);
	return ((current_time.tv_sec - start_time.tv_sec) * 1000
		+ (current_time.tv_usec - start_time.tv_usec) / 1000);
}

int	check_argv(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (i == 0 && (ft_isdigit(str[i]) == 1))
			i++;
		else if (i == 0 && (str[i] != '-' || str[i] != '+'))
			i++;
		if (!str[i])
			return (0);
		else if (ft_isdigit(str[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}
