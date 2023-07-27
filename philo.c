/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 14:00:37 by malancar          #+#    #+#             */
/*   Updated: 2023/07/27 15:27:04 by malancar         ###   ########.fr       */
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

void	init_info_philo(char **av, t_info *info)
{
	info->nbr = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);

	//info->philo->nbr_fork = info->philo->nbr;
}

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_info	info;
	t_mutex var;

	
	if (!check_args(ac, av))
		return (0);
	init_info_philo(av, &info);
	philo = malloc(sizeof(t_philo) * info.nbr);
	if (!philo)
		return (0);
	//philo[i].info = info;
	pthread_mutex_init(&var.mutex, NULL);
	init_thread(&var, info);
	//printf("Main: Creation du premier thread [%ld]\n", tid1);
	
	//printf("Main: Union du premier thread [%ld]\n", tid1);
	printf("oki\n");
}
