/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrplc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:05:44 by averin            #+#    #+#             */
/*   Updated: 2024/01/19 14:04:41 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Replace the string `td` in the string `from` by the string `tr`
 * @param from the string in wich replace
 * @param td the string to delete
 * @param tr the string to replace by
 * @return a new freeable string or NULL
*/
char	*ft_strrplc(char *from, char *td, char *tr)
{
	size_t	i;
	size_t	td_len;
	char	*str;

	td_len = ft_strlen(td);
	i = -1;
	str = ft_calloc(ft_strlen(from) - td_len + ft_strlen(tr) + 1, sizeof(char));
	if (!str)
		return (NULL);
	while (*from && ft_strncmp(from, td, ft_strlen(td)))
		str[++i] = *(from++);
	while (*tr)
		str[++i] = *(tr++);
	from += td_len;
	while (*from)
		str[++i] = *(from++);
	return (str);
}

/**
 * Replace the string `td` in the string `from` by the string `tr`
 * and free `from`
 * @param from the string in wich replace and that will be freed
 * @param td the string to delete
 * @param tr the string to replace by
 * @return a new freeable string or NULL
*/
char	*ft_fstrrplc(char *from, char *td, char *tr)
{
	char	*str;

	str = ft_strrplc(from, td, tr);
	free(from);
	return (str);
}
