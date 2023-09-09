/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:44:56 by malancar          #+#    #+#             */
/*   Updated: 2023/09/09 23:38:51 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int ac, char **av)
{
	int	i;
	int	j;

	if (ac < 5 || ac > 6)
		return (0);
	i = 0;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' && av[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_meals(t_philo *philo)
{
	int	nbr_meals;
	int	meals;

	pthread_mutex_lock(&philo->table->wait);
	nbr_meals = philo->table->nbr_meals;
	meals = philo->table->meals;
	pthread_mutex_unlock(&philo->table->wait);
	if (nbr_meals != -1 && meals == philo->table->nbr)
		return (0);
	return (1);
}

int	check_death(t_philo *philo)
{
	unsigned long	time;
	unsigned long	last_meal;

	pthread_mutex_lock(&philo->table->wait);
	last_meal = philo->last_meal;
	time = 0;
	get_time(philo, &time);
	pthread_mutex_unlock(&philo->table->wait);
	if (time - last_meal > philo->table->time_to_die)
	{
		//printf("current_time = %lu, time = %lu\n", *current_time, time);
		//printf("%d : time_to_die = %lu, time = %lu, last_meal = %lu, time - last_meal = %lu\n", philo->index + 1 , philo->table->time_to_die, time, last_meal, time - last_meal);
		
		if (philo->table->is_dead == 1)
			return (0);
		
		pthread_mutex_lock(&philo->table->wait);
		philo->table->is_dead = 1;
		pthread_mutex_unlock(&philo->table->wait);
		print_philo(philo, "died");
		return (0);
	}
	return (1);
}

int	check_meals_and_death(t_philo *philo)
{
	if (philo->table->is_dead == 1)
		return (0);
	if (check_meals(philo) == 0
		|| check_death(philo) == 0)
	{
		return (0);
	}
	return (1);
}
