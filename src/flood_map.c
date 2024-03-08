/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:40:19 by abasdere          #+#    #+#             */
/*   Updated: 2024/03/08 11:45:14 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

#define MALLOC_ERROR "Malloc failed"
#define WALL_ERROR "There is a hole in the walls"

static int	flood(char **map, size_t *rules, size_t x, size_t y)
{
	int	code;

	code = 0;
	if (map[y][x] == '1')
		return (0);
	if (map[y][x] == '\0')
		return (1);
	if (x == 0 || x == rules[1] || y == 0 || y == rules[0] - 1)
		return (1);
	map[y][x] = '1';
	if (y > 0 && code == 0)
		code = flood(map, rules, x, y - 1);
	if (y < rules[0] - 1 && code == 0)
		code = flood(map, rules, x, y + 1);
	if (x > 0 && code == 0)
		code = flood(map, rules, x - 1, y);
	if (x < rules[1] && code == 0)
		code = flood(map, rules, x + 1, y);
	return (code);
}

static int	find_starting_points(char **map, size_t *rules)
{
	size_t	y;
	size_t	x;

	y = -1;
	while (++y < rules[0])
	{
		x = -1;
		while (++x < rules[1])
			if (map[y][x] != '1' && map[y][x] != '\0'
				&& flood(map, rules, x, y))
				return (1);
	}
	return (0);
}

void	flood_map(t_map *map, t_collector *collector)
{
	char	**cpy;
	size_t	y;
	size_t	x;

	cpy = ft_calloc(map->heigh + 1, sizeof(char *));
	if (!cpy)
		cerror(MALLOC_ERROR, collector);
	y = -1;
	while (++y < map->heigh)
	{
		cpy[y] = ft_calloc(map->width + 1, sizeof(char));
		if (!cpy[y])
			(ft_fsplit(cpy), cerror(MALLOC_ERROR, collector));
		x = -1;
		while (++x < map->width)
			cpy[y][x] = map->map[y][x];
	}
	if (find_starting_points(cpy, (size_t[2]){map->heigh, map->width}))
		(ft_fsplit(cpy), cerror(WALL_ERROR, collector));
	ft_fsplit(cpy);
}
