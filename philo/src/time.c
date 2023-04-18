/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:19:22 by eunskim           #+#    #+#             */
/*   Updated: 2023/04/18 22:19:01 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_milliseconds	current_time_in_ms(void)
{
	t_milliseconds	timestamp;
	struct timeval	now;

	gettimeofday(&now, NULL);
	timestamp = (now.tv_sec * 1000) + (now.tv_usec / 1000);
	return (timestamp);
}
