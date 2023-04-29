/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 21:21:39 by eunskim           #+#    #+#             */
/*   Updated: 2023/04/29 22:55:02 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*solo_routine(void *arg)
{
	t_philo	*info;

	info = (t_philo *) arg;
}

int	solo_simulation(t_simulation *data)
{
	data->info[0].philo_id = 1;
	data->info[0].data = data;
	data->info[0].set = data->set;
	if (pthread_mutex_init(&data->info[0].left_fork, NULL) != 0)
	{
		printf("Error occurred while creating mutexes.");
		return (pthread_mutex_destroy(&data->info[0].left_fork), 1);
	}
	data->philos = malloc(data->set.num_philos * sizeof(pthread_t));
	if (data->philos == NULL)
	{
		printf("Malloc failed.\n");
		// free
		return (1);
	}
	if (pthread_create(&data->philo[0], NULL, solo_routine, &data->info[0]) != 0)
	{
		printf("Error occurred while creating mutexes.");
		// free
		return (1);
	}
	
		
}