/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:09:16 by malancar          #+#    #+#             */
/*   Updated: 2023/08/13 21:42:17 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long		get_time(t_philo *philo, unsigned long *current_time)
{
	//struct timeval  time;
	
	//gettimeofday(&time, NULL);
	*current_time = get_time_millisec() - philo[philo->index].info->start_time;
	//printf("current time = %lu\n", *current_time);
	return (*current_time);
}
void	print_philo(t_philo *philo, unsigned long *current_time, char *str)
{
	
	printf("%lu philo %d %s\n", *current_time, philo->index, str);
}

void	eating(t_philo *philo, unsigned long *current_time)
{
		//printf("cc la\n");
		*current_time = get_time(philo, current_time);
		//printf("current time = %lu\n", *current_time);
		//if (*current_time == philo->info->time_to_eat)
		//	break ;
		pthread_mutex_lock(&philo->info->forks[philo->index]);
		print_philo(philo, current_time, "has taken a fork");
		pthread_mutex_lock(&philo->info->forks[(philo->index) + 1]);
		print_philo(philo, current_time, "has taken a fork");
		
		print_philo(philo, current_time, "is eating");
		usleep(philo[philo->index].info->time_to_eat);
		pthread_mutex_unlock(&philo->info->forks[philo->index]);
		pthread_mutex_unlock(&philo->info->forks[(philo->index) + 1]);
		philo[philo->index].info->nbr_time_philo_must_eat--;
}

void	sleeping(t_philo *philo, unsigned long *current_time)
{
	
	*current_time = get_time(philo, current_time);
	print_philo(philo, current_time, "is sleeping");
	usleep(philo[philo->index].info->time_to_sleep);
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
	info->start_time = get_time_millisec();
	//info->nbr_time_philo_must_eat = ft_atoi(av[5]);
	//printf("must eat = %lu\n", info->nbr_time_philo_must_eat);
}



void	*thread_routine(void *data)
{
	int				i;
	int				j;
	t_philo			*philo;
	unsigned long	current_time;

	i = 0;
	j = 0;
	philo = (t_philo *)data;
	current_time = 0;
	
	while (j < 2)
	{
		//printf("cc\n");
		if (i == 0)
		{
			//printf("cc ici\n");
			if (philo->index % 2 == 0)
			{
				eating(philo, &current_time);
				//printf("cc eating\n");
			}
			else
			{
				sleeping(philo, &current_time);
				//printf("cc sleeping\n");
			}
		}
		else if (i > 0)
		{
			// while (philo[philo->index])
			// {
			// 	if (philo[philo->index].info->nbr_time_philo_must_eat == 0)
			// 	{
			// 		break;
			// 	}
			// }
			 
			//printf("cc apres\n");
			eating(philo, &current_time);
			sleeping(philo, &current_time);
			
		}
			// if (philo[philo->index]->info->forks[philo->index] == 1 || philo[philo->index]->info->forks[philo->index + 1] == 1)
			// {
			// 	thinking(philo);
			// }
		
		i++;
		j++;
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
