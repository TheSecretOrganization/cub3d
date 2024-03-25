/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:52:38 by averin            #+#    #+#             */
/*   Updated: 2024/03/25 15:36:58 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "collector.h"
#include "parsing.h"
#include "window.h"
#include <math.h>

#define USAGE_ERROR "Usage: ./cub3d <file.cub>"

float	raycast(t_vector position, t_vector direction, t_map map, int *color)
{
	int hit = 0;
	int face = 0;
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
		side.x = (position.x - map_pos[0]) * delta.x;
	}
	else
	{
		step.x = 1;
		side.x = (map_pos[0] + 1.0f - position.x) * delta.x;
	}
	if (direction.y < 0)
	{
		step.y = -1;
		side.y = (position.y - map_pos[1]) * delta.y;
	}
	else
	{
		step.y = 1;
		side.y = (map_pos[1] + 1.0f - position.y) * delta.y;
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
	
	if (face == 0 && direction.x > 0)
		*color = 0xfecaca;
	else if (face == 0 && direction.x <= 0)
		*color = 0xbeef00;
	else if (face == 1 && direction.y > 0)
		*color = 0xfadeff;
	else if (face == 1 && direction.y <= 0)
		*color = 0x363042;
	else
		*color = 0xffffff;
	return (distance);
}

void	draw_line(int start, int end, int x, t_window *win, int color)
{
	int	y;

	y = start - 1;
	while (++y <= end)
		img_pixel_put(&win->img, x, y, color);
}

void	print_image(t_data *data)
{
	int		i;
	float	dis;

	ft_bzero(data->window.img.content, HEIGHT * data->window.img.size_line + WIDTH * (data->window.img.bpp / 8));
	i = -1;
	while (++i <= WIDTH)
	{
		int color = 0;
		double cameraX = 2 * i / (double) WIDTH -1;
		dis = raycast(data->map.player.pos,
			(t_vector){
				data->map.player.direction.x + data->map.player.plane.x * cameraX,
				data->map.player.direction.y + data->map.player.plane.y * cameraX
			}, data->map, &color);
		int lineHeight = (int)(HEIGHT / dis);
		int start = -lineHeight / 2 + HEIGHT / 2;
		if (start < 0)
			start = 0;
		int end = lineHeight / 2 + HEIGHT / 2;
		if(end >= HEIGHT)
			end = HEIGHT - 1;
		if (i % 100 == 0)
			printf("%d: %0.3f\n", i, dis);
		draw_line(start, end, i, &data->window, color);
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
	data.map = (t_map){0, {{0, 0}, {0, 0.66f}, {-1, 0}}, {NULL, NULL}, 0, 0};
	data.collector = init_collector();
	parse_file(&data.map, argv[1], data.collector);
	create_window(&data.window, data.collector);
	print_image(&data);
	init_hook(&data);
	mlx_loop(data.window.mlx);
	return (free_collector(data.collector), 0);
}
