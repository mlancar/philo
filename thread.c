/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:09:16 by malancar          #+#    #+#             */
/*   Updated: 2023/09/09 19:37:05 by malancar         ###   ########.fr       */
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
	t_philo			*philo;
	int				meals;
	unsigned long	current_time;

	philo = (t_philo *)data;
	current_time = 0;
	meals = 0;
	philo->table->last_meal = 0;
	if (philo[0].index % 2 == 0)
		usleep(philo->table->time_to_eat * 1000);
	pthread_mutex_lock(&philo->table->wait);
	pthread_mutex_unlock(&philo->table->wait);
	while (1)
	{
		//printf("%d : time_to_die = %lu, time = %lu, last_meal = %lu, time - last_meal = %lu\n", philo->index, philo->table->time_to_die, current_time, philo->table->last_meal, current_time - philo->table->last_meal);
		if (check_meals_and_death(philo, &current_time) == 0)
			return (NULL);
		if (eating(philo, &current_time) == 0)
			return (NULL);
		//get_time(philo, &philo->table->last_meal);
		meals++;
		pthread_mutex_lock(&philo->table->wait);
		if (philo->table->nbr_meals != -1 && meals == philo->table->nbr_meals)
			philo->table->meals++;
		pthread_mutex_unlock(&philo->table->wait);
		if (check_meals_and_death(philo, &current_time) == 0)
			return (NULL);
		if (sleeping(philo, &current_time) == 0)
			return (NULL);
		if (check_meals_and_death(philo, &current_time) == 0)
			return (NULL);
		if (thinking(philo, &current_time) == 0)
			return (NULL);
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

}
