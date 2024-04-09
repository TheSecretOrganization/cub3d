/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:41:32 by averin            #+#    #+#             */
/*   Updated: 2024/04/09 17:00:02 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_ws	*get_wall_state(int x, int y, t_map map)
{
	t_ws	*ws;

	ws = map.graphic.wall_state;
	while (ws)
	{
		if (((int)ws->position.x) == x && ((int)ws->position.y) == y)
			return (ws);
		ws = ws->next;
	}
	return (NULL);
}

int	is_door_open(int x, int y, t_map map)
{
	const t_ws	*ws;

	ws = get_wall_state(x, y, map);
	if (!ws)
		return (0);
	return (ws->state == OPEN);
}

void	close_door(t_player player, t_map map)
{
	t_hit	hit;
	t_ws	*ws;

	raycast((t_vector [2]){player.pos, player.direction}, map, &hit, R_DOOR);
	if (hit.type == 'D' && hit.distance <= 1)
	{
		ws = get_wall_state(hit.position.x, hit.position.y, map);
		ws->state = !ws->state;
	}
}
