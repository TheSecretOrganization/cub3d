/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:21:09 by averin            #+#    #+#             */
/*   Updated: 2023/11/06 11:53:00 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*reverse_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*p;
	size_t			i;

	p = dest;
	i = n;
	while (i-- > 0)
		p[i] = ((unsigned char *) src)[i];
	return (dest);
}

static void	*memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*p;
	size_t			i;

	p = dest;
	i = -1;
	while (++i < n)
		p[i] = ((unsigned char *) src)[i];
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (dest > src)
		reverse_memcpy(dest, src, n);
	else
		memcpy(dest, src, n);
	return (dest);
}
