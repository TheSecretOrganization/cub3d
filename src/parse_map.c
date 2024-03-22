/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:03:57 by abasdere          #+#    #+#             */
/*   Updated: 2024/03/22 10:55:53 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
				cerror(MALLOC_ERROR, collector);
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

static int	parse_player(size_t i, size_t j, t_player *p, const char *line)
{
	if (p->pos.x != 0 && p->pos.y != 0)
		return (1);
	*p = (t_player){{i, j}, {0, 0}};
	if (line[j] == 'S')
		p->view.y = 1;
	else if (line[j] == 'W')
		p->view.x = 1;
	return (0);
}

static void	parse_lines(t_data *data, t_list *line)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	while (line)
	{
		j = -1;
		while (((char *)line->content)[++j])
		{
			if (!ft_strchr(VALID_CHAR, ((char *)line->content)[j]))
				cerror(CHAR_ERROR, data->collector);
			if (ft_strchr(PLAYER_VIEW, ((char *)line->content)[j])
				&& parse_player(i, j, &data->player, (char *)line->content))
				cerror(MULTIPLE_PLAYER, data->collector);
		}
		len = ft_strlen(line->content);
		if (len > data->map.width)
			data->map.width = len;
		i++;
		line = line->next;
	}
	if (data->player.pos.x == 0 && data->player.pos.y == 0)
		cerror(NO_PLAYER, data->collector);
}

void	parse_map(t_data *data, t_list *line)
{
	if (data->map.heigh > 300)
		cerror(MAP_TOO_BIG, data->collector);
	parse_lines(data, line);
	if (data->map.width > 300)
		cerror(MAP_TOO_BIG, data->collector);
	create_rectangle(line, &data->map, data->collector);
	flood_map(&data->map, data->collector);
}
