/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:48:06 by eunskim           #+#    #+#             */
/*   Updated: 2023/05/04 15:38:42 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	even_numbered_picking_up(t_philo *info)
{
	pthread_mutex_lock(info->right_fork);
	pthread_mutex_lock(&info->data->exit_lock);
	if (info->data->exit == true)
	{
		pthread_mutex_unlock(info->right_fork);
		pthread_mutex_unlock(&info->data->exit_lock);
		return (1);
	}
	pthread_mutex_unlock(&info->data->exit_lock);
	pthread_mutex_lock(&info->left_fork);
	return (0);
}

static int	odd_numbered_picking_up(t_philo *info)
{
	pthread_mutex_lock(&info->left_fork);
	pthread_mutex_lock(&info->data->exit_lock);
	if (info->data->exit == true)
	{
		pthread_mutex_unlock(&info->left_fork);
		pthread_mutex_unlock(&info->data->exit_lock);
		return (1);
	}
	pthread_mutex_unlock(&info->data->exit_lock);
	pthread_mutex_lock(info->right_fork);
	return (0);
}

void	philo_picking_up_forks(t_philo *info)
{
	if (info->philo_id % 2 == 1)
	{
		if (odd_numbered_picking_up(info))
			return ;
	}
	else
	{
		if (even_numbered_picking_up(info))
			return ;
	}
	philo_printer(info, "has taken a fork\n");
	philo_printer(info, "has taken a fork\n");
	info->action = &philo_eating;
}

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
	info->action = &philo_picking_up_forks;
	if (info->philo_id % 2 == 1)
		sleep_exact(2);
	routine(info);
	pthread_mutex_lock(&info->last_meal_lock);
	info->last_meal = 0;
	pthread_mutex_unlock(&info->last_meal_lock);
	return (NULL);
}
