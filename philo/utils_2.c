/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:41:21 by malancar          #+#    #+#             */
/*   Updated: 2023/09/13 16:18:38 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_forks(t_info *table, t_philo *philo)
{
	philo->left_fork = &table->forks[philo->index];
	if (philo->index == table->nbr - 1)
		philo->right_fork = &table->forks[0];
	else
		philo->right_fork = &table->forks[(philo->index) + 1];
}

void	count_meals(t_philo *philo, int *meals)
{
	pthread_mutex_lock(&philo->table->wait);
	if (philo->table->nbr_meals != -1 && *meals == philo->table->nbr_meals)
		philo->table->meals++;
	pthread_mutex_unlock(&philo->table->wait);
}

void	print_philo(t_philo *philo, char *str)
{
	unsigned long	current_time;

	current_time = 0;
	get_time(philo, &current_time);
	pthread_mutex_lock(&philo->table->print);
	printf("%lu %d %s\n", current_time, philo->index + 1, str);
	pthread_mutex_unlock(&philo->table->print);
}

void	wait_threads(t_philo *philo, t_info *table)
{
	int	i;

	i = 0;
	while (i < table->nbr)
	{
		pthread_join(philo[i].tid, NULL);
		i++;
	}	
}
