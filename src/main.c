/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:52:38 by averin            #+#    #+#             */
/*   Updated: 2024/03/28 12:29:27 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	*search_texture(const char *name, t_map map)
{
	t_texture *texture = map.graphic.texture;

	while (texture)
	{
		if (ft_strncmp(name, texture->key, ft_strlen(name)) == 0)
			return (&texture->img);
		texture = texture->next;
	}
	return (NULL);
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
	t_hit	hit;

	ft_bzero(data->window.img.content, HEIGHT * data->window.img.size_line + WIDTH * (data->window.img.bpp / 8));
	i = -1;
	while (++i <= WIDTH)
	{
		double cameraX = 2 * i / (double) WIDTH -1;
		t_player *player = &data->player;
		t_vector direction = {
			player->direction.x + player->plane.x * cameraX,
			player->direction.y + player->plane.y * cameraX
		};
		raycast(player->pos, direction, data->map, &hit);
		int lineHeight = (int)(HEIGHT / hit.distance);
		int start = -lineHeight / 2 + HEIGHT / 2;
		if (start < 0)
			start = 0;
		int end = lineHeight / 2 + HEIGHT / 2;
		if(end >= HEIGHT)
			end = HEIGHT - 1;

		double wallX;
		if (hit.face == 0 || hit.face == 1)
			wallX = player->pos.y + hit.distance * direction.y;
		else
			wallX = player->pos.x + hit.distance * direction.x;
		wallX -= floor(wallX);

		t_img	*tex;
		if (hit.face == 0)
			tex = search_texture("NO", data->map);
		if (hit.face == 1)
			tex = search_texture("SO", data->map);
		if (hit.face == 2)
			tex = search_texture("EA", data->map);
		if (hit.face == 3)
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
