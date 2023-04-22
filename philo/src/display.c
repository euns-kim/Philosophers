/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 20:23:04 by eunskim           #+#    #+#             */
/*   Updated: 2023/04/22 18:24:46 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_printer(t_philo *info)
{
	pthread_mutex_lock(info->data->print_lock);
	printf("%lu ", current_time_in_ms() - info->data->start_time);
	if (info->being == DEAD)
		printf("%sphilosopher #%u died%s\n", \
		RED, info->philo_id, NC);
	else if (info->being == ALIVE)
	{	
		if (info->act == THINKING)
			printf("%sphilosopher #%u is thinking%s\n", \
			GREEN, info->philo_id, NC);
		else if (info->act == GOT_FORKS)
			printf("%sphilosopher #%u has taken a fork%s\n", \
			BLACK, info->philo_id, NC);
		else if (info->act == EATING)
			printf("%sphilosopher #%u is eating\n%s", \
			CYAN, info->philo_id, NC);
		else if (info->act == SLEEPING)
			printf("%sphilosopher #%u is sleeping\n%s", \
			BLUE, info->philo_id, NC);
	}
	pthread_mutex_unlock(info->data->print_lock);
}
