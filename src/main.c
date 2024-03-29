/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:52:38 by averin            #+#    #+#             */
/*   Updated: 2024/03/29 09:08:23 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	raycast(t_vector position, t_vector direction, t_map map, int *r)
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
		*r = 0;
	else if (face == 0 && direction.x <= 0)
		*r = 1;
	else if (face == 1 && direction.y > 0)
		*r = 2;
	else if (face == 1 && direction.y <= 0)
		*r = 3;
	return (distance);
}

// void	draw_line(int start, int end, int x, t_window *win, int color)
// {
// 	int	y;

// 	y = start - 1;
// 	while (++y <= end)
// 		img_pixel_put(&win->img, x, y, color);
// }

void	print_image(t_data *data)
{
	int		i;
	float	dis;

	ft_bzero(data->window.img.content, HEIGHT * data->window.img.size_line + WIDTH * (data->window.img.bpp / 8));
	i = -1;
	while (++i <= WIDTH)
	{
		int face = 0;
		double cameraX = 2 * i / (double) WIDTH -1;
		t_player *player = &data->player;
		t_vector direction = {
			player->direction.x + player->plane.x * cameraX,
			player->direction.y + player->plane.y * cameraX
		};
		dis = raycast(player->pos, direction, data->map, &face);
		int lineHeight = (int)(HEIGHT / dis);
		int start = -lineHeight / 2 + HEIGHT / 2;
		if (start < 0)
			start = 0;
		int end = lineHeight / 2 + HEIGHT / 2;
		if(end >= HEIGHT)
			end = HEIGHT - 1;

		double wallX;
		if (face == 0 || face == 1)
			wallX = player->pos.y + dis * direction.y;
		else
			wallX = player->pos.x + dis * direction.x;
		wallX -= floor(wallX);

		t_img	*tex;
		if (face == 0)
			tex = search_texture("NO", data->map);
		if (face == 1)
			tex = search_texture("SO", data->map);
		if (face == 2)
			tex = search_texture("EA", data->map);
		if (face == 3)
			tex = search_texture("WE", data->map);
		if (!tex)
		{
			(printf("no text\n"), mlx_loop_end(data->window.mlx));
			return ;
		}

		int texX = wallX * (double) tex->width;
		// if ((face == 0 || face == 1) && direction.x > 0) texX = tex->width - texX - 1;
		// else if (direction.y < 0) texX = tex->width - texX - 1;

		double step = 1.0f * tex->width / lineHeight;
		double texPos = (start - HEIGHT / 2 + lineHeight / 2) * step;
		int y = start - 1;
		while (++y < end)
		{
			int texY = (int) texPos & (tex->width - 1);
			texPos += step;
			int *pixel = (int *)(tex->content + (texY * tex->size_line + texX * (tex->bpp / 8)));
			img_pixel_put(&data->window.img, i, y, *pixel);
		}
	}
	mlx_put_image_to_window(data->window.mlx, data->window.ptr, data->window.img.ptr, 0, 0);
}

int	main(int argc, char const *argv[])
{
	t_data	data;

	if (argc != 2)
		error(USAGE_ERROR, NULL);
	data.window = (t_window){NULL, NULL,
		{NULL, NULL, 0, 0, 0, 0, 0}};
	data.player = (t_player){{0, 0}, {0, 0.66f}, {-1, 0}};
	data.map = (t_map){0, {NULL, NULL}, 0, 0};
	data.collector = init_collector();
	create_window(&data.window, data.collector);
	parse_file(&data, argv[1]);
	print_image(&data);
	init_hook(&data);
	mlx_loop(data.window.mlx);
	return (free_collector(data.collector), 0);
}
