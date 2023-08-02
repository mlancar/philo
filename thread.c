/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:09:16 by malancar          #+#    #+#             */
/*   Updated: 2023/08/02 21:39:47 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_info_philo(char **av, t_info *info)
{
	info->nbr = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);  
	//info->philo->nbr_fork = info->philo->nbr;
// 	printf("philo %d nbr = %d\n", (*philo)->index, (*philo)[(*philo)->index].info.nbr);
// 	printf("philo %d time to die %d\n", (*philo)->index, (*philo)[(*philo)->index].info.time_to_die);
// 	printf("philo %d tim to eat %d\n", (*philo)->index, (*philo)[(*philo)->index].info.time_to_eat);
// 	printf("philo %d time to sleep %d\n", (*philo)->index, (*philo)[(*philo)->index].info.time_to_sleep);
}

void	*thread_routine(void *data)
{
	int	i;
	t_philo			*philo;
	struct timeval  time;
	unsigned long	start_time;
	unsigned long	current_time;
	
	i = 0;
	philo = (t_philo *)data;
	//printf("cc\n");
	//printf("philo->info->nbr ici = %p\n", &philo->info->nbr);
	gettimeofday(&time, NULL);
	start_time = get_time_millisec();
	while (i < 1)
	{
		current_time = get_time_millisec() - start_time;
		//printf("current time = %lu start time = %lu\n", current_time, start_time);
		//printf("%s%lu Philo %lu is eating %s\n", YELLOW, current_time, info->tid, NC);
		//printf("%s%lu Philo %lu is sleeping %s\n", RED, current_time, info->tid, NC);	
		pthread_mutex_lock(&philo->mutex.mutex);
		printf("philo %d time to die %d\n", philo->index, philo[philo->index].info->time_to_die);
		pthread_mutex_unlock(&philo->mutex.mutex);
		pthread_mutex_lock(&philo->mutex.mutex);
		printf("philo %d tim to eat %d\n", philo->index, philo[philo->index].info->time_to_eat);
		pthread_mutex_unlock(&philo->mutex.mutex);
		pthread_mutex_lock(&philo->mutex.mutex);
		printf("philo %d time to sleep %d\n", philo->index, philo[philo->index].info->time_to_sleep);
		pthread_mutex_unlock(&philo->mutex.mutex);
		i++;
	}
	
	return (NULL);
}

void	init_thread(t_philo *philo, t_info info)
{
	int	i;

	i = 0;
	philo->index = 0;
	while (i < info.nbr)
	{
		philo[i].info = &info;
		//printf("philo->info->nbr la = %p\n", &philo->info->nbr);
		pthread_create(&philo[i].tid, NULL, thread_routine, &philo[i]);
		//printf("index = %d\n", philo->index);
		philo->index = i;
		i++;
	}
	i = 0;
	while (i < info.nbr)
	{
		pthread_join(philo->tid, NULL);
		//printf("cc join\n");
		i++;
	}
	
}
