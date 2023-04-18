/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:08:43 by eunskim           #+#    #+#             */
/*   Updated: 2023/04/18 22:07:35 by eunskim          ###   ########.fr       */
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

typedef struct	s_philo
{
	pthread_t		*philos;
}	t_philo;

typedef struct s_input
{
	unsigned int	num_philos;
	t_milliseconds	time_to_die;
	t_milliseconds	time_to_eat;
	t_milliseconds	time_to_sleep;
	unsigned int	num_mealtime;
}	t_input;

int				parse_input(int argc, char **argv, t_input *set);
int				init_philo(t_philo *data, t_input set);
void			*routine(void *arg);
void			free_before_terminating(t_philo *data);
void			free_p(void *ptr);
t_milliseconds	current_time_in_ms(void);

#endif