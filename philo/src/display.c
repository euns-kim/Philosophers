/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 20:23:04 by eunskim           #+#    #+#             */
/*   Updated: 2023/04/19 22:32:20 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_printer(t_philo *info)
{
	pthread_mutex_lock(info->data->printer_mutex);
	printf("%lld", current_time_in_ms());
	printf(" philosopher #%u ", info->philo_id);
	if (info->being == DEAD)
		printf("died\n");
	else if (info->being == ALIVE)
	{
		if (info->act == GOT_FORKS)
			printf("has taken a fork\n");
		else if (info->act == THINKING)
			printf("is thinking\n");
		else if (info->act == EATING)
			printf("is eating\n");
		else if (info->act == SLEEPING)
			printf("is sleeping\n");
	}
	pthread_mutex_unlock(info->data->printer_mutex);
}
