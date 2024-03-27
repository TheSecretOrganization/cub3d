/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:47:32 by abasdere          #+#    #+#             */
/*   Updated: 2024/03/27 16:35:59 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_space(char *line)
{
	size_t		len;
	size_t		i;

	len = ft_strlen(line);
	i = -1;
	while (++i < len)
	{
		if (line[i] == ' ')
		{
			ft_memcpy(&(line[i]), &(line[i + 1]), len - i);
			len--;
			i--;
		}
	}
}

void	remove_space(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	if (!line[i])
		return ;
	i++;
	move_space(line + i);
}

size_t	check_commas(const char *value)
{
	size_t	i;
	size_t	commas;

	i = -1;
	commas = 0;
	while (value[++i])
		if (value[i] == ',')
			commas++;
	return (commas);
}

static void	destroy_texture(void *text)
{
	t_texture	*texture;

	texture = (t_texture *)text;
	mlx_destroy_image(texture->mlx, texture->img.ptr);
	free(texture);
}

t_texture	*init_text(t_data *data, const char *k, const char *v)
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
