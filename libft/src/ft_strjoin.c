/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:07:52 by averin            #+#    #+#             */
/*   Updated: 2024/02/14 15:01:36 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*r;
	size_t	size;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	r = (char *) ft_calloc(size, sizeof(char));
	if (!r)
		return (NULL);
	ft_strlcat(r, s1, size);
	ft_strlcat(r, s2, size);
	return (r);
}

/**
 * @brief Join two string and free n strings
 *
 * @param s1 string 1 to join
 * @param s2 string 2 to join
 * @param n set to 1 to free s1, 2 to free s2 or 0 to free both
 * @return char* or NULL if an error occurs
 */
char	*ft_fstrjoin(const char *s1, const char *s2, int n)
{
	char	*join;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	join = ft_strjoin(s1, s2);
	if (n == 1)
		free((char *)s1);
	else if (n == 2)
		free((char *)s2);
	else if (!n)
		(free((char *)s1), free((char *)s2));
	return (join);
}
