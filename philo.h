/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 14:00:45 by malancar          #+#    #+#             */
/*   Updated: 2023/09/09 23:19:55 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_info
{
	int				nbr;
	unsigned long	time_to_die;
	unsigned long	time_to_sleep;
	unsigned long	time_to_eat;
	int				nbr_meals;
	long			has_eaten;
	unsigned long	death_time;
	int				meals;
	unsigned long	start_time;
	int				is_dead;
	pthread_mutex_t	*last_meal;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	wait;
	pthread_mutex_t	wait_meals;

}	t_info;

typedef struct s_philo
{
	t_info			*table;
	pthread_t		tid;
	int				index;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	unsigned long 	last_meal;

}	t_philo;

int				ft_atoi(char *str);
unsigned long	get_time_millisec(void);
void			init_thread(t_philo *philo, t_info *table);
unsigned long	get_time_millisec(void);
void			get_time(t_philo *philo, unsigned long *current_time);
void			print_philo(t_philo *philo, char *str);
int				eating(t_philo *philo);
int				sleeping(t_philo *philo);
int				thinking(t_philo *philo);
void			init_table(int ac, char **av, t_info *table);
int				init_mutex(t_info *table);
int				check_args(int ac, char **av);
int				ft_atoi(char *str);
void			init_forks(t_info *table, t_philo *philo);
int				check_death(t_philo *philo);
int				check_meals(t_philo *philo);
int				check_meals_and_death(t_philo *philo);
void			init_routine_value(t_philo *philo, int *meals);
void			count_meals(t_philo *philo, int meals);
void			*thread_routine(void *data);

#endif