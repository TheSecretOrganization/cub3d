/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 13:53:57 by averin            #+#    #+#             */
/*   Updated: 2023/11/13 10:48:36 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*r;
	size_t	slen;
	size_t	rlen;

	slen = ft_strlen(s);
	if (slen < start)
	{
		r = ft_calloc(1, sizeof(char));
		if (r == NULL)
			return (NULL);
		*r = '\0';
		return (r);
	}
	if (len > slen - start)
		rlen = slen - start;
	else
		rlen = len;
	r = (char *) ft_calloc(rlen + 1, sizeof(char));
	if (!r)
		return (NULL);
	ft_strlcpy(r, s + start, rlen + 1);
	return (r);
}
