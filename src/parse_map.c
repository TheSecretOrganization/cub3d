/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:03:57 by abasdere          #+#    #+#             */
/*   Updated: 2024/03/07 13:04:53 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

#define VALID_CHAR "10NSEW "
#define PLAYER_VIEW "NSEW"
#define CHAR_ERROR "Invalid char found in the map"
#define MULTIPLE_PLAYER "Multiple starting player postion found"

void	parse_map(t_pmap *pmap, t_map *map, t_collector *collector)
{
	size_t	i;
	size_t	j;

	i = 0;
	map->map = ccalloc(pmap->size + 1, sizeof(char **), collector);
	while (pmap->map)
	{
		map->map[i++] = pmap->map->content;
		j = -1;
		while (map->map[i][++j])
		{
			if (!ft_strchr(VALID_CHAR, map->map[i][j]))
				cerror(CHAR_ERROR, collector);
			if (!ft_strchr(PLAYER_VIEW, map->map[i][j]))
				continue ;
			if (map->player.pos.x != 0 && map->player.pos.y != 0)
				cerror(MULTIPLE_PLAYER, collector);
			map->player = (t_player){{i, j}, {0, 0}};
			if ((map->map[i][j] == 'S' && ++(map->player.view.y))
				|| (map->map[i][j] == 'W' && ++(map->player.view.x)))
				;
		}
		pmap->map = pmap->map->next;
	}
}
