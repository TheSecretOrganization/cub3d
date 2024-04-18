/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:26:54 by abasdere          #+#    #+#             */
/*   Updated: 2024/04/18 17:13:48 by abasdere         ###   ########.fr       */
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
	int	y;
	int	x;
	int	color = -1;
    int start_x = (int)data->player.pos.x - 5;
    int start_y = (int)data->player.pos.y - 5;

	y =  - 1;
	while (++y < MINIMAP_HEIGHT)
	{
		x = - 1;
		while (++x < MINIMAP_WIDTH)
		{
			size_t map_x = start_x + x;
            size_t map_y = start_y + y;
			if (map_x >= 0 && map_x < data->map.width && map_y >= 0 && map_y < data->map.height)
			{
				if (color == -1 || !(x % 10))
				{
					// printf("%d %d\n", x, y);
					// printf("%ld %ld\n", map_x, map_y);
					// printf("%c\n", data->map.content[map_y][map_x]);
					color = get_color(data->map.content[map_y][map_x], (map_y == (size_t)data->player.pos.y
						&& map_x == (size_t)data->player.pos.x));
				}
				img_pixel_put(&data->window.img, x, y, color);
			}
		}
	}
}
