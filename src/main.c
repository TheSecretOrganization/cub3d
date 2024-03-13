/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:52:38 by averin            #+#    #+#             */
/*   Updated: 2024/03/13 10:45:23 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "collector.h"
#include "parsing.h"
#include "window.h"
#include <math.h>

#define USAGE_ERROR "Usage: ./cub3d <file.cub>"

float	raycast(t_vector *position, t_vector *direction, t_map *map)
{
	int hit = 0;
	int face;
	t_vector step = {0, 0};
	t_vector side = {0, 0};
	int map_pos[2] = {(int) position->x, (int) position->y};
	t_vector delta = {
		direction->x == 0 ? 1e30 : fabs(1 / direction->x),
		direction->y == 0 ? 1e30 : fabs(1 / direction->y)
	};
	float	distance = -1;

	if (direction->x < 0)
	{
		step.x = -1;
		side.x = (position->x - (int) position->x) * delta.x;
	}
	else
	{
		step.x = 1;
		side.x = (position->x + 1 - (int) position->x) * delta.x;
	}
	if (direction->y >= 0)
	{
		step.y = -1;
		side.y = (position->y - (int) position->y) * delta.y;
	}
	else
	{
		step.y = 1;
		side.y = (position->y + 1 - (int) position->y) * delta.y;
	}
	while (hit == 0)
	{
		if (side.x < side.y)
		{
			side.x += delta.x;
			map_pos[0] += step.x;
			face = 0;
		}
		else
		{
			side.y += delta.y;
			map_pos[1] += step.y;
			face = 1;
		}
		if (map->content[map_pos[1]][map_pos[0]] == '1') hit = 1;
	}
	if (face == 0)
	{
		if (step.x < 0)
			distance = side.x - delta.x;
		else
			distance = side.x - delta.x * 2;
	}
	else
	{
		if (step.y < 0)
			distance = side.y - delta.y;
		else
			distance = side.y - delta.y * 2;
	}
	return (distance);
}



int	main(int argc, char const *argv[])
{
	t_data	data;

	if (argc != 2)
		error(USAGE_ERROR);
	data.window = (t_window){NULL, NULL};
	data.map = (t_map){0, {{0, 0}, {0, 0}, {0, 0.66}}, {NULL, NULL}, 0, 0};
	data.collector = init_collector();
	parse_file(&data.map, argv[1], data.collector);
	create_window(&data.window, data.collector);
	init_hook(&data);
	mlx_loop(data.window.mlx);
	return (free_collector(data.collector), 0);
}
