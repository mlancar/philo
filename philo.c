/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 14:00:37 by malancar          #+#    #+#             */
/*   Updated: 2023/08/02 21:50:44 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long get_time_millisec()
{
	unsigned long	time_millisec;
	struct timeval	time;
	
	gettimeofday(&time, NULL);
	time_millisec = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	//printf("time = %lu\n", time_millisec);
	//printf("%lu secondes\n%lu micro secondes\n%lu milli secondes\n", time.tv_sec, time.tv_usec, time_millisec);
	return (time_millisec);
}

int		check_args(int ac, char **av)
{
	int	i;
	int	j;
	
	if (ac != 5)
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



int	main(int ac, char **av)
{
	t_philo	*philo;
	t_info	info;
	t_mutex var;
	int		nbr;
	
	philo = NULL;
	if (!check_args(ac, av))
		return (0);
	nbr = ft_atoi(av[1]);
	//philo->info.nbr = ft_atoi(av[1]);
	//init_info_philo(av, &info);
	philo = malloc(sizeof(t_philo) * nbr);
	if (!philo)
		return (0);
	
	//philo[philo->index] 
	//init_info_philo(av,  &philo[philo->index]);
	init_info_philo(av, &info);
	//philo[i].info = info;
	pthread_mutex_init(&var.mutex_print, NULL);
	init_thread(philo, info);
	//printf("Main: Creation du premier thread [%ld]\n", tid1);
	
	//printf("Main: Union du premier thread [%ld]\n", tid1);
	printf("oki\n");
}
