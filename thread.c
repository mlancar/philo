/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:09:16 by malancar          #+#    #+#             */
/*   Updated: 2023/08/23 17:19:22 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_philo(t_philo *philo, unsigned long *current_time, char *str)
{
	pthread_mutex_lock(&philo->table->print);
	printf("%lu %d %s\n", *current_time, philo->index + 1, str);
	pthread_mutex_unlock(&philo->table->print);
}

void	*thread_routine(void *data)
{
	int				i;
	t_philo			*philo;
	unsigned long	current_time;

	i = 0;
	int j = 4;
	philo = (t_philo *)data;
	current_time = 0;
	if (philo[i].index % 2 == 0)
	{
		//printf("cc\n");
		usleep(philo->table->time_to_eat * 1000);
	}
	while (i < j)
	{
		pthread_mutex_lock(&philo->table->wait);
		pthread_mutex_unlock(&philo->table->wait);
		
		eating(philo, &current_time);
		sleeping(philo, &current_time);
		thinking(philo, &current_time);
		i++;
	}
	return (NULL);
}

void	init_thread(t_philo *philo, t_info *table)
{
	int	i;

	i = 0;
	philo->index = 0;
	//printf("philo->index = %d\n", philo->index);
	//printf("table nbr = %u\n", table.nbr);

	pthread_mutex_lock(&table->wait);
	
	while (i < table->nbr)
	{
		
		philo[i].index = i;
		philo[i].table = table;
		init_forks(table, &philo[i]);
		
		pthread_create(&philo[i].tid, NULL, thread_routine, &philo[i]);
		i++;
		
	}
	pthread_mutex_unlock(&table->wait);
	i = 0;
	while (i < table->nbr)
	{
		pthread_join(philo[i].tid, NULL);
		//printf("tid = %lu\n", philo[i].tid);
		i++;
	}
}
