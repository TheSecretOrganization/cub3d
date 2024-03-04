/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 17:17:54 by averin            #+#    #+#             */
/*   Updated: 2023/11/06 12:18:25 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	ch;

	ch = c;
	i = ft_strlen(s) - 1;
	if (ch == '\0')
		return ((char *) s + i + 1);
	while (i >= 0 && s[i])
	{
		if (s[i] == ch)
			return ((char *) s + i);
		i--;
	}
	return (NULL);
}
