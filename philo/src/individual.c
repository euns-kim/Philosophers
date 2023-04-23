/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   individual.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:48:06 by eunskim           #+#    #+#             */
/*   Updated: 2023/04/23 17:54:33 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleeping_thinking(t_philo *info)
{
	info->act = SLEEPING;
	philo_printer(info);
	sleep_exact(info->set->time_to_sleep);
	info->act = THINKING;
	philo_printer(info);
}

void	philo_putting_down_forks(t_philo *info)
{
	if (info->philo_id % 2 == 1)
	{
		pthread_mutex_unlock(&info->left_fork);
		pthread_mutex_unlock(info->right_fork);
	}
	else
	{
		pthread_mutex_unlock(info->right_fork);
		pthread_mutex_unlock(&info->left_fork);
	}
}

void	philo_eating(t_philo *info)
{
	info->act = EATING;
	philo_printer(info);
	info->death_time = current_time_in_ms() + info->set->time_to_die;
	info->mealtime_cnt++;
	if (info->mealtime_cnt >= info->set->num_mealtime)
		info->being = FINISHED;
	sleep_exact(info->set->time_to_eat);
}

void	philo_picking_up_forks(t_philo *info)
{
	if (info->philo_id % 2 == 1)
	{
		while (pthread_mutex_lock(&info->left_fork) == 0)
		{
			if (pthread_mutex_lock(info->right_fork) != 0)
				pthread_mutex_unlock(&info->left_fork);
			else
				break;
		}
	}
	else
	{
		while (pthread_mutex_lock(info->right_fork) == 0)
		{
			if (pthread_mutex_lock(&info->left_fork) != 0)
				pthread_mutex_unlock(info->right_fork);
			else
				break;
		}
	}
	info->act = GOT_FORKS;
	philo_printer(info);
	philo_printer(info);
}

void	*start_routine(void *arg)
{
	t_philo	*info;

	info = (t_philo *) arg;
	pthread_mutex_lock(&info->data->start_lock);
	pthread_mutex_unlock(&info->data->start_lock);
	if (info->philo_id % 2 == 1)
		sleep_exact(5);
	while (info->being == ALIVE)
	{
		philo_picking_up_forks(info);
		philo_eating(info);
		philo_putting_down_forks(info);
		philo_sleeping_thinking(info);
	}
	return (NULL);
}
