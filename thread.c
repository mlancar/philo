/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:09:16 by malancar          #+#    #+#             */
/*   Updated: 2023/09/09 23:19:32 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_philo(t_philo *philo, char *str)
{
	unsigned long	current_time;

	current_time = 0;
	get_time(philo, &current_time);
	pthread_mutex_lock(&philo->table->print);
	printf("%lu %d %s\n", current_time, philo->index + 1, str);
	pthread_mutex_unlock(&philo->table->print);
}

void	*thread_routine(void *data)
{
	t_philo			*philo;
	int				meals;

	philo = (t_philo *)data;
	init_routine_value(philo, &meals);
	if (philo[0].index % 2 == 0)
		usleep(philo->table->time_to_eat * 1000);
	pthread_mutex_lock(&philo->table->wait);
	pthread_mutex_unlock(&philo->table->wait);
	while (1)
	{
		//printf("%d : time_to_die = %lu, time = %lu, last_meal = %lu, time - last_meal = %lu\n", philo->index, philo->table->time_to_die, current_time, philo->table->last_meal, current_time - philo->table->last_meal);
		if (check_meals_and_death(philo) == 0)
			return (NULL);
		if (eating(philo) == 0)
			return (NULL);
		meals++;
		count_meals(philo, meals);
		if (check_meals_and_death(philo) == 0)
			return (NULL);
		if (sleeping(philo) == 0)
			return (NULL);
		if (check_meals_and_death(philo) == 0)
			return (NULL);
		if (thinking(philo) == 0)
			return (NULL);
	}
	return (NULL);
}

void	count_meals(t_philo *philo, int meals)
{
	pthread_mutex_lock(&philo->table->wait);
	if (philo->table->nbr_meals != -1 && meals == philo->table->nbr_meals)
		philo->table->meals++;
	pthread_mutex_unlock(&philo->table->wait);
}