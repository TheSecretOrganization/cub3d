/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:47:32 by abasdere          #+#    #+#             */
/*   Updated: 2024/03/11 11:02:21 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	move_space(char *line)
{
	size_t		len;
	size_t		i;

	len = ft_strlen(line);
	i = -1;
	while (++i < len)
	{
		if (line[i] == ' ')
		{
			ft_memcpy(&(line[i]), &(line[i + 1]), len - i);
			len--;
			i--;
		}
	}
}

void	remove_space(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	if (!line[i])
		return ;
	i++;
	move_space(line + i);
}

size_t	check_commas(const char *value)
{
	size_t	i;
	size_t	commas;

	i = -1;
	commas = 0;
	while (value[++i])
		if (value[i] == ',')
			commas++;
	return (commas);
}
