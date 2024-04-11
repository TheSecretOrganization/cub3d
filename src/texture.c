/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:44:31 by abasdere          #+#    #+#             */
/*   Updated: 2024/04/03 14:45:13 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	destroy_texture(void *text)
{
	t_texture	*texture;

	texture = (t_texture *)text;
	mlx_destroy_image(texture->mlx, texture->img.ptr);
	free(texture);
}

static t_texture	*init_text(t_data *data, const char *k, const char *v)
{
	t_texture	*new;

	new = ft_calloc(1, sizeof(t_texture));
	if (!new)
		cerror(MALLOC_ERROR, "init_text", data->collector);
	new->key = k;
	new->next = NULL;
	new->mlx = data->window.mlx;
	new->img = (t_img){NULL, 0, 0, 0, 0, 0, 0};
	new->img.ptr = mlx_xpm_file_to_image(new->mlx, (char *)v,
			&new->img.width, &new->img.height);
	if (!new->img.ptr)
		(free(new), cerror(TEXTURE_ERROR, v, data->collector));
	add_collector(data->collector, new, &destroy_texture);
	new->img.content = mlx_get_data_addr(new->img.ptr, &new->img.bpp,
			&new->img.size_line, &new->img.endian);
	if (!new->img.content)
		cerror(TEXTURE_ERROR, v, data->collector);
	return (new);
}

void	add_text(t_data *data, const char *k, const char *v)
{
	t_texture	*new;
	t_texture	*last;
	int			fd;

	fd = open(v, O_RDONLY);
	if (fd == -1)
		cerror(TEXTURE_ERROR, v, data->collector);
	close(fd);
	new = init_text(data, k, v);
	if (!data->map.graphic.texture)
		data->map.graphic.texture = new;
	else
	{
		last = data->map.graphic.texture;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}
