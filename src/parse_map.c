/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:03:57 by abasdere          #+#    #+#             */
/*   Updated: 2024/03/26 15:19:16 by abasdere         ###   ########.fr       */
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

static int	parse_player(size_t i, size_t j, t_player *p, const char view)
{
	if (p->pos.x != 0 && p->pos.y != 0)
		return (1);
	p->pos.x = j;
	p->pos.y = i;
	if (view == 'N')
		rotate(M_PI / 2, p);
	else if (view == 'S')
		rotate(-M_PI / 2, p);
	else if (view == 'E')
		rotate(M_PI, p);
	return (0);
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
		{
			if (!ft_strchr(VALID_CHAR, ((char *)l->content)[j]))
				cerror(CHAR_ERROR, &(((char *)l->content)[j]), d->collector);
			if (ft_strchr(PLAYER_VIEW, ((char *)l->content)[j])
				&& parse_player(i, j, &d->player, ((char *)l->content)[j]))
				cerror(MULTIPLE_PLAYER, (char *)l->content, d->collector);
		}
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
