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

/* a funtion to create philos as threads */
/* start lock is used to synchronize the starting time for every philo */
int	create_philos(t_simulation *data)
{
	unsigned int	i;

	i = 0;
	data->philos = malloc(data->set.num_philos * sizeof(pthread_t));
	if (data->philos == NULL)
		return (printf("Malloc failed.\n"), 1);
	pthread_mutex_lock(&data->start_lock);
	while (i < data->set.num_philos)
	{
		if (pthread_create(&data->philos[i], NULL, \
		start_routine, &data->info[i]) != 0)
		{
			printf("Error occurred while creating threads.\n");
			pthread_mutex_unlock(&data->start_lock);
			philos_join(data, i);
			return (1);
		}
		i++;
	}
	data->start = true;
	data->start_time = current_time_in_ms();
	pthread_mutex_unlock(&data->start_lock);
	return (0);
}

/* a function which saves all non-zero informaion including the forks */
/* in each struct for each philo */
int	personification(t_simulation *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->set.num_philos)
	{
		data->info[i].philo_id = i + 1;
		data->info[i].data = data;
		data->info[i].set = data->set;
		if (i != 0)
			data->info[i].right_fork = &data->info[i - 1].left_fork;
		if (pthread_mutex_init(&data->info[i].left_fork, NULL) != 0)
		{
			printf("Error occurred while creating mutexes.\n");
			return (destroy_forks(data, i), 1);
		}
		if (pthread_mutex_init(&data->info[i].last_meal_lock, NULL) != 0)
		{
			printf("Error occurred while creating mutexes.\n");
			return (destroy_forks(data, i + 1), \
			destroy_last_meal_locks(data, i), 1);
		}
		i++;
	}
	data->info[0].right_fork = &data->info[i - 1].left_fork;
	return (0);
}

/* a function to initiate special mutexes*/
int	init_mutexes(t_simulation *data)
{
	if (pthread_mutex_init(&data->print_lock, NULL) != 0)
		return (printf("Error occurred while creating mutexes.\n"), 1);
	if (pthread_mutex_init(&data->start_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print_lock);
		return (printf("Error occurred while creating mutexes.\n"), 1);
	}
	if (pthread_mutex_init(&data->finish_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print_lock);
		pthread_mutex_destroy(&data->start_lock);
		return (printf("Error occurred while creating mutexes.\n"), 1);
	}
	if (pthread_mutex_init(&data->exit_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print_lock);
		pthread_mutex_destroy(&data->start_lock);
		pthread_mutex_destroy(&data->finish_lock);
		return (printf("Error occurred while creating mutexes.\n"), 1);
	}
	return (0);
}

/* main function */
int	main(int argc, char **argv)
{
	t_simulation	data;

	if (argc != 5 && argc != 6)
		return (usage_printer(), 1);
	ft_memset(&data, 0, sizeof(t_simulation));
	if (parse_input(argc, argv, &data.set) || init_mutexes(&data))
		return (1);
	data.info = ft_calloc(data.set.num_philos, sizeof(t_philo));
	if (data.info == NULL)
		return (printf("Malloc failed.\n"), 1);
	if (data.set.num_mealtime == 0 && data.set.num_philos != 1)
		return (destroy_mutexes(&data), free(data.info), 0);
	if (data.set.num_philos == 1)
		return (solo_simulation(&data));
	if (personification(&data))
		return (destroy_mutexes(&data), free_pointers(&data), 1);
	if (create_philos(&data) || reaper(&data) \
	|| philos_join(&data, data.set.num_philos))
		return (free_before_terminating(&data), 1);
	return (free_before_terminating(&data), 0);
}
