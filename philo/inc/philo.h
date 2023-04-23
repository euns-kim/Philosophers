/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:08:43 by eunskim           #+#    #+#             */
/*   Updated: 2023/04/23 15:38:34 by eunskim          ###   ########.fr       */
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
	THINKING,
	GOT_FORKS,
	EATING,
	SLEEPING
}	t_routine;

typedef enum	e_state
{
	ALIVE,
	DEAD,
	FINISHED
}	t_state;

typedef struct s_input
{
	unsigned int	num_philos;
	t_milliseconds	time_to_die;
	t_milliseconds	time_to_eat;
	t_milliseconds	time_to_sleep;
	unsigned int	num_mealtime;
}	t_input;

typedef struct s_simulation	t_simulation;

typedef struct	s_philo
{
	unsigned int	philo_id;
	unsigned int	mealtime_cnt;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	left_fork;
	t_milliseconds	death_time;
	t_state			being;
	t_routine		act;
	t_simulation	*data;
	t_input			*set;
}	t_philo;

typedef struct	s_simulation
{
	pthread_t		*philos;
	t_philo			*info;
	t_milliseconds	start_time;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	start_lock;
	pthread_mutex_t	exit_lock;
	t_input			set;
}	t_simulation;

int				parse_input(int argc, char **argv, t_input *set);

int				personification(t_simulation *data);
int				create_philos(t_simulation *data);
int				init_mutexes(t_simulation *data);

void			*start_routine(void *info);
void			philo_picking_up_forks(t_philo *info);
void			philo_eating(t_philo *info);
void			philo_putting_down_forks(t_philo *info);
void			philo_sleeping_thinking(t_philo *info);

void			philo_printer(t_philo *info);

t_milliseconds	current_time_in_ms(void);
t_milliseconds	time_passed(t_milliseconds start_time);
void			sleep_exact(t_milliseconds timeval);

void			free_p(void *ptr);
void			destroy_mutex(pthread_mutex_t *mtx);
void			free_before_terminating(t_simulation *data);

int				philos_join(t_simulation *data);

void			*ft_memset(void *b, int c, size_t len);
void			*ft_calloc(size_t count, size_t size);

#endif