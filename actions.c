/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:40:31 by malancar          #+#    #+#             */
/*   Updated: 2023/09/09 19:17:32 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	ft_usleep(t_philo *philo, unsigned long *current_time, unsigned long time_max)
{
	unsigned long	time;

	time = 0;
	get_time(philo, &time);
	time_max = philo->table->time_to_eat;
	time_max = time + time_max;
	//printf("time = %lu, time_max = %lu, time + time_passed = %lu\n", time, time_max, time + time_max);
	while (time < time_max)
	{
		//printf("%d : time_max %lu time = %lu\n", philo->index + 1, time_max, time);
		if (check_death(philo, current_time) == 0)
		{
			//printf("%d : time_to_die = %lu, time = %lu, last_meal = %lu, time - last_meal = %lu\n", philo->index, philo->table->time_to_die, *current_time, philo->table->last_meal, *current_time - philo->table->last_meal);
			//printf("ft_usleep : %d\n", philo->index + 1);
			return (0);
		}
		get_time(philo, &time);
		usleep(1000);	
	}
	return (1);
}

int	eating(t_philo *philo, unsigned long *current_time)
{
	get_time(philo, current_time);
	get_time(philo, &philo->table->last_meal);
	if (philo->index % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		get_time(philo, current_time);
		print_philo(philo, current_time, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		get_time(philo, current_time);
		print_philo(philo, current_time, "has taken a fork");
		get_time(philo, current_time);
		print_philo(philo, current_time, "is eating");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		get_time(philo, current_time);
		print_philo(philo, current_time, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		get_time(philo, current_time);
		print_philo(philo, current_time, "has taken a fork");
		get_time(philo, current_time);
		print_philo(philo, current_time, "is eating");
	}
	//faire une boucle qui check toute les 10ms si un philo meurt//ft_usleep
	if (ft_usleep(philo, current_time, philo->table->time_to_eat) == 0)
	{
		//printf("%d\n", philo->index + 1);
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

int	sleeping(t_philo *philo, unsigned long *current_time)
{
	get_time(philo, current_time);
	print_philo(philo, current_time, "is sleeping");
	if (ft_usleep(philo, current_time, philo->table->time_to_sleep) == 0)
		return (0);
	return (1);
}

int	thinking(t_philo *philo, unsigned long *current_time)
{
	unsigned long	time_to_think;

	
	pthread_mutex_lock(&philo->table->wait);
	time_to_think = 0;
	get_time(philo, current_time);
	if (philo->table->time_to_eat < philo->table->time_to_sleep)
		time_to_think = philo->table->time_to_sleep - philo->table->time_to_eat;
	else if (philo->table->time_to_eat > philo->table->time_to_sleep)
		time_to_think = philo->table->time_to_eat - philo->table->time_to_sleep;
	else if (philo->table->time_to_eat == philo->table->time_to_sleep)
		time_to_think = philo->table->time_to_eat;
	pthread_mutex_unlock(&philo->table->wait);
	print_philo(philo, current_time, "is thinking");
	if (ft_usleep(philo, current_time, time_to_think) == 0)
		return (0);
	return (1);
}
