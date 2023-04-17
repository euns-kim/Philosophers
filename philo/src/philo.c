/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 20:41:15 by eunskim           #+#    #+#             */
/*   Updated: 2023/04/17 21:30:21 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	(void) arg;
	printf("One of the philos said: I am philosopher.\n");
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philo			philo;
	unsigned int	i;

	if (argc < 5 || argc > 6)
	{
		write(1, "Invalid arguments.\n", 20);
		return (1);
	}
	i = 0;
	philo.num_philos = *argv[1];
	philo.philos = malloc(philo.num_philos * sizeof(pthread_t));
	if (philo.philos == NULL)
	{
		write(1, "Malloc failed.\n", 16);
		return (1);
	}
	philo.philo_ids = malloc(philo.num_philos * sizeof(unsigned int));
	if (philo.philo_ids == NULL)
	{
		free(philo.philos);
		write(1, "Malloc failed.\n", 16);
		return (1);
	}
	while (i < philo.num_philos)
	{
		philo.philo_ids[i] = i;
		if (pthread_create(&philo.philos[i], NULL, routine, NULL) != 0)
		{
			free(philo.philos);
			free(philo.philo_ids);
			write(1, "Error occurred while creating threads.\n", 40);
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < philo.num_philos)
	{
		if (pthread_join(philo.philos[i], NULL) != 0)
		{
			free(philo.philos);
			free(philo.philo_ids);
			write(1, "Error occurred while joining threads.\n", 39);
			return (1);
		}
		i++;
	}
	write(1, "All philos spoke successfully.\n", 32);

	struct timeval	tv;
	gettimeofday(&tv, NULL);
	long long timestamp = current_time_in_ms(tv);
	printf("Current time in milliseconds: %lld\n", timestamp);

	return (0);
}
