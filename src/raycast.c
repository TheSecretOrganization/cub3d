/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:29:25 by averin            #+#    #+#             */
/*   Updated: 2024/04/10 10:36:28 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_raycast(const t_vector *position, t_vector *step,
	t_vector *side, t_vector *delta)
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

static void	conclude_raycast(int face, t_hit *hit, const t_vector *tools)
{
	if (face == 0)
		hit->distance = tools[0].x - tools[1].x;
	else
		hit->distance = tools[0].y - tools[1].y;
	if (face == 0 && tools[2].x >= 0)
		hit->face = EA;
	else if (face == 0 && tools[2].x < 0)
		hit->face = WE;
	else if (face == 1 && tools[2].y >= 0)
		hit->face = SO;
	else
		hit->face = NO;
}

static int	check_collision(t_map map, const int *pos, t_hit *hit, int option)
{
	char	c;

	c = map.content[pos[1]][pos[0]];
	if (c == '\0' || c == '0')
		return (0);
	hit->type = c;
	hit->position.x = pos[0];
	hit->position.y = pos[1];
	if (c == 'D' && (option & R_DOOR || !is_door_open(pos[0], pos[1], map)))
		return (1);
	return (c == '1');
}

/*
 * view { position, direction }
*/
void	raycast(t_vector *view, t_map map, t_hit *hit, int option)
{
	int			face;
	t_vector	step;
	t_vector	side;
	t_vector	delta;

	init_raycast((t_vector [2]){view[0], view[1]}, &step, &side, &delta);
	view[0] = (t_vector){(int)view[0].x, (int)view[0].y};
	while (1)
	{
		if (side.x < side.y)
		{
			side.x += delta.x;
			view[0].x += step.x;
			face = 0;
		}
		else
		{
			side.y += delta.y;
			view[0].y += step.y;
			face = 1;
		}
		if (check_collision(map, (int [2]){view[0].x, view[0].y}, hit, option))
			break ;
	}
	conclude_raycast(face, hit, (t_vector[3]){side, delta, view[1]});
}
