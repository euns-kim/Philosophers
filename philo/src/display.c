/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 20:23:04 by eunskim           #+#    #+#             */
/*   Updated: 2023/05/04 16:07:25 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	usage_printer(void)
{
	printf("Invalid arguments. Use as follows:\n");
	printf("./philo ");
	printf("[number of philosophers] ");
	printf("[time to die (in milliseconds)] ");
	printf("[time to eat (in milliseconds)] ");
	printf("[time to sleep (in milliseconds)] ");
	printf("[number of mealtime (optional)]\n");
}

/* printer for philo action */
/* if the simulation is meant to be ended, */
/* no more action should be printed */
void	philo_printer(t_philo *info, char *act)
{
	pthread_mutex_lock(&info->data->exit_lock);
	if (info->data->exit == true || info->set.time_to_die == 0)
	{
		pthread_mutex_unlock(&info->data->exit_lock);
		return ;
	}
	pthread_mutex_unlock(&info->data->exit_lock);
	pthread_mutex_lock(&info->data->print_lock);
	printf("%lu %u %s", \
	time_passed(info->data->start_time), info->philo_id, act);
	pthread_mutex_unlock(&info->data->print_lock);
}
