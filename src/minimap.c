/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:26:54 by abasdere          #+#    #+#             */
/*   Updated: 2024/04/19 16:14:57 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define DOOR 0xCD7F32
#define PATH 0xFFFFFF
#define PLAYER 0x0000FF
#define WALL 0x000000

static int	get_color(char tile, int is_player)
{
	if (is_player)
		return (PLAYER);
	else if (tile == '1')
		return (WALL);
	else if (tile == 'D')
		return (DOOR);
	else
		return (PATH);
}

void	draw_minimap(t_data *data)
{
	size_t	y;
	size_t	x;
	size_t	color = -1;
	size_t	i;
	size_t	j;

	y =  - 1;
	while (++y < data->map.height)
	{
		x = - 1;
		while (++x < data->map.width)
		{
			color = get_color(data->map.content[y][x], (y == (size_t)data->player.pos.y
				&& x == (size_t)data->player.pos.x));
			i = -1;
			while (++i < 10)
			{
				j = -1;
				while (++j < 10)
				{
					img_pixel_put(&data->window.img, x * 10 + j, y * 10 + i, color);
				}
			}
		}
	}
	// printf("%ld %ld\n", x, y);
}
