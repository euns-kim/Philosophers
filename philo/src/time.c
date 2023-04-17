/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:19:22 by eunskim           #+#    #+#             */
/*   Updated: 2023/04/17 20:04:51 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// 1 seconds = 1000 milliseconds
// 1 microseconds = 0.001 milliseconds

// struct timeval {
// 	time_t		tv_sec; 	/* seconds */
// 	suseconds_t	tv_usec; 	/* microseconds */
// }

long long	current_time_in_ms(struct timeval tv)
{
	long long	timestamp;

	timestamp = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
	return (timestamp);
}

// int main(void)
// {
// 	struct timeval	tv;
// 	gettimeofday(&tv, NULL);
// 	printf("tv.tv_sec: %ld\n", tv.tv_sec);
// 	printf("tv.tv_usec: %d\n", tv.tv_usec);
// 	long long timestamp = current_time_in_ms(tv);
// 	printf("current time in milliseconds: %lld\n", timestamp);
// }
