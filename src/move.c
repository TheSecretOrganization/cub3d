/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 08:57:21 by abasdere          #+#    #+#             */
/*   Updated: 2024/04/09 16:52:09 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_collision(char c, int x, int y, t_map map)
{
	if (c == '1' || c == '\0')
		return (1);
	if (c == 'D' && !is_door_open(x, y, map))
		return (1);
	return (0);
}

void	forward(float step, t_player *player, t_map map)
{
	size_t	x;
	size_t	y;

	x = (size_t)(player->pos.x + step * player->direction.x);
	y = (size_t)(player->pos.y + step * player->direction.y);
	if (x > map.width || y > map.heigh)
		return ;
	if (!check_collision(map.content[(size_t)player->pos.y][x],
		x, player->pos.y, map))
		player->pos.x += step * player->direction.x;
	if (!check_collision(map.content[y][(size_t)player->pos.x],
		player->pos.x, y, map))
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
	if (!check_collision(map.content[(size_t)player->pos.y][x],
		player->pos.y, x, map))
		player->pos.x += STEP * perpendicular.x;
	if (!check_collision(map.content[y][(size_t)player->pos.x],
		y, player->pos.x, map))
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
