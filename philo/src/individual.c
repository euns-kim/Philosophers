/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   individual.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:48:06 by eunskim           #+#    #+#             */
/*   Updated: 2023/04/22 18:32:00 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleeping_thinking(t_philo *info)
{
	info->act = SLEEPING;
	philo_printer(info);
	sleep_exact(info->set->time_to_sleep);
	info->act = THINKING;
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
	info->mealtime_cnt++;
	info->death_time = current_time_in_ms() + info->set->time_to_die;
	sleep_exact(info->set->time_to_eat);
}

void	philo_picking_up_forks(t_philo *info)
{
	if (info->philo_id % 2 == 1)
	{
		pthread_mutex_lock(&info->left_fork);
		info->act = GOT_FORKS;
		philo_printer(info);
		pthread_mutex_lock(info->right_fork);
	}
	else
	{
		pthread_mutex_lock(info->right_fork);
		info->act = GOT_FORKS;
		philo_printer(info);
		pthread_mutex_lock(&info->left_fork);
	}
	philo_printer(info);
}

void	*start_routine(void *arg)
{
	t_philo *info = (t_philo *) arg;

	info->data->start_time = current_time_in_ms();
	if (info->philo_id % 2 == 1)
		sleep_exact(info->set->time_to_eat / 2);
	while (info->being == ALIVE)
	{
		philo_printer(info);
		philo_picking_up_forks(info);
		philo_eating(info);
		philo_putting_down_forks(info);
		philo_sleeping_thinking(info);
	}
	return (NULL);
}
