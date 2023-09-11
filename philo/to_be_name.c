/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_be_name.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:41:21 by malancar          #+#    #+#             */
/*   Updated: 2023/09/11 17:51:35 by malancar         ###   ########.fr       */
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

int	ft_usleep(t_philo *philo, unsigned long time_max)
{
	unsigned long	current_time;

	current_time = 0;
	get_time(philo, &current_time);
	time_max = current_time + time_max;
	while (current_time <= time_max)
	{
		if (check_death(philo) == 0)
			return (0);
		get_time(philo, &current_time);
		usleep(1000);
	}
	return (1);
}

void	get_time(t_philo *philo, unsigned long *current_time)
{
	pthread_mutex_lock(&philo->table->last_meal[philo->index]);
	*current_time = get_time_millisec() - philo->table->start_time;
	pthread_mutex_unlock(&philo->table->last_meal[philo->index]);
}

unsigned long	get_time_millisec(void)
{
	unsigned long	time_millisec;
	struct timeval	time;

	gettimeofday(&time, NULL);
	time_millisec = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (time_millisec);
}

void	count_meals(t_philo *philo, int meals)
{
	pthread_mutex_lock(&philo->table->wait);
	if (philo->table->nbr_meals != -1 && meals == philo->table->nbr_meals)
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
