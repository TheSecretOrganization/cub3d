/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 19:20:37 by averin            #+#    #+#             */
/*   Updated: 2024/01/02 13:28:11 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_next_char_index(const char *s, char c)
{
	size_t	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == c)
			return (i);
	}
	return (i);
}

size_t	ft_count_words(const char *s, char c)
{
	size_t	r;

	r = 0;
	while (*s && *s == c)
		s++;
	if (*s == 0)
		return (0);
	while (*s)
	{
		if (*s == c)
		{
			r++;
			while (*s == c)
				s++;
			if (*s == 0)
				return (r);
		}
		s++;
	}
	return (r + 1);
}

void	ft_fsplit(char **s)
{
	size_t	i;

	if (s == NULL)
		return ;
	i = -1;
	while (s[++i] != NULL)
		free(s[i]);
	free(s);
}

char	**ft_split(const char *s, char c)
{
	size_t	size;

	return (ft_size_split(s, c, &size));
}

char	**ft_size_split(const char *s, char c, size_t *size)
{
	char	**r;
	size_t	i;
	size_t	k;
	size_t	next;

	*size = ft_count_words(s, c);
	r = (char **) ft_calloc(*size + 1, sizeof(char *));
	if (r == NULL)
		return (NULL);
	k = -1;
	i = 0;
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{
		next = get_next_char_index(s + i, c);
		r[++k] = ft_substr(s, i, next);
		if (r[k] == NULL)
			return (ft_fsplit(r), NULL);
		i += next;
		while (s[i] == c && s[i])
			i++;
	}
	return (r);
}
