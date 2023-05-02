/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 21:21:39 by eunskim           #+#    #+#             */
/*   Updated: 2023/05/02 20:51:40 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*solo_routine(void *arg)
{
	t_philo	*info;

	info = (t_philo *) arg;
	info->data->start_time = current_time_in_ms();
	if (info->set.time_to_die == 0)
	{
		printf("%lu 1 died\n", time_passed(info->data->start_time));
		return (NULL);
	}
	info->act = THINKING;
	philo_printer(info);
	pthread_mutex_lock(&info->left_fork);
	info->act = GOT_FORKS;
	philo_printer(info);
	pthread_mutex_unlock(&info->left_fork);
	info->being = DEAD;
	printf("%lu 1 died\n", time_passed(info->data->start_time));
	return (NULL);
}

int	solo_personification(t_simulation *data)
{
	data->info[0].philo_id = 1;
	data->info[0].data = data;
	data->info[0].set = data->set;
	if (pthread_mutex_init(&data->info[0].left_fork, NULL) != 0)
	{
		printf("Error occurred while creating mutexes.\n");
		return (1);
	}
	data->philos = ft_calloc(1, sizeof(pthread_t));
	if (data->philos == NULL)
	{
		printf("Malloc failed.\n");
		return (pthread_mutex_destroy(&data->info[0].left_fork), 1);
	}
	return (0);
}

int	solo_simulation(t_simulation *data)
{
	if (solo_personification(data))
		return (destroy_mutexes(data), free(data->info), 1);
	if (pthread_create(&data->philos[0], NULL, \
	solo_routine, &data->info[0]) != 0)
	{
		printf("Error occurred while creating threads.\n");
		return (pthread_mutex_destroy(&data->info[0].left_fork), \
		destroy_mutexes(data), free_pointers(data), 1);
	}
	if (pthread_join(data->philos[0], NULL) != 0)
	{
		printf("Error occurred while joining threads.\n");
		return (pthread_mutex_destroy(&data->info[0].left_fork), \
		destroy_mutexes(data), free_pointers(data), 1);
	}
	return (pthread_mutex_destroy(&data->info[0].left_fork), \
	destroy_mutexes(data), free_pointers(data), 0);
}
