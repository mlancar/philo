/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 14:00:45 by malancar          #+#    #+#             */
/*   Updated: 2023/07/25 17:44:11 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>

# define NC	"\e[0m"
# define YELLOW	"\e[1;33m"

typedef	struct s_info
{
	int	nbr;
	int	time_to_die;
	int	time_to_sleep;
	int	time_to_eat;
	
}	t_info;

typedef	struct s_philo
{
	t_info	*philo;
	
	
}	t_philo;



int	ft_atoi(char *str);

#endif