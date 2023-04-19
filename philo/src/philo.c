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

int	offer_forks(t_simulation *data, t_input set)
{
	unsigned int	i;

	i = 0;
	data->forks = malloc(set.num_philos * sizeof(pthread_mutex_t));
	if (data->forks == NULL)
	{
		printf("Malloc failed.\n");
		return (1);
	}
	while (i < set.num_philos)
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

void	*routine(void *arg)
{
	(void) arg;
	printf("One of the philos said: I am philosopher.\n");
	return (NULL);
}

int	create_philos(t_simulation *data, t_input set)
{
	unsigned int	i;

	i = 0;
	data->philos = malloc(set.num_philos * sizeof(pthread_t));
	if (data->philos == NULL)
	{
		printf("Malloc failed.\n");
		return (1);
	}
	while (i < set.num_philos)
	{
		if (pthread_create(&data->philos[i], NULL, routine, NULL) != 0)
		{
			free_before_terminating(data);
			printf("Error occurred while creating threads.\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_simulation	data;
	t_input			set;
	unsigned int	i;

	i = 0;
	if (argc != 5 && argc != 6)
	{
		printf("Invalid arguments.");
		return (1);
	}
	if (parse_input(argc, argv, &set) || create_philos(&data, set) \
	|| offer_forks(&data, set))
		return (1);
	while (i < set.num_philos)
	{
		if (pthread_join(data.philos[i], NULL) != 0)
		{
			free_before_terminating(&data);
			printf("Error occurred while joining threads.\n");
			return (1);
		}
		i++;
	}
	printf("All philos spoke successfully.\n");
	return (0);
}
