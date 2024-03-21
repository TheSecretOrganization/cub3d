/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:03:57 by abasdere          #+#    #+#             */
/*   Updated: 2024/03/21 10:36:30 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "window.h"

#define VALID_CHAR "10NSEW "
#define PLAYER_VIEW "NSEW"
#define CHAR_ERROR "Invalid char found in the map"
#define NO_PLAYER "No starting position was found"
#define MULTIPLE_PLAYER "Multiple starting position found"
#define MAP_TOO_BIG "The map is too big, a 300x300 is the maximum"
#define MALLOC_ERROR "Malloc failed"

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

static int	parse_player(size_t i, size_t j, t_map *map, const char *line)
{
	if (map->player.pos.x != 0 && map->player.pos.y != 0)
		return (1);
	map->player.pos.x = j;
	map->player.pos.y = i;
	(void) line;
	// if (line[j] == 'E')
	// 	map->player.dir = 0;
	// else if (line[j] == 'N')
	// 	map->player.dir = 90;
	// else if (line[j] == 'S')
	// 	map->player.dir = 270;
	// else if (line[j] == 'W')
	// 	map->player.dir = 180;
	return (0);
}

static void	parse_lines(t_list *line, t_map *map, t_collector *collector)
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
				cerror(CHAR_ERROR, collector);
			if (ft_strchr(PLAYER_VIEW, ((char *)line->content)[j])
				&& parse_player(i, j, map, (char *)line->content))
				cerror(MULTIPLE_PLAYER, collector);
		}
		len = ft_strlen(line->content);
		if (len > map->width)
			map->width = len;
		i++;
		line = line->next;
	}
	if (map->player.pos.x == 0 && map->player.pos.y == 0)
		cerror(NO_PLAYER, collector);
}

void	parse_map(t_list *line, t_map *map, t_collector *collector)
{
	if (map->heigh > 300)
		cerror(MAP_TOO_BIG, collector);
	parse_lines(line, map, collector);
	if (map->width > 300)
		cerror(MAP_TOO_BIG, collector);
	create_rectangle(line, map, collector);
	flood_map(map, collector);
}
