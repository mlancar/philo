/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:40:31 by malancar          #+#    #+#             */
/*   Updated: 2023/09/13 16:32:54 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*living(void *data)
{
	t_philo	*philo;
	int		meals;

	philo = (t_philo *)data;
	init_routine_value(philo, &meals);
	if (philo[0].index % 2 == 0)
		usleep(philo->table->time_to_eat * 1000);
	pthread_mutex_lock(&philo->table->wait);
	pthread_mutex_unlock(&philo->table->wait);
	while (1)
	{
		if (routine(philo, &meals) == 0)
			return (NULL);
	}
	return (NULL);
}

int	routine(t_philo *philo, int	*meals)
{
	if (check_meals_and_death(philo) == 0)
		return (0);
	if (diner_time(philo) == 0)
		return (0);
	*meals = *meals + 1;
	count_meals(philo, meals);
	if (check_meals_and_death(philo) == 0)
		return (0);
	if (sleeping(philo) == 0)
		return (0);
	if (check_meals_and_death(philo) == 0)
		return (0);
	if (thinking(philo) == 0)
		return (0);
	return (1);
}
