/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:39:07 by malancar          #+#    #+#             */
/*   Updated: 2023/08/17 18:31:54 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_table(char **av, t_info *table)
{
	
	table->nbr = ft_atoi(av[1]);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nbr);
	if (!table->forks)
		return ;
	
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	table->start_time = get_time_millisec();
	
	//info->nbr_time_philo_must_eat = ft_atoi(av[5]);
	//printf("must eat = %lu\n", info->nbr_time_philo_must_eat);
}

int	init_mutex(t_info *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->nbr)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			//free;
			printf("error\n");
			return (0);
		}
		i++;		
	}
	if (pthread_mutex_init(&table->print, NULL) != 0)
	{
		printf("error ici\n");
		return (0);
	}
	else if  (pthread_mutex_init(&table->wait, NULL) != 0)
	{
		printf("error la\n");
		return (0);
	}
	return (1);
}

void	init_forks(t_info *table, t_philo *philo)
{
	philo->left_fork = table->forks[philo->index];
	philo->right_fork = table->forks[(philo->index) + 1];
}