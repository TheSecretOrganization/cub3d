/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:17:02 by averin            #+#    #+#             */
/*   Updated: 2023/11/16 14:55:12 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*r;
	size_t	x;

	x = nmemb * size;
	if (size != 0 && x / size != nmemb)
		return (NULL);
	r = malloc(x);
	if (!r)
		return (NULL);
	ft_bzero(r, x);
	return (r);
}
