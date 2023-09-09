/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 14:00:37 by malancar          #+#    #+#             */
/*   Updated: 2023/09/09 23:11:12 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_info	table;
	int		nbr;
	int		i;

	i = 0;
	philo = NULL;
	if (!check_args(ac, av))
		return (0);
	nbr = ft_atoi(av[1]);
	philo = malloc(sizeof(t_philo) * nbr);
	if (!philo)
		return (0);
	init_table(ac, av, &table);
	if (!init_mutex(&table))
		return (0);
	init_thread(philo, &table);
	while (i < table.nbr)
	{
		pthread_join(philo[i].tid, NULL);
		i++;
	}
	i = 0;
	pthread_mutex_destroy(&table.print);
	pthread_mutex_destroy(&table.wait);
	while (i < table.nbr)
	{
		pthread_mutex_destroy(&table.forks[i]);
		pthread_mutex_destroy(&table.last_meal[i]);
		i++;
	}
	free(philo->table->forks);
	free(philo);
	
	
	

	
}
