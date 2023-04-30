/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 20:23:04 by eunskim           #+#    #+#             */
/*   Updated: 2023/04/30 18:15:34 by eunskim          ###   ########.fr       */
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

void	philo_printer(t_philo *info)
{
	pthread_mutex_lock(&info->data->exit_lock);
	if (info->data->exit == true || info->set.time_to_die == 0)
	{
		pthread_mutex_unlock(&info->data->exit_lock);
		return ;
	}
	pthread_mutex_unlock(&info->data->exit_lock);
	pthread_mutex_lock(&info->data->print_lock);
	printf("%lu ", time_passed(info->data->start_time));
	if (info->being == ALIVE)
	{	
		if (info->act == THINKING)
			printf("%u is thinking\n", info->philo_id);
		else if (info->act == GOT_FORKS)
			printf("%u has taken a fork\n", info->philo_id);
		else if (info->act == EATING)
			printf("%u is eating\n", info->philo_id);
		else if (info->act == SLEEPING)
			printf("%u is sleeping\n", info->philo_id);
	}
	pthread_mutex_unlock(&info->data->print_lock);
}
