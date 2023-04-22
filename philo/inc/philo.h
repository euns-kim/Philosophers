/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:08:43 by eunskim           #+#    #+#             */
/*   Updated: 2023/04/22 16:08:51 by eunskim          ###   ########.fr       */
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

# define NC "\e[0m"
# define BLACK "\e[1;30m"
# define RED "\e[1;31m"
# define GREEN "\e[1;32m"
# define BLUE "\e[1;34m"
# define CYAN "\e[1;36m"

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

typedef struct	s_simulation
{
	pthread_t		*philos;
	t_philo			*info;
	t_milliseconds	start_time;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*exit_lock;
	t_input			set;
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

int				parse_input(int argc, char **argv, t_input *set);

int				personification(t_simulation *data);
int				create_philos(t_simulation *data);
int				init_mutexes(t_simulation *data);

void			*start_routine(void *info);

void			philo_printer(t_philo *info);

t_milliseconds	current_time_in_ms(void);
t_milliseconds	time_passed(t_milliseconds start_time);
void			sleep_exact(t_milliseconds timeval);

void			free_p(void *ptr);
void			free_before_terminating(t_simulation *data);

int				philos_join(t_simulation *data);

#endif