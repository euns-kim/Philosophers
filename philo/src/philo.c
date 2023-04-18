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

void	*routine(void *arg)
{
	(void) arg;
	printf("One of the philos said: I am philosopher.\n");
	return (NULL);
}

int	init_philo(t_philo *data, t_input set)
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
	t_philo			data;
	t_input			set;
	unsigned int	i;

	i = 0;
	if (parse_input(argc, argv, &set) || init_philo(&data, set))
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
