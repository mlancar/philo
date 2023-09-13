/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 14:00:37 by malancar          #+#    #+#             */
/*   Updated: 2023/09/13 16:58:50 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_info	table;
	int		i;

	i = 0;
	philo = NULL;
	if (!check_args(ac, av))
		return (0);
	philo = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	if (!philo)
		return (0);
	init_table(ac, av, &table);
	if (!init_mutex(philo, &table))
	{
		free_and_destroy_mutex(philo);
		return (0);
	}
	if (table.nbr == 1)
		lonely_philo(philo, &table);
	else
		init_thread(philo, &table);
	wait_threads(philo, &table);
	free_and_destroy_mutex(philo);
}
