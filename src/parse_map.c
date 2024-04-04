/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:03:57 by abasdere          #+#    #+#             */
/*   Updated: 2024/04/04 18:08:54 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define DOOR "D"

static void	create_rectangle(t_list *line, t_map *map, t_collector *collector)
{
	char	*tmp;
	size_t	i;
	size_t	len;

	i = 0;
	map->content = ccalloc(map->heigh + 1, sizeof(char *), collector);
	while (line)
	{
		len = ft_strlen((char *)line->content);
		if (len < map->width)
		{
			tmp = ft_calloc(map->width + 1, sizeof(char));
			if (!tmp)
				cerror(MALLOC_ERROR, "create_rectangle", collector);
			ft_memcpy(tmp, (char *)line->content, len);
			(free(line->content), line->content = tmp);
		}
		len = -1;
		while (((char *)line->content)[++len])
			if (((char *)line->content)[len] == ' ')
				((char *)line->content)[len] = '\0';
		map->content[i++] = line->content;
		line = line->next;
	}
}

static int	parse_player(size_t i, size_t j, t_player *p, char *view)
{
	if (p->pos.x != 0 && p->pos.y != 0)
		return (1);
	p->pos.x = j + 0.5;
	p->pos.y = i + 0.5;
	if (*view == 'N')
		rotate(M_PI / 2, p);
	else if (*view == 'S')
		rotate(-M_PI / 2, p);
	else if (*view == 'E')
		rotate(M_PI, p);
	*view = '0';
	return (0);
}

static void	parse_door(t_data *data, size_t i, size_t j)
{
	t_ws	*ws;

	ws = ccalloc(1, sizeof(t_ws), data->collector);
	ws->position = (t_vector){j, i};
	ws->state = CLOSE;
	ws->next = data->map.graphic.wall_state;
	data->map.graphic.wall_state = ws;
}

static void	process_char(t_data *data, char *c, size_t i, size_t j)
{
	if (!ft_strchr(VALID_CHAR, *c))
		cerror(CHAR_ERROR, c, data->collector);
	if (ft_strchr(PLAYER_VIEW, *c)
		&& parse_player(i, j, &data->player, c))
		cerror(MULTIPLE_PLAYER, c, data->collector);
	if (ft_strchr(DOOR, *c))
		parse_door(data, i, j);
}

static void	parse_lines(t_data *d, t_list *l)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	while (l)
	{
		j = -1;
		while (((char *)l->content)[++j])
			process_char(d, &((char *)l->content)[j], i, j);
		len = ft_strlen(l->content);
		if (len > d->map.width)
			d->map.width = len;
		i++;
		l = l->next;
	}
	if (d->player.pos.x == 0 && d->player.pos.y == 0)
		cerror(NO_PLAYER, NULL, d->collector);
}

void	parse_map(t_data *data, t_list *line)
{
	if (data->map.heigh > 300)
		cerror(MAP_TOO_BIG, NULL, data->collector);
	parse_lines(data, line);
	if (data->map.width > 300)
		cerror(MAP_TOO_BIG, NULL, data->collector);
	create_rectangle(line, &data->map, data->collector);
	flood_map(&data->map, data->collector);
}
