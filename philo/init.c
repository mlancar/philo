/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:39:07 by malancar          #+#    #+#             */
/*   Updated: 2023/09/13 16:28:41 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_table(int ac, char **av, t_info *table)
{
	table->nbr = ft_atoi(av[1]);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nbr);
	if (!table->forks)
		return ;
	table->last_meal = malloc(sizeof(pthread_mutex_t) * table->nbr);
	if (!table->last_meal)
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

int	init_mutex(t_philo *philo, t_info *table)
{
	if (init_mutex_arrays(philo, table) != 1)
	{
		error_message("pthread_mutex_init failed\n");
		return (0);
	}
	if (pthread_mutex_init(&table->print, NULL) != 0)
	{
		error_message("pthread_mutex_init failed\n");
		return (0);
	}
	else if (pthread_mutex_init(&table->wait, NULL) != 0)
	{
		error_message("pthread_mutex_init failed\n");
		return (0);
	}
	else if (pthread_mutex_init(&table->wait_meals, NULL) != 0)
	{
		error_message("pthread_mutex_init failed\n");
		return (0);
	}
	return (1);
}

int	init_mutex_arrays(t_philo *philo, t_info *table)
{
	int	i;

	i = 0;
	philo->count_mutex = 0;
	while (i < table->nbr)
	{
		if ((pthread_mutex_init(&table->forks[i], NULL) != 0)
			|| (pthread_mutex_init(&table->last_meal[i], NULL) != 0))
		{
			error_message("pthread_mutex_init failed\n");
			return (0);
		}
		i++;
	}
	return (1);
}

void	init_routine_value(t_philo *philo, int *meals)
{
	pthread_mutex_lock(&philo->table->wait);
	*meals = 0;
	philo->last_meal = 0;
	pthread_mutex_unlock(&philo->table->wait);
}

void	init_thread(t_philo *philo, t_info *table)
{
	int	i;

	i = 0;
	philo->index = 0;
	pthread_mutex_lock(&table->wait);
	while (i < table->nbr)
	{
		philo[i].index = i;
		philo[i].table = table;
		set_forks(table, &philo[i]);
		pthread_create(&philo[i].tid, NULL, living, &philo[i]);
		if (philo[i].table->is_dead == 1)
			return ;
		i++;
	}
	pthread_mutex_unlock(&table->wait);
}
