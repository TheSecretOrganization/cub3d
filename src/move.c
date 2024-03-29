/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 08:57:21 by abasdere          #+#    #+#             */
/*   Updated: 2024/03/29 09:05:35 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	forward(float step, t_player *player, t_map map)
{
	size_t	x;
	size_t	y;

	x = (size_t)(player->pos.x + step * player->direction.x);
	y = (size_t)(player->pos.y + step * player->direction.y);
	if (x < 0 || x > map.width || y < 0 || y > map.heigh)
		return ;
	if (!ft_strchr("1\0", map.content[(size_t)player->pos.y][x]))
		player->pos.x += step * player->direction.x;
	if (!ft_strchr("1\0", map.content[y][(size_t)player->pos.x]))
		player->pos.y += step * player->direction.y;
}

void	side(int is_left, t_player *player, t_map map)
{
	t_vector	perpendicular;
	size_t		x;
	size_t		y;

	if (is_left)
		perpendicular = (t_vector){-player->direction.y, player->direction.x};
	else
		perpendicular = (t_vector){player->direction.y, -player->direction.x};
	x = (size_t)(player->pos.x + STEP * perpendicular.x);
	y = (size_t)(player->pos.y + STEP * perpendicular.y);
	if (!ft_strchr("1\0", map.content[(size_t)player->pos.y][x]))
		player->pos.x += STEP * perpendicular.x;
	if (!ft_strchr("1\0", map.content[y][(size_t)player->pos.x]))
		player->pos.y += STEP * perpendicular.y;
}

void	rotate(float v, t_player *player)
{
	float	tmp;

	tmp = player->direction.x;
	player->direction.x = tmp * cos(v) - player->direction.y * sin(v);
	player->direction.y = tmp * sin(v) + player->direction.y * cos(v);
	tmp = player->plane.x;
	player->plane.x = tmp * cos(v) - player->plane.y * sin(v);
	player->plane.y = tmp * sin(v) + player->plane.y * cos(v);
}
