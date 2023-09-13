/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lonely_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:41:16 by malancar          #+#    #+#             */
/*   Updated: 2023/09/13 17:12:28 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_must_die(void *data)
{
	t_philo			*philo;
	unsigned long	time_max;
	unsigned long	current_time;

	philo = (t_philo *)data;
	current_time = 0;
	get_time(philo, &current_time);
	time_max = philo->table->time_to_eat;
	time_max = current_time + time_max;
	pthread_mutex_lock(philo->left_fork);
	print_philo(philo, "has taken a fork");
	while (current_time <= time_max)
	{
		get_time(philo, &current_time);
		usleep(1000);
	}
	print_philo(philo, "died");
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

void	lonely_philo(t_philo *philo, t_info *table)
{
	philo[0].index = 0;
	philo[0].table = table;
	set_forks(table, &philo[0]);
	pthread_create(&philo[0].tid, NULL, philo_must_die, &philo[0]);
}
