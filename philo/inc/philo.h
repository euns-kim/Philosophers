/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:08:43 by eunskim           #+#    #+#             */
/*   Updated: 2023/05/05 19:31:27 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

typedef unsigned long		t_milliseconds;
typedef struct s_simulation	t_simulation;
typedef struct s_philo		t_philo;

/* enum representing philo's state of being */
typedef enum e_state
{
	ALIVE,
	DEAD,
	FINISHED
}	t_state;

/* t_input saving the set conditions of simuation given by user input */
typedef struct s_input
{
	unsigned int	num_philos;
	t_milliseconds	time_to_die;
	t_milliseconds	time_to_eat;
	t_milliseconds	time_to_sleep;
	unsigned int	num_mealtime;
}	t_input;

/* t_philo saving private info of each philo */
/* this includes a mutex fork and a pointer to another fork */
/* each philo has a last_meal_lock used when updating its last mealtime, */
/* and when the reaper reads their last mealtime to detect any death incident */
typedef struct s_philo
{
	unsigned int	philo_id;
	unsigned int	mealtime_cnt;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	left_fork;
	t_milliseconds	last_meal;
	pthread_mutex_t	last_meal_lock;
	t_state			being;
	void			(*action)(t_philo *);
	t_simulation	*data;
	t_input			set;
}	t_philo;

/* t_simulation saving all the needed data for the whole simulation */
/* including a pointer to philo threads, a pointer to a t_philo array */
/* and four extra mutex locks for starting, finishing and exiting */
typedef struct s_simulation
{
	pthread_t		*philos;
	t_philo			*info;
	t_milliseconds	start_time;
	pthread_mutex_t	print_lock;
	bool			start;
	pthread_mutex_t	start_lock;
	unsigned int	finish_cnt;
	pthread_mutex_t	finish_lock;
	bool			exit;
	pthread_mutex_t	exit_lock;
	t_input			set;
}	t_simulation;

/* parser */
int				parse_input(int argc, char **argv, t_input *set);
int				get_value_uint(unsigned int *num, const char *str);
int				get_value_ms(t_milliseconds *time, const char *str);

/* simulation initiator */
int				personification(t_simulation *data);
int				init_mutexes(t_simulation *data);
int				create_philos(t_simulation *data);

/* deadly routine of philos */
void			*start_routine(void *arg);
void			routine(t_philo *info);
void			philo_thinking(t_philo *info);
void			philo_picking_up_forks(t_philo *info);
void			philo_eating(t_philo *info);
void			philo_putting_down_forks(t_philo *info);
void			philo_sleeping(t_philo *info);
void			philo_thinking(t_philo *info);

/* solo simulation for one and only philo */
int				solo_simulation(t_simulation *data);
int				solo_personification(t_simulation *data);
void			*solo_routine(void *arg);

/* printer */
void			philo_printer(t_philo *info, char *act);
void			usage_printer(void);

/* time manager */
t_milliseconds	current_time_in_ms(void);
t_milliseconds	time_passed(t_milliseconds start_time);
void			sleep_exact(t_milliseconds timeval, t_philo *info);

/* free and destroy */
void			destroy_forks(t_simulation *data, unsigned int i);
void			destroy_last_meal_locks(t_simulation *data, unsigned int i);
void			destroy_mutexes(t_simulation *data);
void			free_pointers(t_simulation *data);
void			free_before_terminating(t_simulation *data);

/* reaper */
int				reaper(t_simulation *data);
void			check_if_dead(t_simulation *data, bool *running);
void			check_if_finished(t_simulation *data, bool *running);
int				philos_join(t_simulation *data);

/* utils */
void			*ft_memset(void *b, int c, size_t len);
void			*ft_calloc(size_t count, size_t size);
int				ft_isdigit(int c);
void			free_p(void *ptr);

#endif