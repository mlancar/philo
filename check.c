/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:44:56 by malancar          #+#    #+#             */
/*   Updated: 2023/09/07 19:37:11 by malancar         ###   ########.fr       */
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
		return (1);
	return (0);
}

int	check_death(t_philo *philo, unsigned long last_meal, unsigned long *current_time)
{
	unsigned long	time;

	time = get_time(philo, current_time);
	printf("%d : time_to_die = %lu, time = %lu, last_meal = %lu, time - last_meal = %lu\n", philo->index, philo->table->time_to_die, time, last_meal, time - last_meal);
	if (time - last_meal > philo->table->time_to_die)
	{
		print_philo(philo, current_time, "died");
		philo->table->is_dead = 1;
		return (1);
	}
	return (0);
}

int	check_meals_and_death(t_philo *philo, unsigned long last_meal, unsigned long *current_time)
{
	if (check_meals(philo) == 0
		&& check_death(philo, last_meal, current_time) == 0)
	{
		return (0);
	}
	return (1);
}
