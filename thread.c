/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:09:16 by malancar          #+#    #+#             */
/*   Updated: 2023/08/15 15:51:05 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_philo(t_philo *philo, unsigned long *current_time, char *str)
{
	pthread_mutex_lock(&philo->table->print);
	printf("%lu %d %s\n", *current_time, philo->index, str);
	pthread_mutex_unlock(&philo->table->print);
}

void	*thread_routine(void *data)
{
	int				i;
	t_philo			*philo;
	unsigned long	current_time;

	i = 1;
	philo = (t_philo *)data;
	current_time = 0;
	while (1)
	{
		pthread_mutex_lock(&philo->table->wait);
		pthread_mutex_unlock(&philo->table->wait);
		eating(philo, &current_time);
		sleeping(philo, &current_time);
		i++;
	}
	return (NULL);
}

void	init_thread(t_philo *philo, t_info table)
{
	unsigned int	i;

	i = 1;
	philo->index = 1;
	printf("philo->index = %d\n", philo->index);
	pthread_mutex_lock(&philo->table->wait);
	while (i < table.nbr)
	{
		philo[i].table = &table;
		if (philo->index % 2 == 0)
			usleep(philo->table->time_to_eat);
		pthread_create(&philo[i].tid, NULL, thread_routine, &philo[i]);
		philo[i].index = i;
		i++;
	}
	pthread_mutex_unlock(&philo->table->wait);
	i = 1;
	while (i < table.nbr)
	{
		pthread_join(philo[i].tid, NULL);
		//printf("tid = %lu\n", philo[i].tid);
		i++;
	}
}
