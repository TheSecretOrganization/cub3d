/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 11:24:57 by abasdere          #+#    #+#             */
/*   Updated: 2024/03/29 11:25:40 by abasdere         ###   ########.fr       */
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
	return (*(int *)(tex->content + (y * tex->size_line + x * (tex->bpp / 8))));
}

/*
tools = {
	0 = start,
	1 = end,
	2 = lineHeight,
	3 = i
};
*/
static void	print_img_line(t_data *data, t_hit *hit, t_vector dir, int *tools)
{
	double	wall_x;
	int		tex_x;
	double	step;
	double	tex_pos;
	t_img	*tex;

	if (hit->face == NO || hit->face == SO)
		wall_x = data->player.pos.y + hit->distance * dir.y;
	else
		wall_x = data->player.pos.x + hit->distance * dir.x;
	wall_x -= floor(wall_x);
	tex = finf_face_texture(hit->face, data->map);
	tex_x = wall_x * (double) tex->width;
	step = 1.0f * tex->width / tools[2];
	tex_pos = (tools[0] - HEIGHT / 2 + tools[2] / 2) * step;
	while (++(tools[0]) <= tools[1])
	{
		img_pixel_put(&data->window.img, tools[3], tools[0] - 1,
			get_pixel(tex, tex_x, (int) tex_pos & (tex->width - 1)));
		tex_pos += step;
	}
}

static void	init_img_line(t_data *data, int i, t_hit *hit)
{
	t_vector	direction;
	int			end;
	int			start;
	int			line_height;

	direction = (t_vector){data->player.direction.x + data->player.plane.x
		* (2.0f * i / WIDTH - 1), data->player.direction.y
		+ data->player.plane.y * (2.0f * i / WIDTH - 1)};
	raycast(data->player.pos, direction, data->map, hit);
	line_height = (int)(HEIGHT / hit->distance);
	start = -line_height / 2 + HEIGHT / 2;
	if (start < 0)
		start = 0;
	end = line_height / 2 + HEIGHT / 2;
	if (end >= HEIGHT)
		end = HEIGHT - 1;
	print_img_line(data, hit, direction, (int [4]){start, end, line_height, i});
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
	mlx_put_image_to_window(data->window.mlx, data->window.ptr,
		data->window.img.ptr, 0, 0);
}
