/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 20:41:15 by eunskim           #+#    #+#             */
/*   Updated: 2023/04/18 16:29:34 by eunskim          ###   ########.fr       */
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

int	create_philos(t_simulation *data)
{
	unsigned int	i;

	i = 0;
	data->philos = malloc(data->set.num_philos * sizeof(pthread_t));
	if (data->philos == NULL)
	{
		printf("Malloc failed.\n");
		return (1);
	}
	pthread_mutex_lock(&data->start_lock);
	while (i < data->set.num_philos)
	{
		if (pthread_create(&data->philos[i], NULL, \
		start_routine, &data->info[i]) != 0)
		{
			printf("Error occurred while creating threads.\n");
			return (1);
		}
		i++;
	}
	pthread_mutex_unlock(&data->start_lock);
	data->start_time = current_time_in_ms(); // where?
	return (0);
}

int	personification(t_simulation *data)
{
	unsigned int	i;

	i = 0;
	data->info = ft_calloc(data->set.num_philos, sizeof(t_philo));
	if (data->info == NULL)
	{
		printf("Malloc failed.\n");
		return (1);
	}
	while (i < data->set.num_philos)
	{
		data->info[i].philo_id = i + 1;
		data->info[i].data = data;
		data->info[i].set = &data->set;
		if (i != 0)
			data->info[i].right_fork = &data->info[i - 1].left_fork;
		if (pthread_mutex_init(&data->info[i].left_fork, NULL) != 0)
		{
			printf("Error occurred while creating mutexes.");
			return (1);
		}
		i++;
	}
	data->info[0].right_fork = &data->info[i - 1].left_fork;
	return (0);
}

int	init_mutexes(t_simulation *data)
{
	if (pthread_mutex_init(&data->print_lock, NULL) != 0 \
	|| pthread_mutex_init(&data->start_lock, NULL) != 0 \
	|| pthread_mutex_init(&data->exit_lock, NULL) != 0)
	{
		printf("Error occurred while creating mutexes.");
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_simulation	*data;

	if (argc != 5 && argc != 6)
	{
		printf("Invalid arguments.");
		return (1);
	}
	data = ft_calloc(1, sizeof(t_simulation));
	if (data == NULL)
	{
		printf("Malloc failed.\n");
		return (1);
	}
	if (parse_input(argc, argv, &data->set) || init_mutexes(data) \
	|| personification(data) || create_philos(data) || philos_join(data))
	{
		free_before_terminating(data);
		return (1);
	}
	free_before_terminating(data);
	return (0);
}
