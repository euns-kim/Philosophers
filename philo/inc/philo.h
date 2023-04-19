/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:08:43 by eunskim           #+#    #+#             */
/*   Updated: 2023/04/19 22:59:07 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <limits.h>

typedef unsigned long	t_milliseconds;

typedef enum	e_routine
{
	GOT_FORKS,
	THINKING,
	EATING,
	SLEEPING
}	t_routine;

typedef enum	e_state
{
	ALIVE,
	DEAD
}	t_state;

typedef struct	s_simulation
{
	pthread_t		*philos;
	pthread_mutex_t	*forks;
	t_milliseconds	start_time;
	t_milliseconds	*last_mealtime;
	pthread_mutex_t	*printer_mutex;
}	t_simulation;

typedef struct s_input
{
	unsigned int	num_philos;
	t_milliseconds	time_to_die;
	t_milliseconds	time_to_eat;
	t_milliseconds	time_to_sleep;
	unsigned int	num_mealtime;
}	t_input;

typedef struct	s_philo
{
	unsigned int	philo_id;
	unsigned int	mealtime_cnt;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	t_state			being;
	t_routine		act;
	t_simulation	*data;
	t_input			*set;
}	t_philo;

int				create_philos(t_simulation *data, t_input set);
void			*routine(void *arg);
int				offer_forks(t_simulation *data, t_input set);

void			philo_printer(t_philo *info);

t_milliseconds	current_time_in_ms(void);
t_milliseconds	time_passed(t_simulation data);
void			ms_sleep(t_milliseconds timeval);

void			free_p(void *ptr);
void			free_before_terminating(t_simulation *data);

#endif