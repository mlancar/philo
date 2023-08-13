/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 14:00:45 by malancar          #+#    #+#             */
/*   Updated: 2023/08/13 19:24:43 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
#include <sys/time.h>

# define NC	"\e[0m"
# define YELLOW	"\e[1;33m"
#define BYELLOW	"\e[1;33m"
#define RED	"\e[31m"
#define GREEN	"\e[32m"

typedef	struct s_info
{
	unsigned int    nbr;
	unsigned long	time_to_die;
	unsigned long	time_to_sleep;
	unsigned long	time_to_eat;
	unsigned long	nbr_time_philo_must_eat;
	unsigned long	start_time;
	pthread_mutex_t	*forks;
	
}	t_info;

typedef	struct s_philo
{
	t_info			*info;
	//pthread_mutex_t	mutex;
	pthread_t		tid;
	int				index;
	
}	t_philo;


int	ft_atoi(char *str);
unsigned long get_time_millisec();
void	init_thread(t_philo *philo, t_info info);
void	init_info_philo(char **av, t_info *info);

#endif