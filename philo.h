/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 14:00:45 by malancar          #+#    #+#             */
/*   Updated: 2023/08/15 15:51:18 by malancar         ###   ########.fr       */
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
	pthread_mutex_t	print;
	pthread_mutex_t	wait;
	
}	t_info;

typedef	struct s_philo
{
	t_info			*table;
	//pthread_mutex_t	mutex;
	pthread_t		tid;
	int				index;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;
	
	
}	t_philo;


int	ft_atoi(char *str);
unsigned long get_time_millisec();
void	init_thread(t_philo *philo, t_info table);
void	init_table(char **av, t_info *table);
unsigned long get_time_millisec();
unsigned long		get_time(t_philo *philo, unsigned long *current_time);
void	print_philo(t_philo *philo, unsigned long *current_time, char *str);
void	eating(t_philo *philo, unsigned long *current_time);
void	sleeping(t_philo *philo, unsigned long *current_time);
void	thinking(t_philo *philo);
void	init_tableo(char **av, t_info *table);
int	init_mutex(t_info table);
int		check_args(int ac, char **av);
int	ft_atoi(char *str);


	
#endif