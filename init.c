/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:39:07 by malancar          #+#    #+#             */
/*   Updated: 2023/09/07 18:31:43 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_table(int ac, char **av, t_info *table)
{
	table->nbr = ft_atoi(av[1]);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nbr);
	if (!table->forks)
		return ;
	table->has_eaten = 0;
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		table->nbr_meals = ft_atoi(av[5]);
		table->meals = 0;
	}
	else
		table->nbr_meals = -1;
	table->start_time = get_time_millisec();
	table->is_dead = 0;
}

int	init_mutex(t_info *table)
{
	int	i;

	i = 0;
	while (i < table->nbr)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			printf("error\n");//free
			return (0);
		}
		i++;
	}
	if (pthread_mutex_init(&table->print, NULL) != 0)
	{
		printf("error ici\n");
		return (0);
	}
	else if (pthread_mutex_init(&table->wait, NULL) != 0)
	{
		printf("error la\n");
		return (0);
	}
	return (1);
}

void	init_forks(t_info *table, t_philo *philo)
{
	philo->left_fork = &table->forks[philo->index];
	if (philo->index == table->nbr - 1)
		philo->right_fork = &table->forks[0];
	else
		philo->right_fork = &table->forks[(philo->index) + 1];
}

// void	init_table_value(t_philo *philo, int *i, int *meals, int *last_meals)
// {
// philo = (t_philo *)data;
// }