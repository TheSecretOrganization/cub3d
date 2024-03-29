/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:52:38 by averin            #+#    #+#             */
/*   Updated: 2024/03/29 10:55:41 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_img	*finf_face_texture(t_dir face, t_map map)
{
	if (face == NO)
		return (search_texture("NO", map));
	else if (face == SO)
		return (search_texture("SO", map));
	else if (face == EA)
		return (search_texture("EA", map));
	else if (face == WE)
		return (search_texture("WE", map));
	else
		return (NULL);
}

static int	get_pixel(t_img *tex, int x, int y)
{
	return (*(tex->content + (y * tex->size_line + x * (tex->bpp / 8))));
}

void	init_img_line(t_data *data, int i, t_hit *hit)
{
	double cameraX = 2 * i / (double) WIDTH -1;
	t_player *player = &data->player;
	t_vector direction = {
		player->direction.x + player->plane.x * cameraX,
		player->direction.y + player->plane.y * cameraX
	};
	raycast(player->pos, direction, data->map, hit);
	int lineHeight = (int)(HEIGHT / hit->distance);
	int start = -lineHeight / 2 + HEIGHT / 2;
	if (start < 0)
		start = 0;
	int end = lineHeight / 2 + HEIGHT / 2;
	if(end >= HEIGHT)
		end = HEIGHT - 1;
	double wallX;
	if (hit->face == NO || hit->face == SO)
		wallX = player->pos.y + hit->distance * direction.y;
	else
		wallX = player->pos.x + hit->distance * direction.x;
	wallX -= floor(wallX);
	t_img	*tex = finf_face_texture(hit->face, data->map);
	int texX = wallX * (double) tex->width;
	double step = 1.0f * tex->width / lineHeight;
	double texPos = (start - HEIGHT / 2 + lineHeight / 2) * step;
	while (++start <= end)
	{
		img_pixel_put(&data->window.img, i, start - 1,
			get_pixel(tex, texX, (int) texPos & (tex->width - 1)));
		texPos += step;
	}
}

void	print_image(t_data *data)
{
	int		i;
	t_hit	hit;

	ft_bzero(data->window.img.content, HEIGHT * data->window.img.size_line
		+ WIDTH * (data->window.img.bpp / 8));
	i = -1;
	while (++i <= WIDTH)
		init_img_line(data, i, &hit);
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
