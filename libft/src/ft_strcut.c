/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:05:46 by antoine           #+#    #+#             */
/*   Updated: 2023/12/20 15:14:16 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @param str String in wich cut
 * @param delimiter Char used to delimiter
 * @return A string containing the start to the first occurence of delimiter
*/
char	*ft_strcut(char *str, char delimiter)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != delimiter)
		i++;
	return (ft_substr(str, 0, i));
}
