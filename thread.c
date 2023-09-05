/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:09:16 by malancar          #+#    #+#             */
/*   Updated: 2023/09/05 19:36:58 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_philo(t_philo *philo, unsigned long *current_time, char *str)
{
	pthread_mutex_lock(&philo->table->print);
	printf("%lu %d %s\n", *current_time, philo->index + 1, str);
	pthread_mutex_unlock(&philo->table->print);
}


int		check_meals(t_philo *philo)
{
	int	nbr_meals;
	int meals;
	
	pthread_mutex_lock(&philo->table->wait);
	nbr_meals = philo->table->nbr_meals;
	meals = philo->table->meals;
	pthread_mutex_unlock(&philo->table->wait);
	if (nbr_meals != -1 && meals == philo->table->nbr)
		return (1);
	return (0);
}

void	*thread_routine(void *data)
{
	int				i;
	t_philo			*philo;
	int	meals;
	unsigned long	current_time;

	i = 0;
	philo = (t_philo *)data;
	current_time = 0;
	
	meals = 0;
	philo->table->death_time = current_time;
	if (philo[i].index % 2 == 0)
	{
		//printf("cc\n");
		usleep(philo->table->time_to_eat * 1000);
	}
	pthread_mutex_lock(&philo->table->wait);
	pthread_mutex_unlock(&philo->table->wait);
	while (1)
	{
		if (check_meals(philo) == 1)
			return (NULL);
		eating(philo, &current_time);
		meals++;
		pthread_mutex_lock(&philo->table->wait);
		if (philo->table->nbr_meals!= -1 && meals == philo->table->nbr_meals)
			philo->table->meals++;
		//printf("table meals = %d\n", philo->table->meals);
		pthread_mutex_unlock(&philo->table->wait);
		//philo->table->death_time = 0;
		//check_death(philo, &current_time);		
		if (check_meals(philo) == 1)
			return (NULL);
		sleeping(philo, &current_time);
		//philo->table->death_time = 0;
		if (check_meals(philo) == 1)
			return (NULL);
		if (philo->table->nbr % 2 == 1)
		{
			//check_death(philo, &current_time);
			thinking(philo, &current_time);
		}
		i++;
	}
	return (NULL);
}

void	init_thread(t_philo *philo, t_info *table)
{
	int	i;

	i = 0;
	philo->index = 0;
	//printf("philo->index = %d\n", philo->index);
	//printf("table nbr = %u\n", table.nbr);
	//printf("nbr time eat = %d\n", philo->table->nbr_time_philo_must_eat);
	//printf("philo->table->meals = %d\n", philo->table->meals);
	pthread_mutex_lock(&table->wait);
	while (i < table->nbr)
	{
		philo[i].index = i;
		philo[i].table = table;
		//printf("nbr time eat = %d\n", philo->table->nbr_time_philo_must_eat);
		
		// if (philo[i].table->nbr_meals!= -1 &&
		// 	philo[i].table->meals == philo[i].table->nbr)
		// {
		// 	printf("finish\n");
		// 	return;
		// }
		
		init_forks(table, &philo[i]);
		pthread_create(&philo[i].tid, NULL, thread_routine, &philo[i]);
		i++;
		
	}
	pthread_mutex_unlock(&table->wait);
	i = 0;
	while (i < table->nbr)
	{
		pthread_join(philo[i].tid, NULL);
		//printf("tid = %lu\n", philo[i].tid);
		i++;
	}
}
