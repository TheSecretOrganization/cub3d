/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 08:57:21 by abasdere          #+#    #+#             */
/*   Updated: 2024/04/18 10:13:19 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define RADIUS 0.3

static int	check_sprite_collision(t_vector player_pos, t_vector sprite_pos)
{
	float	dx;
	float	dy;
	float	d_sqrd;
	float	col_d_sqrd;

	dx = player_pos.x - sprite_pos.x;
	dy = player_pos.y - sprite_pos.y;
	d_sqrd = dx * dx + dy * dy;
	col_d_sqrd = RADIUS * RADIUS;
	return (d_sqrd < col_d_sqrd);
}

static int	check_collision(float x, float y, t_map map, int side)
{
	t_sprite	*s;

	if (map.content[(size_t)y][(size_t)x] == '1'
		|| map.content[(size_t)y][(size_t)x] == '\0')
		return (1);
	if (map.content[(size_t)y][(size_t)x] == 'D' && !is_door_open(x, y, map))
		return (1);
	s = map.graphic.sprite;
	while (s)
	{
		if (!side && check_sprite_collision((t_vector){x, y}, s->pos))
			return (1);
		else if (side && check_sprite_collision((t_vector){y, x}, s->pos))
			return (1);
		s = s->next;
	}
	return (0);
}

void	forward(float step, t_player *player, t_map map)
{
	float	x;
	float	y;

	x = player->pos.x + step * player->direction.x;
	y = player->pos.y + step * player->direction.y;
	if ((size_t)x > map.width || (size_t)y > map.heigh)
		return ;
	if (!check_collision(x, player->pos.y, map, 0))
		player->pos.x = x;
	if (!check_collision(player->pos.x, y, map, 0))
		player->pos.y = y;
}

void	side(int is_left, t_player *player, t_map map)
{
	t_vector	perpendicular;
	float		x;
	float		y;

	if (is_left)
		perpendicular = (t_vector){-player->direction.y, player->direction.x};
	else
		perpendicular = (t_vector){player->direction.y, -player->direction.x};
	x = player->pos.x + STEP * perpendicular.x;
	y = player->pos.y + STEP * perpendicular.y;
	if (!check_collision(x, player->pos.y, map, 1))
		player->pos.x = x;
	if (!check_collision(player->pos.x, y, map, 1))
		player->pos.y = y;
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
