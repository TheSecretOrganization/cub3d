/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 20:03:46 by averin            #+#    #+#             */
/*   Updated: 2023/11/07 11:36:45 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char	*r;
	size_t	i;

	r = (char *) ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!r)
		return (NULL);
	i = -1;
	while (s[++i])
		r[i] = f(i, s[i]);
	r[i] = '\0';
	return (r);
}
