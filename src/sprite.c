/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:42:04 by abasdere          #+#    #+#             */
/*   Updated: 2024/04/03 14:21:47 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	destroy_sprite(void *sprite)
{
	t_sprite	*s;

	s = (t_sprite *)sprite;
	mlx_destroy_image(s->mlx, s->img.ptr);
	free(s);
}

static t_sprite	*init_sprite(t_data *data, const char *k, const char *v)
{
	t_sprite	*new;

	new = ft_calloc(1, sizeof(t_sprite));
	if (!new)
		cerror(MALLOC_ERROR, "init_text", data->collector);
	new->key = k;
	new->next = NULL;
	new->mlx = data->window.mlx;
	new->pos = (t_vector){0, 0};
	new->img = (t_img){NULL, 0, 0, 0, 0, 0, 0};
	new->img.ptr = mlx_xpm_file_to_image(new->mlx, (char *)v,
			&new->img.width, &new->img.height);
	if (!new->img.ptr)
		(free(new), cerror(TEXTURE_ERROR, v, data->collector));
	add_collector(data->collector, new, &destroy_sprite);
	new->img.content = mlx_get_data_addr(new->img.ptr, &new->img.bpp,
			&new->img.size_line, &new->img.endian);
	if (!new->img.content)
		cerror(TEXTURE_ERROR, v, data->collector);
	return (new);
}

void	add_sprite(t_data *data, const char *k, const char *v)
{
	t_sprite	*new;
	t_sprite	*last;
	int			fd;

	fd = open(v, O_RDONLY);
	if (fd == -1)
		cerror(TEXTURE_ERROR, v, data->collector);
	close(fd);
	new = init_sprite(data, k, v);
	if (!data->map.graphic.sprite)
		data->map.graphic.sprite = new;
	else
	{
		last = data->map.graphic.sprite;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}
