/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 13:42:12 by averin            #+#    #+#             */
/*   Updated: 2023/11/16 15:42:41 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_shift_str(char *s, size_t shift, size_t len)
{
	size_t	i;

	i = -1;
	while (++i < len)
	{
		if (shift + i >= len)
			s[i] = '\0';
		else
			s[i] = s[shift + i];
	}
}

size_t	find_end_line(char *s, size_t len)
{
	size_t	i;

	i = -1;
	while (s[++i] && i < len)
	{
		if (s[i] == '\n')
			return (i + 1);
	}
	if (s[i])
		return (i - 1);
	return (i);
}

char	*ft_strcat(char *s1, char *s2)
{
	size_t	i;
	size_t	s1_len;
	size_t	s2_len;
	char	*str;

	i = -1;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = ft_calloc(s1_len + s2_len + 1, sizeof(char));
	if (!str)
		return (NULL);
	while (++i < s1_len)
		str[i] = s1[i];
	--i;
	while (++i < s1_len + s2_len)
		str[i] = s2[i - s1_len];
	str[i] = '\0';
	free(s1);
	free(s2);
	return (str);
}
