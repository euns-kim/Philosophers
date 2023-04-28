/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 17:52:13 by eunskim           #+#    #+#             */
/*   Updated: 2023/04/28 20:51:21 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philos_join(t_simulation *data)
{
	unsigned int	i;
	unsigned int	finish_cnt;

	i = 0;
	finish_cnt = 0;
	while (i < data->set.num_philos)
	{
		if (pthread_join(data->philos[i], NULL) != 0)
		{
			printf("Error occurred while joining threads.\n");
			return (1);
		}
		if (data->info[i].being == FINISHED)
			finish_cnt += 1;
		i++;
	}
	if (finish_cnt == data->set.num_mealtime)
		data->running = false;
	return (0);
}

void	check_if_dead(t_simulation *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->set.num_philos)
	{
		pthread_mutex_lock(&data->info[i].last_meal_lock);
		if (data->info[i].last_meal != 0 \
		&& (current_time_in_ms() - data->info[i].last_meal >= data->set.time_to_die))
		{
			pthread_mutex_lock(&data->exit_lock);
			data->exit = true;
			pthread_mutex_unlock(&data->exit_lock);
			pthread_mutex_lock(&data->print_lock);
			printf("%lu %u died", time_passed(data->start_time), \
			data->info[i].philo_id);
			pthread_mutex_unlock(&data->print_lock);
			data->running = false;
			pthread_mutex_unlock(&data->info[i].last_meal_lock);
			break ;
		}
		pthread_mutex_unlock(&data->info[i].last_meal_lock);
		i++;
	}
}

int	reaper(t_simulation *data)
{
	data->running = true;
	while (data->running)
		check_if_dead(data);
	return (0);
}
