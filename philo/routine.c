/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:40:31 by malancar          #+#    #+#             */
/*   Updated: 2023/09/11 15:52:36 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	diner(t_philo *philo)
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
		if (check_meals_and_death(philo) == 0)
			return (NULL);
		if (diner(philo) == 0)
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
