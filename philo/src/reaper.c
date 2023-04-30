/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 17:52:13 by eunskim           #+#    #+#             */
/*   Updated: 2023/04/30 18:29:45 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	check_if_finished(t_simulation *data, bool *running)
{
	unsigned int	i;

	i = 0;
	while (i < data->set.num_philos)
	{
		pthread_mutex_lock(&data->finish_lock);
		if (data->finish_cnt == data->set.num_philos)
		{
			*running = false;
			break ;
		}	
		pthread_mutex_unlock(&data->finish_lock);
		i++;
	}
}

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
			pthread_mutex_lock(&data->exit_lock);
			data->exit = true;
			pthread_mutex_unlock(&data->exit_lock);
			pthread_mutex_lock(&data->print_lock);
			printf("%lu %u died", time_passed(data->start_time), \
			data->info[i].philo_id);
			pthread_mutex_unlock(&data->print_lock);
			*running = false;
			pthread_mutex_unlock(&data->info[i].last_meal_lock);
			break ;
		}
		pthread_mutex_unlock(&data->info[i].last_meal_lock);
		i++;
	}
}

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
