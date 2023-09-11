/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 14:00:37 by malancar          #+#    #+#             */
/*   Updated: 2023/09/11 15:52:29 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



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
	{
		//detruire mutex init;
		free_and_destroy_mutex(philo);
		return (0);
	}
	init_thread(philo, &table);
	while (i < table.nbr)
	{
		pthread_join(philo[i].tid, NULL);
		i++;
	}
	free_and_destroy_mutex(philo);
}
