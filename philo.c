/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 14:00:37 by malancar          #+#    #+#             */
/*   Updated: 2023/08/17 18:31:05 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long		get_time(t_philo *philo, unsigned long *current_time)
{
	*current_time = get_time_millisec() - philo->table->start_time;
	return (*current_time);
}

unsigned long get_time_millisec()
{
	unsigned long	time_millisec;
	struct timeval	time;
	
	gettimeofday(&time, NULL);
	time_millisec = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	//time.tv_sec, time.tv_usec, time_millisec);
	return (time_millisec);
}

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_info	table;
	int		nbr;
	
	philo = NULL;
	
	if (!check_args(ac, av))
		return (0);
	nbr = ft_atoi(av[1]);
	philo = malloc(sizeof(t_philo) * nbr);
	if (!philo)
		return (0);
	init_table(av, &table);
	if (!init_mutex(&table))
		return (0);
	init_thread(philo, &table);
	//printf("oki\n");
}
