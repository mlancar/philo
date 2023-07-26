/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:25:38 by malancar          #+#    #+#             */
/*   Updated: 2023/07/26 19:12:54 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

#define PHILO_NBR 10

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

// void	protected_print(char *str, t_mutex var)
// {
// 	printf("%s%lu Philo %d%s\n", YELLOW, )
	
// }

void	*thread_routine(void *data)
{
	 // pointeur vers la variable dans le main
	unsigned int	i;
	unsigned long	start_time;
	unsigned long current_time;
	t_mutex *var;
	
	
	i = 0;
	start_time = get_time_millisec();
	
	var = (t_mutex *)data;
	
	while (i < PHILO_NBR)
	{
		current_time = get_time_millisec();
		pthread_mutex_lock(&var->mutex);
		printf("current time = %lu start time = %lu\n", current_time, start_time);
		printf("%s%lu Philo %u : %u%s\n", YELLOW, (current_time - start_time), var->philo, i, NC);
		pthread_mutex_unlock(&var->mutex);
		usleep(100000);
		i++;
	}
	
	return (NULL); 
}

int	main(void)
{
	pthread_t	tid1;	// Identifiant du premier thread
	pthread_t	tid2;	// Identifiant du second thread
	struct timeval  time;
	t_mutex	var;
	

	var.philo1 = 0;
	var.philo2 = 1;
	var.philo_nbr = 10;

	pthread_mutex_init(&var.mutex, NULL);
	
	gettimeofday(&time, NULL);
	
	pthread_create(&tid1, NULL, thread_routine, &var);
	//printf("Main: Creation du premier thread [%ld]\n", tid1);
	
	pthread_create(&tid2, NULL, thread_routine, &var);
	//printf("Main: Creation du second thread [%ld]\n", tid2);
	// Recuperation des threads :
	pthread_join(tid1, NULL);
	//printf("Main: Union du premier thread [%ld]\n", tid1);
	pthread_join(tid2, NULL);
	//printf("Main: Union du second thread [%ld]\n", tid2);

	return (0);
}
