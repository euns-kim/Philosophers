/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 21:05:03 by eunskim           #+#    #+#             */
/*   Updated: 2023/05/04 16:00:06 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* a function which returns t_milliseconds value when successful */
/* for successful parsing overflow shouldn't happen, */
/* and string should not contain any character other than digits */
int	get_value_ms(t_milliseconds *time, const char *str)
{
	*time = 0;
	if (*str == '\0')
		return (1);
	while (*str)
	{
		if (ft_isdigit(*str) == 0)
			return (1);
		if (*time > ((ULONG_MAX - (*str - '0')) / 10))
			return (1);
		*time = *time * 10 + (*str - '0');
		str++;
	}
	return (0);
}

/* a function which returns uint value when successful */
/* for successful parsing overflow shouldn't happen, */
/* and string should not contain any character other than digits */
int	get_value_uint(unsigned int *num, const char *str)
{
	*num = 0;
	if (*str == '\0')
		return (1);
	while (*str)
	{
		if (ft_isdigit(*str) == 0)
			return (1);
		if (*num > ((UINT_MAX - (*str - '0')) / 10))
			return (1);
		*num = *num * 10 + (*str - '0');
		str++;
	}
	return (0);
}

/* input parser */
int	parse_input(int argc, char **argv, t_input *set)
{
	if (get_value_uint(&set->num_philos, argv[1]) \
	|| get_value_ms(&set->time_to_die, argv[2]) \
	|| get_value_ms(&set->time_to_eat, argv[3]) \
	|| get_value_ms(&set->time_to_sleep, argv[4]))
		return (printf("Parsing failed.\n"), 1);
	if (set->num_philos == 0)
		return (printf("Number of philosophers should be at least one.\n"), 1);
	set->num_mealtime = UINT_MAX;
	if (argc == 6)
	{
		if (get_value_uint(&set->num_mealtime, argv[5]))
			return (printf("Parsing failed.\n"), 1);
	}
	return (0);
}
