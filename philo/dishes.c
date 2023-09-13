/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dishes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:14:05 by malancar          #+#    #+#             */
/*   Updated: 2023/09/13 17:22:34 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_and_destroy_mutex(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&philo->table->print);
	pthread_mutex_destroy(&philo->table->wait);
	while (i < philo->count_mutex)
	{
		pthread_mutex_destroy(&philo->table->forks[i]);
		pthread_mutex_destroy(&philo->table->last_meal[i]);
		i++;
	}
	free(philo->table->forks);
	free(philo->table->last_meal);
	free(philo);
}

void	error_message(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	write(2, str, len);
}
