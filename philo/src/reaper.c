/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 17:52:13 by eunskim           #+#    #+#             */
/*   Updated: 2023/04/23 19:59:17 by eunskim          ###   ########.fr       */
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

void	check_if_finished(t_simulation *data)
{
	unsigned int	i;
	unsigned int	finished_cnt;

	i = 0;
	finished_cnt = 0;
	while (i < data->set.num_philos)
	{
		if (data->info[i].being == FINISHED)
			finished_cnt++;
		i++;
	}
	if (finished_cnt == data->set.num_philos)
	{
		pthread_mutex_lock(&data->print_lock);
		printf("Simulation finished\n");
		pthread_mutex_unlock(&data->print_lock);
		data->running = false;
	}
}

void	check_if_dead(t_simulation *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->set.num_philos)
	{
		if (data->info[i].death_time != 0 \
		&& data->info[i].death_time <= current_time_in_ms())
		{
			data->info[i].being = DEAD;
			philo_printer(&data->info[i]);
			data->running = false;
			break ;
		}
		i++;
	}
}

int	reaper(t_simulation *data)
{
	bool	running;

	running = true;
	data->running = &running;
	while (data->running)
	{
		check_if_dead(data);
		if (data->running == false)
			break ;
		check_if_finished(data);
	}
	if (philos_join(data))
		return (1);
	return (0);	
}
