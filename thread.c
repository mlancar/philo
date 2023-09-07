/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:09:16 by malancar          #+#    #+#             */
/*   Updated: 2023/09/07 19:47:43 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_philo(t_philo *philo, unsigned long *current_time, char *str)
{
	//pthread_mutex_lock(&philo->table->print);
	printf("%lu %d %s\n", *current_time, philo->index + 1, str);
	//pthread_mutex_unlock(&philo->table->print);
}

void	*thread_routine(void *data)
{
	t_philo			*philo;
	int				meals;
	unsigned long	last_meal;
	unsigned long	current_time;

	philo = (t_philo *)data;
	current_time = 0;
	meals = 0;
	last_meal = 0;
	if (philo[0].index % 2 == 0)
		usleep(philo->table->time_to_eat * 1000);
	pthread_mutex_lock(&philo->table->wait);
	pthread_mutex_unlock(&philo->table->wait);
	while (1)
	{
		if (check_meals_and_death(philo, last_meal, &current_time) == 1)
		{
			printf("cc %d\n", philo->index);
			return (NULL);
		}
		
		eating(philo, &current_time);
		last_meal = get_time(philo, &current_time);
		meals++;
		pthread_mutex_lock(&philo->table->wait);
		if (philo->table->nbr_meals != -1 && meals == philo->table->nbr_meals)
			philo->table->meals++;
		pthread_mutex_unlock(&philo->table->wait);
		sleeping(philo, &current_time);
		thinking(philo, &current_time);
	}
	return (NULL);
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
		init_forks(table, &philo[i]);
		pthread_create(&philo[i].tid, NULL, thread_routine, &philo[i]);
		if (philo[i].table->is_dead == 1)
			return;
		//printf("is dead = %d\n", philo[i].table->is_dead);
		i++;
	}
	pthread_mutex_unlock(&table->wait);
	i = 0;
	while (i < table->nbr)
	{
		pthread_join(philo[i].tid, NULL);
		i++;
	}
}
