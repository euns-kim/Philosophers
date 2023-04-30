/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:48:06 by eunskim           #+#    #+#             */
/*   Updated: 2023/04/30 18:41:04 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine(t_philo *info)
{
	while (info->being == ALIVE)
	{
		pthread_mutex_lock(&info->data->exit_lock);
		if (info->data->exit == true)
		{
			if (info->action == &philo_eating)
				philo_putting_down_forks(info);
			info->being = DEAD;
			pthread_mutex_unlock(&info->data->exit_lock);
			break ;
		}
		pthread_mutex_unlock(&info->data->exit_lock);
		info->action(info);
	}
}

void	*start_routine(void *arg)
{
	t_philo	*info;

	info = (t_philo *) arg;
	pthread_mutex_lock(&info->data->start_lock);
	if (info->data->start == false)
		return (pthread_mutex_unlock(&info->data->start_lock), NULL);
	pthread_mutex_unlock(&info->data->start_lock);
	pthread_mutex_lock(&info->last_meal_lock);
	info->last_meal = info->data->start_time;
	pthread_mutex_unlock(&info->last_meal_lock);
	info->action = &philo_thinking;
	if (info->philo_id % 2 == 1)
		sleep_exact(5);
	routine(info);
	pthread_mutex_lock(&info->last_meal_lock);
	info->last_meal = 0;
	pthread_mutex_unlock(&info->last_meal_lock);
	return (NULL);
}
