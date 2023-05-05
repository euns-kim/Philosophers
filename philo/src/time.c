/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:19:22 by eunskim           #+#    #+#             */
/*   Updated: 2023/05/05 15:31:50 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* a function which calls gettimeofday and returns the current time in ms */
t_milliseconds	current_time_in_ms(void)
{
	t_milliseconds	timestamp;
	struct timeval	now;

	gettimeofday(&now, NULL);
	timestamp = (now.tv_sec * 1000) + (now.tv_usec / 1000);
	return (timestamp);
}

/* a function which returns the time passed in ms since the start time */
t_milliseconds	time_passed(t_milliseconds start_time)
{
	return (current_time_in_ms() - start_time);
}

/* a substitute function for usleep to sleep more exact */
void	sleep_exact(t_milliseconds timeval)
{
	t_milliseconds	start_time;

	start_time = current_time_in_ms();
	while (time_passed(start_time) <= timeval)
		usleep(100);
}
