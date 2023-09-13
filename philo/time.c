/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:43:23 by malancar          #+#    #+#             */
/*   Updated: 2023/09/13 16:06:32 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(t_philo *philo, unsigned long time_max)
{
	unsigned long	current_time;

	current_time = 0;
	get_time(philo, &current_time);
	time_max = current_time + time_max;
	while (current_time <= time_max)
	{
		if (check_death(philo) == 0)
			return (0);
		get_time(philo, &current_time);
		usleep(1000);
	}
	return (1);
}

void	get_time(t_philo *philo, unsigned long *current_time)
{
	pthread_mutex_lock(&philo->table->last_meal[philo->index]);
	*current_time = get_time_millisec() - philo->table->start_time;
	pthread_mutex_unlock(&philo->table->last_meal[philo->index]);
}

unsigned long	get_time_millisec(void)
{
	unsigned long	time_millisec;
	struct timeval	time;

	gettimeofday(&time, NULL);
	time_millisec = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (time_millisec);
}
