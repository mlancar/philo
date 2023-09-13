/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:10:41 by malancar          #+#    #+#             */
/*   Updated: 2023/09/13 16:52:53 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	diner_time(t_philo *philo)
{
	eating(philo);
	if (ft_usleep(philo, philo->table->time_to_eat) == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(&philo->table->wait_meals);
	if (philo->table->nbr_meals >= 0)
		philo->table->has_eaten++;
	pthread_mutex_unlock(&philo->table->wait_meals);
	return (1);
}

void	eating(t_philo *philo)
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
	if (philo->table->nbr % 2)
	{
		time_to_think = (philo->table->time_to_eat * 2);
		time_to_think = time_to_think - philo->table->time_to_sleep;
	}
	else if (philo->table->time_to_eat < philo->table->time_to_sleep)
		time_to_think = philo->table->time_to_sleep - philo->table->time_to_eat;
	else if (philo->table->time_to_eat >= philo->table->time_to_sleep)
		time_to_think = philo->table->time_to_eat - philo->table->time_to_sleep;
	pthread_mutex_unlock(&philo->table->wait);
	print_philo(philo, "is thinking");
	if (ft_usleep(philo, time_to_think) == 0)
		return (0);
	return (1);
}
