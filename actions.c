/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:40:31 by malancar          #+#    #+#             */
/*   Updated: 2023/09/05 18:41:53 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo, unsigned long *current_time)
{
	*current_time = get_time(philo, current_time);
	if (philo->index % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		*current_time = get_time(philo, current_time);
		print_philo(philo, current_time, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		*current_time = get_time(philo, current_time);
		print_philo(philo, current_time, "has taken a fork");
		*current_time = get_time(philo, current_time);
		print_philo(philo, current_time, "is eating");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		*current_time = get_time(philo, current_time);
		print_philo(philo, current_time, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		*current_time = get_time(philo, current_time);
		print_philo(philo, current_time, "has taken a fork");
		*current_time = get_time(philo, current_time);
		print_philo(philo, current_time, "is eating");
	}
	usleep(philo->table->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	if (philo->table->nbr_meals >= 0)
		philo->table->has_eaten++;
	
}

void	sleeping(t_philo *philo, unsigned long *current_time)
{
	
	*current_time = get_time(philo, current_time);
	print_philo(philo, current_time, "is sleeping");
	usleep(philo->table->time_to_sleep * 1000);
}

void	thinking(t_philo *philo, unsigned long *current_time)
{
	*current_time = get_time(philo, current_time);
	print_philo(philo, current_time, "is thinking");
	usleep(philo->table->time_to_eat * 1000);
}

