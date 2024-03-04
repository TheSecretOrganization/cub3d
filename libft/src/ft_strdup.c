/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:09:01 by averin            #+#    #+#             */
/*   Updated: 2023/11/06 11:52:58 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*r;

	r = (char *) malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!r)
		return (NULL);
	ft_strlcpy(r, s, ft_strlen(s) + 1);
	return (r);
}
