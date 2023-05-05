/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:38:42 by eunskim           #+#    #+#             */
/*   Updated: 2023/05/05 15:29:50 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* a function which frees and destroys everything before terminating */
void	free_before_terminating(t_simulation *data)
{
	destroy_forks(data, data->set.num_philos);
	destroy_last_meal_locks(data, data->set.num_philos);
	destroy_mutexes(data);
	free_pointers(data);
}

/* a function freeing pointer when there is one to free */
void	free_pointers(t_simulation *data)
{
	free_p(data->philos);
	free_p(data->info);
}

/* a function which destroys three special mutexes */
void	destroy_mutexes(t_simulation *data)
{
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->start_lock);
	pthread_mutex_destroy(&data->exit_lock);
}

/* a function which destroys multiple mutexes with an index */
void	destroy_last_meal_locks(t_simulation *data, unsigned int i)
{
	while (--i)
		pthread_mutex_destroy(&data->info[i].last_meal_lock);
}

/* a function which destroys multiple mutexes with an index */
void	destroy_forks(t_simulation *data, unsigned int i)
{
	while (--i)
		pthread_mutex_destroy(&data->info[i].left_fork);
}
