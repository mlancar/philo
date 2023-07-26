/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 14:00:37 by malancar          #+#    #+#             */
/*   Updated: 2023/07/26 18:16:57 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	init_info_philo(char **av, t_philo *info)
{
	info->philo->nbr = ft_atoi(av[1]);
	info->philo->time_to_die = ft_atoi(av[2]);
	info->philo->time_to_eat = ft_atoi(av[3]);
	info->philo->time_to_sleep = ft_atoi(av[4]);

	//info->philo->nbr_fork = info->philo->nbr;
}

int	main(int ac, char **av)
{
	int		i;
	t_philo	info;
	t_philo	*tab;

	if (!check_args(ac, av))
		return (0);
	init_info_philo(av, &info);
	tab = malloc(sizeof(t_philo) * info.philo->nbr);
	if (!tab)
		return (0);
	
	printf("oki\n");
}
