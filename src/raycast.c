/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:29:25 by averin            #+#    #+#             */
/*   Updated: 2024/03/29 10:17:29 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_raycast(t_vector *position, t_vector *step, t_vector *side,
	t_vector *delta)
{
	*delta = (t_vector){1e30, 1e30};
	if (position[1].x != 0)
		delta->x = fabs(1 / position[1].x);
	if (position[1].y != 0)
		delta->y = fabs(1 / position[1].y);
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
	if (position[1].y < 0)
	{
		step->y = -1;
		side->y = (position[0].y - (int) position[0].y) * delta->y;
	}
	else
	{
		step->y = 1;
		side->y = ((int) position[0].y + 1.0f - position[0].y) * delta->y;
	}
}

static void	conclude_raycast(int face, t_hit *hit, t_vector *tools)
{
	if (face == 0)
		hit->distance = tools[0].x - tools[1].x;
	else
		hit->distance = tools[0].y - tools[1].y;
	if (face == 0 && tools[2].x >= 0)
		hit->face = NO;
	else if (face == 0 && tools[2].x < 0)
		hit->face = SO;
	else if (face == 1 && tools[2].y >= 0)
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
		if (map.content[(int)position.y][(int)position.x] == '1')
			break ;
	}
	conclude_raycast(face, hit, (t_vector[3]){side, delta, direction});
}
