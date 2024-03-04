/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 19:45:56 by averin            #+#    #+#             */
/*   Updated: 2023/12/02 23:31:57 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_chars(int n)
{
	size_t	chars;

	chars = 0;
	if (n == -2147483648)
		return (11);
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		chars++;
	}
	while (n > 0)
	{
		n /= 10;
		chars++;
	}
	return (chars);
}

char	*ft_itoa(int n)
{
	char	*r;
	int		sign;
	size_t	i;

	sign = 0;
	if (n < 0)
		sign = 1;
	i = count_chars(n);
	r = (char *) ft_calloc(i + 1, sizeof(char));
	if (!r)
		return (NULL);
	while (i-- > 0)
	{
		r[i] = ft_abs(n % 10) + '0';
		n /= 10;
	}
	if (sign)
		r[0] = '-';
	return (r);
}
