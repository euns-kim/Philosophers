/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 18:40:25 by eunskim           #+#    #+#             */
/*   Updated: 2023/05/08 17:12:51 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* fourth action: thinking */
/* philos are forced to think when needed for better scheduling */
void	philo_thinking(t_philo *info)
{
	philo_printer(info, "is thinking\n");
	pthread_mutex_lock(&info->last_meal_lock);
	sleep_exact((info->set.time_to_die - time_passed(info->last_meal)) \
	* 2 / 3, info);
	pthread_mutex_unlock(&info->last_meal_lock);
	info->action = &philo_picking_up_forks;
}

/* third action: sleeping */
void	philo_sleeping(t_philo *info)
{
	philo_printer(info, "is sleeping\n");
	sleep_exact(info->set.time_to_sleep, info);
	info->action = &philo_thinking;
}

/* hidden action: puttig down the forks */
/* unlock mutexes to destroy them decently */
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

/* second action: eating */
/* meal time will be updated using the meal lock */
/* this function counts up the mealtime of each philo */
/* and checks if it has eaten enough */
/* state of being will be changed to escape the action loop */
/* finish_cnt will be added up to communicate with the reaper */
void	philo_eating(t_philo *info)
{
	pthread_mutex_lock(&info->last_meal_lock);
	info->last_meal = current_time_in_ms();
	pthread_mutex_unlock(&info->last_meal_lock);
	philo_printer(info, "is eating\n");
	sleep_exact(info->set.time_to_eat, info);
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
