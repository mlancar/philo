/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:09:16 by malancar          #+#    #+#             */
/*   Updated: 2023/07/27 15:28:49 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_routine(void *data)
{
	unsigned int	i;
	t_philo			*info;
	struct timeval  time;
	unsigned long	start_time;
	unsigned long current_time;
	
	i = 0;
	gettimeofday(&time, NULL);
	start_time = get_time_millisec();
	info = (t_philo *)data;
	
	while (i < 5)
	{
		current_time = get_time_millisec() - start_time;
		pthread_mutex_lock(&info->mutex.mutex);
		//printf("current time = %lu start time = %lu\n", current_time, start_time);
		printf("%s%lu Philo %lu is eating %s\n", YELLOW, current_time, info->tid, NC);
		printf("%s%lu Philo %lu is sleeping %s\n", RED, current_time, info->tid, NC);
		printf("%s%lu Philo %lu is thinking %s\n", GREEN, current_time, info->tid, NC);
		pthread_mutex_unlock(&info->mutex.mutex);
		usleep(100000);
		i++;
	}
	
	return (NULL); 
}

void	init_thread(t_mutex *var, t_info info, t_philo *philo)
{
	int	i;

	i = 0;
	philo->tid = pthread_self();
	var->philo1 = 0;
	var->philo2 = 1;
	var->philo_nbr = 10;
	while (i < info.nbr)
	{
		pthread_create(&philo[i].tid, NULL, thread_routine, &);
		pthread_join(philo->tid, NULL);
		i++;
	}
	
	
}
