/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:47:32 by abasdere          #+#    #+#             */
/*   Updated: 2024/04/08 17:10:07 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	replace_char(char *s, char target, char replace)
{
	size_t	i;

	i = -1;
	while (s[++i])
		if (s[i] == target)
			s[i] = replace;
}
