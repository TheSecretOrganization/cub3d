/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:52:38 by averin            #+#    #+#             */
/*   Updated: 2024/03/20 18:32:57 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "collector.h"
#include "parsing.h"
#include "window.h"
#include <math.h>

#define USAGE_ERROR "Usage: ./cub3d <file.cub>"

float	raycast(t_vector position, t_vector direction, t_map map)
{
	int hit = 0;
	int face;
	t_vector step = {0, 0};
	t_vector side = {0, 0};
	int map_pos[2] = {(int) position.x, (int) position.y};
	t_vector delta = {
		direction.x == 0 ? 1e30 : fabs(1 / direction.x),
		direction.y == 0 ? 1e30 : fabs(1 / direction.y)
	};
	float	distance = -1;

	if (direction.x < 0)
	{
		step.x = -1;
		side.x = (position.x - (int) position.x) * delta.x;
	}
	else
	{
		step.x = 1;
		side.x = (position.x + 1 - (int) position.x) * delta.x;
	}
	if (direction.y >= 0)
	{
		step.y = -1;
		side.y = (position.y - (int) position.y) * delta.y;
	}
	else
	{
		step.y = 1;
		side.y = (position.y + 1 - (int) position.y) * delta.y;
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
		if (map.content[map_pos[1]][map_pos[0]] == '1') hit = 1;
	}
	if (face == 0)
		distance = side.x - delta.x;
	else
		distance = side.y - delta.y;
	return (distance);
}

void	draw_line(int start, int end, int x, t_window *win)
{
	int	y;

	y = start - 1;
	while (++y <= end)
		img_pixel_put(&win->img, x, y, 0xfecaca);
}

void	print_image(t_data *data)
{
	int		i;
	float	dis;

	ft_bzero(data->window.img.content, HEIGHT * data->window.img.size_line + WIDTH * (data->window.img.bpp / 8));
	i = -1;
	while (++i <= WIDTH)
	{
		double cameraX = 2 * i / (double) WIDTH -1;
		dis = raycast(data->map.player.pos,
			(t_vector){
				cos(data->map.player.dir) + 0 * cameraX,
				sin(data->map.player.dir) + 0.66f * cameraX,
			}, data->map);
		int lineHeight = (int)(HEIGHT / dis);
		int start = -lineHeight / 2 + HEIGHT / 2;
		if (start < 0)
			start = 0;
		int end = lineHeight / 2 + HEIGHT / 2;
		if(end >= HEIGHT)
			end = HEIGHT - 1;
		if (i > WIDTH - 100 && i % 5 == 0)
			printf("%d: %0.3f\n", i, dis);
		draw_line(start, end, i, &data->window);
	}
	// i = 10;
	// while (i < WIDTH)
	// {
	// 	angle = RAD(-half_fov + i * angle_increment);
	// 	dis = raycast(data->map.player.pos,
	// 		(t_vector){cos(angle), sin(angle)}, data->map);
	// 	int lineHeight = (int)(HEIGHT / dis);
	// 	int start = -lineHeight / 2 + HEIGHT / 2;
    // 	if (start < 0)
	// 		start = 0;
    // 	int end = lineHeight / 2 + HEIGHT / 2;
    // 	if(end >= HEIGHT)
	//   		end = HEIGHT - 1;

	// 	printf("%d: %f\t%d - %d\t%d\n", i, dis, start, end, end - start);
	// 	char str[200];
	// 	sprintf(str, "%0.3f %d", dis, end - start);
	// 	mlx_string_put(data->window.mlx, data->window.ptr, i, 100, 0x00FF00, str);
	// 	i += 100;
	// }
	mlx_put_image_to_window(data->window.mlx, data->window.ptr, data->window.img.ptr, 0, 0);
}

int	main(int argc, char const *argv[])
{
	t_data	data;

	if (argc != 2)
		error(USAGE_ERROR);
	data.window = (t_window){NULL, NULL,
		{NULL, NULL, 0, 0, 0}};
	data.map = (t_map){0, {{0, 0}, 0}, {NULL, NULL}, 0, 0};
	data.collector = init_collector();
	parse_file(&data.map, argv[1], data.collector);
	create_window(&data.window, data.collector);
	print_image(&data);
	init_hook(&data);
	mlx_loop(data.window.mlx);
	return (free_collector(data.collector), 0);
}
