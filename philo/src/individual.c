/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   individual.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:48:06 by eunskim           #+#    #+#             */
/*   Updated: 2023/04/20 13:55:52 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleeping(t_philo *info)
{
	ms_sleep(info->set->time_to_sleep);
	philo_printer(info);
	info->act = THINKING;
}

void	philo_eating(t_philo *info)
{
	info->data->last_mealtime = current_time_in_ms();
	info->mealtime_cnt++;
	ms_sleep(info->set->time_to_eat);
	philo_printer(info);
	info->act = SLEEPING;
}

void	philo_picking_up_forks(t_philo *info)
{
	if (info->philo_id % 2 == 1)
	{
		pthread_mutex_lock(info->left_fork);
		info->act = GOT_FORKS;
		philo_printer(info);
		pthread_mutex_lock(info->right_fork);
	}
	else
	{
		pthread_mutex_lock(info->right_fork);
		info->act = GOT_FORKS;
		philo_printer(info);
		pthread_mutex_lock(info->left_fork);
	}
	info->act = EATING;
}

void	individual_simulation(t_simulation *data, t_input *set, unsigned int thread_idx)
{
	t_philo	info;

	info.philo_id = thread_idx + 1;
	info.mealtime_cnt = 0;
	info.right_fork = &data->forks[thread_idx];
	info.left_fork = &data->forks[thread_idx + 1];
	info.being = ALIVE;
	info.act = THINKING;
	info.data = data;
	info.set = set;
}
