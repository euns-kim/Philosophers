/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:48:06 by eunskim           #+#    #+#             */
/*   Updated: 2023/05/05 19:30:39 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* even numbered philos pick up the right fork first */
/* this will prevent deadlock */
/* if someone died before it picks up another */
/* it will put down the fork again */
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

/* odd numbered philos pick up the left fork first */
/* this will prevent deadlock */
/* if someone died before it picks up another */
/* it will put down the fork again */
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

/* first action: picking up the forks */
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

/* a function putting philos in a loop of actions */
/* the function pointer action calls different actions each time */
/* before any action, it checks if the simulation should stop */
/* by checking the exit variable with the exit lock */
/* if a philo has finished the meal (info->being == FINISHED), */
/* it will go out of the loop as well */
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

/* a routine function for philo threads, calling a while loop of actions */
/* it will wait for the start lock to unlock before starting any action, */
/* and update the last mealtime with the synchronized start time */
/* odd numbered philos sleep 2 milliseconds for better scheduling */
/* the last mealtime will be set to 0 before returning NULL */
/* to avoid a wrong death detection */
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
		sleep_exact(2, info);
	routine(info);
	pthread_mutex_lock(&info->last_meal_lock);
	info->last_meal = 0;
	pthread_mutex_unlock(&info->last_meal_lock);
	return (NULL);
}
