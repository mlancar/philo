/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:09:16 by malancar          #+#    #+#             */
/*   Updated: 2023/08/10 19:19:58 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long		get_time(unsigned long *current_time)
{
	struct timeval  time;
	unsigned long	start_time;
	
	gettimeofday(&time, NULL);
	start_time = get_time_millisec();
	*current_time = get_time_millisec() - start_time;
	printf("current time = %lu\n", *current_time);
	return (*current_time);
}

void	eating(t_philo *philo, unsigned long *current_time)
{
	while (1)
	{
		//printf("cc la\n");
		*current_time = get_time(current_time);
		printf("current time = %lu\n", *current_time);
		if (*current_time == philo->info->time_to_eat)
			break ;
		pthread_mutex_lock(&philo->info->forks[philo->index]);
		pthread_mutex_lock(&philo->info->forks[(philo->index) + 1]);
		//printf("%lu philo %d is eating\n", *current_time, philo->index);
		pthread_mutex_unlock(&philo->info->forks[philo->index]);
		pthread_mutex_unlock(&philo->info->forks[(philo->index) + 1]);
	}
}

void	sleeping(t_philo *philo, unsigned long *current_time)
{
	while (1)
	{	
		*current_time = get_time(current_time);
		if (*current_time == philo->info->time_to_sleep)
			break ;
		printf("%lu philo %d is sleeping\n", *current_time, philo->index);
	}
}

// void	thinking(t_philo *philo)
// {
// 	unsigned long current_time;

// 	current_time = get_time();
// 	printf("%lu philo %d is thinking %lu\n", current_time, philo->index, philo[philo->index].info->time_to_die);
// }

void	init_info_philo(char **av, t_info *info)
{
	info->nbr = ft_atoi(av[1]);
	info->forks = malloc(sizeof(pthread_mutex_t) * info->nbr);
	if (!info->forks)
		return ;
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	//info->nbr_time_philo_must_eat = ft_atoi(av[5]);
}



void	*thread_routine(void *data)
{
	int				i;
	t_philo			*philo;
	unsigned long	current_time;

	i = 0;
	philo = (t_philo *)data;
	current_time = 0;
	while (1)
	{
		printf("cc\n");
		if (i == 0)
		{
			if (philo->index % 2 == 0)
				eating(philo, &current_time);
		}
		else if (i > 0)
		{
			//printf("cc ici\n");
			eating(philo, &current_time);
			sleeping(philo, &current_time);
		}
			// if (philo[philo->index]->info->forks[philo->index] == 1 || philo[philo->index]->info->forks[philo->index + 1] == 1)
			// {
			// 	thinking(philo);
			// }
		
		i++;	
		}
		
	return (NULL);
}

void	init_thread(t_philo *philo, t_info info)
{
	unsigned int	i;

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
		pthread_join(philo[i].tid, NULL);
		//printf("tid = %lu\n", philo[i].tid);
		i++;
	}
	
}
