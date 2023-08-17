/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:40:31 by malancar          #+#    #+#             */
/*   Updated: 2023/08/17 18:22:10 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo, unsigned long *current_time)
{
		*current_time = get_time(philo, current_time);
		pthread_mutex_lock(&philo->left_fork);
		print_philo(philo, current_time, "has taken a fork");
		pthread_mutex_lock(&philo->right_fork);
		print_philo(philo, current_time, "has taken a fork");
		
		print_philo(philo, current_time, "is eating");
		usleep(philo->table->time_to_eat);
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);
		philo->table->nbr_time_philo_must_eat--;
}

void	sleeping(t_philo *philo, unsigned long *current_time)
{
	
	*current_time = get_time(philo, current_time);
	print_philo(philo, current_time, "is sleeping");
	usleep(philo->table->time_to_sleep);
}

// void	thinking(t_philo *philo)
// {
// 	unsigned long current_time;

// 	current_time = get_time();
// 	printf("%lu philo %d is thinking %lu\n", current_time, philo->index, philo[philo->index].info->time_to_die);
// }