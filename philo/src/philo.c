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
			free_before_terminating(data);
			printf("Error occurred while joining threads.\n");
			return (1);
		}
		i++;
	}
}

void	*start_routine(void *data)
{
	(t_simulation *) data;
	return (NULL);
}

int	init_mutexes(t_simulation *data)
{
	if (pthread_mutex_init(data->print_lock, NULL) != 0 \
	|| pthread_mutex_init(data->exit_lock, NULL) != 0)
	{
		free_before_terminating(data);
		printf("Error occurred while creating mutexes.");
		return (1);
	}
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
	while (i < data->set.num_philos)
	{
		data->thread_idx = i;
		if (pthread_create(&data->philos[i], NULL, start_routine, (void *) data) != 0)
		{
			free_before_terminating(data);
			printf("Error occurred while creating threads.\n");
			return (1);
		}
		i++;
	}
	return (0);
}



		// t_philo	info;

		// info.philo_id = thread_idx + 1;
		// info.mealtime_cnt = 0;
		// info.right_fork = &data->forks[thread_idx];
		// info.left_fork = &data->forks[thread_idx + 1];
		// info.being = ALIVE;
		// info.act = THINKING;
		// info.data = data;
		// info.set = set;



int	personification(t_simulation *data)
{
	unsigned int	i;

	i = 0;
	data->info = malloc(data->set.num_philos * sizeof(t_philo));
	if (data->forks == NULL)
	{
		printf("Malloc failed.\n");
		return (1);
	}
	while (i < data->set.num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			free_before_terminating(data);
			printf("Error occurred while creating mutexes.");
			return (1);
		}
		i++;
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
	data = calloc(1, sizeof(t_simulation));
	if (data == NULL)
	{
		printf("Malloc failed.\n");
		return (1);
	}
	if (parse_input(argc, argv, &data->set) || personification(data) \
	|| create_philos(data) || init_mutexes(data) || philos_join(data))
		return (1);
	free_before_terminating(data);
	return (0);
}
