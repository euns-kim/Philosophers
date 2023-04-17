/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:08:43 by eunskim           #+#    #+#             */
/*   Updated: 2023/04/17 21:20:36 by eunskim          ###   ########.fr       */
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

typedef struct	s_philo
{
	pthread_t		*philos;
	unsigned int	*philo_ids;
	unsigned int	num_philos;
}	t_philo;

void		*routine(void *arg);
long long	current_time_in_ms(struct timeval tv);


#endif