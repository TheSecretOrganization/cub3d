/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:26:54 by abasdere          #+#    #+#             */
/*   Updated: 2024/04/23 14:54:51 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define DOOR 0xCD7F32
#define PATH 0xFFFFFF
#define PLAYER 0x0000FF
#define WALL 0x000000
#define MINIMAP_DIM 10

static int	get_color(char tile, int is_player)
{
	if (is_player)
		return (PLAYER);
	else if (tile == '1')
		return (WALL);
	else if (tile == 'D')
		return (DOOR);
	else if (tile == '0')
		return (PATH);
	else
		return (WALL);
}

static void	draw(t_data *data, size_t x, size_t y, int color)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (++i < MINIMAP_DIM)
	{
		j = -1;
		while (++j < MINIMAP_DIM)
			img_pixel_put(&data->window.img, x * MINIMAP_DIM + j,
				y * MINIMAP_DIM + i, color);
	}
}

void	draw_minimap(t_data *data)
{
	size_t	y;
	size_t	x;
	int		is_player;

	if (!(data->controls & C_MINIMAP))
		return ;
	y = -1;
	while (++y < data->map.height)
	{
		x = -1;
		while (++x < data->map.width)
		{
			is_player = (y == (size_t)data->player.pos.y
					&& x == (size_t)data->player.pos.x);
			draw(data, x, y, get_color(data->map.content[y][x], is_player));
		}
	}
}
