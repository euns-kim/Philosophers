/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 17:52:13 by eunskim           #+#    #+#             */
/*   Updated: 2023/05/05 19:31:49 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* a function which waits for the termination of all philo threads */
int	philos_join(t_simulation *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->set.num_philos)
	{
		if (pthread_join(data->philos[i], NULL) != 0)
		{
			printf("Error occurred while joining threads.\n");
			return (1);
		}
		i++;
	}
	return (0);
}

/* a function to terminate the reaper when all philos have finished the meal */
void	check_if_finished(t_simulation *data, bool *running)
{
	pthread_mutex_lock(&data->finish_lock);
	if (data->finish_cnt == data->set.num_philos)
		*running = false;
	pthread_mutex_unlock(&data->finish_lock);
}

/* a function which goes through the philo threads in a while loop, */
/* checks if someone is meant to be dead, means, */
/* the time passed since the last mealtime is equal, or exceeds time to die */
/* when a death case is detected it sets the exit variable to true, */
/* so that philos can know that the simulation should stop */
/* it will also prints out the death message after waiting for 2 ms, */
/* break out of the while loop and terminate the reaper */
void	check_if_dead(t_simulation *data, bool *running)
{
	unsigned int	i;

	i = 0;
	while (i < data->set.num_philos)
	{
		pthread_mutex_lock(&data->info[i].last_meal_lock);
		if (data->info[i].last_meal != 0 \
		&& (current_time_in_ms() - data->info[i].last_meal \
		>= data->set.time_to_die))
		{
			pthread_mutex_unlock(&data->info[i].last_meal_lock);
			pthread_mutex_lock(&data->exit_lock);
			data->exit = true;
			pthread_mutex_unlock(&data->exit_lock);
			sleep_exact(2, &data->info[i]);
			pthread_mutex_lock(&data->print_lock);
			printf("%lu %u died\n", \
			time_passed(data->start_time), data->info->philo_id);
			pthread_mutex_unlock(&data->print_lock);
			*running = false;
			break ;
		}
		pthread_mutex_unlock(&data->info[i].last_meal_lock);
		i++;
	}
}

/* a function which monitors philo threads to check */
/* if the simulation should stop (a philo died or the meal has been finished) */
int	reaper(t_simulation *data)
{
	bool	running;

	running = true;
	while (running)
	{
		check_if_dead(data, &running);
		if (running == false)
			break ;
		check_if_finished(data, &running);
	}
	return (0);
}
