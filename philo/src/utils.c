/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 14:01:39 by eunskim           #+#    #+#             */
/*   Updated: 2023/05/05 15:35:46 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* a function which allocates memory space and fills up the space with 0 */
void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	if (size != 0 && count > SIZE_MAX / size)
		return (0);
	p = malloc(count * size);
	if (p == 0)
		return (p);
	ft_memset(p, 0, count * size);
	return (p);
}

/* a function which writes len bytes of value c to the string b */
void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*p;

	p = b;
	while (len != 0)
	{
		*p++ = (unsigned char) c;
		len--;
	}
	return (b);
}

/* a function which checkes if the parameter is a digit or not */
int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

/* free function that has a protection against freeing null */
void	free_p(void *ptr)
{
	if (ptr)
		free(ptr);
}
