/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:03:57 by abasdere          #+#    #+#             */
/*   Updated: 2024/03/07 13:58:49 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

#define VALID_CHAR "10NSEW "
#define PLAYER_VIEW "NSEW"
#define CHAR_ERROR "Invalid char found in the map"
#define MULTIPLE_PLAYER "Multiple starting player postion found"
#define MALLOC_ERROR "Malloc failed"

static void	create_rectangle(t_list *line, t_map *map, t_collector *collector)
{
	char	*tmp;
	size_t	i;
	size_t	len;

	i = 0;
	map->map = ccalloc(map->heigh + 1, sizeof(char *), collector);
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
		map->map[i++] = line->content;
		line = line->next;
	}
}

static int	parse_player(size_t i, size_t j, t_map *map, char *line)
{
	if (map->player.pos.x != 0 && map->player.pos.y != 0)
		return (1);
	map->player = (t_player){{i, j}, {0, 0}};
	if (line[j] == 'S')
		map->player.view.y = 1;
	else if (line[j] == 'W')
		map->player.view.x = 1;
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
			if (ft_strchr(PLAYER_VIEW, ((char *)line->content)[j]))
				if (parse_player(i, j, map, (char *)line->content))
					cerror(MULTIPLE_PLAYER, collector);
		}
		len = ft_strlen(line->content);
		if (len > map->width)
			map->width = len;
		(i++, line = line->next);
	}
}

void	parse_map(t_list *line, t_map *map, t_collector *collector)
{
	parse_lines(line, map, collector);
	create_rectangle(line, map, collector);
	for (size_t i = 0; map->map[i]; i++)
	{
		write(1, map->map[i], map->width);
		write(1, "\n", 1);
	}
}
