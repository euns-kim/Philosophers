/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:38:42 by eunskim           #+#    #+#             */
/*   Updated: 2023/04/20 16:35:53 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_before_terminating(t_simulation *data)
{
	unsigned int	i;

	i = 0;
	if (data->philos != NULL)
	{
		while (i < data->set.num_philos)
		{
			
		}
		i++;		
	}
	destroy_mutex(data->print_lock);
	destroy_mutex(data->exit_lock);
	free_p(data->philos);
	free_p(data->forks);
}


void	destroy_mutex(pthread_mutex_t *mtx)
{
	if (mtx)
		pthread_mutex_destroy(mtx);
}

void	free_p(void *ptr)
{
	if (ptr)
		free(ptr);
}
