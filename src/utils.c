/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:59:20 by abasdere          #+#    #+#             */
/*   Updated: 2024/04/23 15:22:51 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cerror(const char *message, const char *el, t_collector *collector)
{
	ft_dprintf(2, "Error\n%s", message);
	if (el)
		ft_dprintf(2, ": %s", el);
	ft_putchar_fd('\n', 2);
	if (collector)
		free_collector(collector);
	exit(1);
}

void	error(const char *message, const char *el)
{
	cerror(message, el, NULL);
}

float	rad(float deg)
{
	return (deg * M_PI / 180);
}

int	search_color(const char *name, t_map map)
{
	t_color	*color;

	color = map.graphic.color;
	while (color)
	{
		if (ft_strncmp(name, color->key, ft_strlen(name)) == 0)
			return (
				color->red << 16 | color->blue << 8 | color->green
			);
		color = color->next;
	}
	return (-1);
}

t_img	*search_texture(const char *name, t_map map)
{
	t_texture	*texture;

	texture = map.graphic.texture;
	while (texture)
	{
		if (ft_strncmp(name, texture->key, ft_strlen(name)) == 0)
			return (&texture->img);
		texture = texture->next;
	}
	return (NULL);
}
