/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   individual.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:48:06 by eunskim           #+#    #+#             */
/*   Updated: 2023/04/22 20:33:38 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleeping_thinking(t_philo *info)
{
	info->act = SLEEPING;
	pthread_mutex_lock(&info->data->print_lock);
	printf("%lu philosopher #%u is sleeping\n", \
	time_passed(info->data->start_time), info->philo_id);
	pthread_mutex_unlock(&info->data->print_lock);
	sleep_exact(info->set->time_to_sleep);
	info->act = THINKING;
	pthread_mutex_lock(&info->data->print_lock);
	printf("%lu philosopher #%u is thinking\n", \
	time_passed(info->data->start_time), info->philo_id);
	pthread_mutex_unlock(&info->data->print_lock);
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
	pthread_mutex_lock(&info->data->print_lock);
	printf("%lu philosopher #%u is eating\n", \
	time_passed(info->data->start_time), info->philo_id);
	pthread_mutex_unlock(&info->data->print_lock);
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
		pthread_mutex_lock(&info->data->print_lock);
		printf("%lu philosopher #%u has taken a fork\n", \
		time_passed(info->data->start_time), info->philo_id);
		pthread_mutex_unlock(&info->data->print_lock);
		pthread_mutex_lock(info->right_fork);
	}
	else
	{
		pthread_mutex_lock(info->right_fork);
		info->act = GOT_FORKS;
		pthread_mutex_lock(&info->data->print_lock);
		printf("%lu philosopher #%u has taken a fork\n", \
		time_passed(info->data->start_time), info->philo_id);
		pthread_mutex_unlock(&info->data->print_lock);
		pthread_mutex_lock(&info->left_fork);
	}
	pthread_mutex_lock(&info->data->print_lock);
	printf("%lu philosopher #%u has taken a fork\n", \
	time_passed(info->data->start_time), info->philo_id);
	pthread_mutex_unlock(&info->data->print_lock);
}

void	*start_routine(void *arg)
{
	t_philo	*info;

	info = (t_philo *) arg;
	// if (info->philo_id % 2 == 1)
	// 	sleep_exact(info->set->time_to_eat / 2);
	while (info->being == ALIVE)
	{
		philo_picking_up_forks(info);
		philo_eating(info);
		philo_putting_down_forks(info);
		philo_sleeping_thinking(info);
	}
	return (NULL);
}
