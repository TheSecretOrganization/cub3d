/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:29:25 by averin            #+#    #+#             */
/*   Updated: 2024/03/28 12:26:02 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Init raycast variables
 * 
 * @param position array containing position and direction
 */
static void	init_raycast(t_vector *position, t_vector *step, t_vector *side,
	t_vector *delta)
{
	*delta = (t_vector){ft_abs(1 / position[1].x), ft_abs(1 / position[1].y)};
	if (position[0].x == 0)
		delta->x = 1e30;
	if (position[0].y == 0)
		delta->y = 1e30;
	if (position[1].x < 0)
	{
		step->x = -1;
		side->x = (position[0].x - (int) position[0].x) * delta->x;
	}
	else
	{
		step->x = 1;
		side->x = ((int) position[0].x + 1.0f - position[0].x) * delta->x;
	}
	if (position[1].y)
	{
		step->y = -1;
		side->y = (position[0].y - (int) position[0].y) * delta->y;
	}
	else
	{
		step->y = 1;
		side->y = ((int) position[0].y + 1.0f - position[0].y) - delta->y;
	}
}

void	conclude_raycast(int face, t_hit *hit, t_vector side, t_vector delta,
	t_vector direction)
{
	if (face == 0)
		hit->distance = side.x - delta.x;
	else
		hit->distance = side.y - delta.y;
	if (face == 0 && direction.x >= 0)
		hit->face = NO;
	else if (face == 0 && direction.x < 0)
		hit->face = SO;
	else if (face == 1 && direction.y >= 0)
		hit->face = EA;
	else
		hit->face = WE;
}

void	raycast(t_vector position, t_vector direction, t_map map, t_hit *hit)
{
	int			face;
	t_vector	step;
	t_vector	side;
	t_vector	delta;

	init_raycast((t_vector [2]){position, direction}, &step, &side, &delta);
	position = (t_vector){(int)position.x, (int)position.y};
	while (1)
	{
		if (side.x < side.y)
		{
			side.x += delta.x;
			position.x += step.x;
			face = 0;
		}
		else
		{
			side.y += delta.y;
			position.y += step.y;
			face = 1;
		}
		if (map.content[(int)position.y][(int)position.x] == '1') break;
	}
	conclude_raycast(face, hit, side, delta, direction);
}
