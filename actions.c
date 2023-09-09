/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:40:31 by malancar          #+#    #+#             */
/*   Updated: 2023/09/09 23:48:44 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	ft_usleep(t_philo *philo, unsigned long time_max)
{
	unsigned long	current_time;

	current_time = 0;
	get_time(philo, &current_time);
	time_max = current_time + time_max;
	//printf("%d : current time = %lu, last_meal = %lu, time - last_meal = %lu\n", philo->index + 1 , current_time,  philo->last_meal, current_time - philo->last_meal);
	while (current_time <= time_max)
	{
		if (check_death(philo) == 0)
			return (0);
		get_time(philo, &current_time);
		usleep(1000);
	}
	return (1);
}

int	eating(t_philo *philo)
{
	if (philo->index % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_philo(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_philo(philo, "has taken a fork");
		get_time(philo, &philo->last_meal);
		print_philo(philo, "is eating");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_philo(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_philo(philo, "has taken a fork");
		get_time(philo, &philo->last_meal);
		print_philo(philo, "is eating");
	}
	if (ft_usleep(philo, philo->table->time_to_eat) == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	if (philo->table->nbr_meals >= 0)
		philo->table->has_eaten++;
	return (1);
}

int	sleeping(t_philo *philo)
{
	print_philo(philo, "is sleeping");
	if (ft_usleep(philo, philo->table->time_to_sleep) == 0)
		return (0);
	return (1);
}

int	thinking(t_philo *philo)
{
	unsigned long	time_to_think;

	pthread_mutex_lock(&philo->table->wait);
	time_to_think = 0;
	if (philo->table->time_to_eat < philo->table->time_to_sleep)
		time_to_think = philo->table->time_to_sleep - philo->table->time_to_eat;
	else if (philo->table->time_to_eat >= philo->table->time_to_sleep)
		time_to_think = philo->table->time_to_eat - philo->table->time_to_sleep;
	pthread_mutex_unlock(&philo->table->wait);
	print_philo(philo, "is thinking");
	if (ft_usleep(philo, time_to_think) == 0)
		return (0);
	return (1);
}
