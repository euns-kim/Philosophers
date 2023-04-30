/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 18:40:25 by eunskim           #+#    #+#             */
/*   Updated: 2023/04/30 18:41:08 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_thinking(t_philo *info)
{
	info->act = THINKING;
	philo_printer(info);
	info->action = &philo_picking_up_forks;
}

void	philo_sleeping(t_philo *info)
{
	info->act = SLEEPING;
	philo_printer(info);
	sleep_exact(info->set.time_to_sleep);
	info->action = &philo_thinking;
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
	pthread_mutex_lock(&info->last_meal_lock);
	info->last_meal = current_time_in_ms();
	pthread_mutex_unlock(&info->last_meal_lock);
	sleep_exact(info->set.time_to_eat);
	info->mealtime_cnt++;
	if (info->mealtime_cnt == info->set.num_mealtime)
	{
		info->being = FINISHED;
		pthread_mutex_lock(&info->data->finish_lock);
		info->data->finish_cnt += 1;
		pthread_mutex_unlock(&info->data->finish_lock);
	}
	philo_putting_down_forks(info);
	info->action = &philo_sleeping;
}

void	philo_picking_up_forks(t_philo *info)
{
	if (info->philo_id % 2 == 1)
	{
		pthread_mutex_lock(&info->left_fork);
		pthread_mutex_lock(info->right_fork);
	}
	else
	{
		pthread_mutex_lock(info->right_fork);
		pthread_mutex_lock(&info->left_fork);
	}
	info->act = GOT_FORKS;
	philo_printer(info);
	philo_printer(info);
	info->action = &philo_eating;
}
