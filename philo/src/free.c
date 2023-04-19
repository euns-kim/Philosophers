/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:38:42 by eunskim           #+#    #+#             */
/*   Updated: 2023/04/19 22:27:36 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_before_terminating(t_simulation *data)
{
	free(data->philos);
	free(data->forks);
}

void	free_p(void *ptr)
{
	if (ptr)
		free(ptr);
}
