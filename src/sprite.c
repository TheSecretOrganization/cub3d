/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:42:04 by abasdere          #+#    #+#             */
/*   Updated: 2024/04/09 16:59:38 by abasdere         ###   ########.fr       */
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
	new->distance = 0;
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

void	add_sprite(t_data *data, const char **kvsp)
{
	t_sprite	*new;
	t_sprite	*last;
	int			fd;

	fd = open(kvsp[1], O_RDONLY);
	if (fd == -1)
		cerror(TEXTURE_ERROR, kvsp[1], data->collector);
	close(fd);
	new = init_sprite(data, kvsp[0], kvsp[1]);
	new->pos = (t_vector){ft_atof(kvsp[2]), ft_atof(kvsp[3])};
	if (new->pos.x <= 0 || (int)new->pos.x >= WIDTH - 1
		|| new->pos.y <= 0 || (int)new->pos.y >= HEIGHT - 1)
		cerror(SPRITE_POS_ERROR_1, kvsp[0], data->collector);
	if (check_sprite_pos(data->map.graphic.sprite, new->pos))
		cerror(SPRITE_POS_ERROR_2, kvsp[0], data->collector);
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

void	check_sprite_free_space(t_data *data)
{
	t_sprite	*s;

	s = data->map.graphic.sprite;
	while (s)
	{
		if ((size_t)(int)s->pos.x >= data->map.width - 1
			|| (size_t)(int)s->pos.y >= data->map.heigh - 1)
			cerror(SPRITE_POS_ERROR_1, s->key, data->collector);
		if (data->map.content[(int)s->pos.y][(int)s->pos.x] != '0')
			cerror(SPRITE_POS_ERROR_2, s->key, data->collector);
		s = s->next;
	}
}

t_sprite	*check_sprite_pos(t_sprite *sprite, t_vector pos)
{
	while (sprite)
	{
		if ((int)sprite->pos.x == (int)pos.x
			&& (int)sprite->pos.y == (int)pos.y)
			return (sprite);
		sprite = sprite->next;
	}
	return (NULL);
}
