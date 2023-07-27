/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 14:00:45 by malancar          #+#    #+#             */
/*   Updated: 2023/07/27 15:27:39 by malancar         ###   ########.fr       */
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

typedef struct s_mutex
{
	pthread_mutex_t    mutex;
	unsigned int	philo;
	unsigned int	philo1;
	unsigned int	philo2;
	unsigned int	philo_nbr;
	
}	t_mutex;

typedef	struct s_info
{
	int	nbr;
	int	time_to_die;
	int	time_to_sleep;
	int	time_to_eat;
	
}	t_info;

typedef	struct s_philo
{
	t_info			info;
	unsigned long	tid;
	t_mutex			mutex;
	
}	t_philo;



int	ft_atoi(char *str);
unsigned long get_time_millisec();
void	init_thread(t_mutex *var, t_info info, t_philo *philo);


#endif