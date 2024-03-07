/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:56:21 by abasdere          #+#    #+#             */
/*   Updated: 2024/03/07 11:26:16 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

#define SPACE " \t"
#define MAP_NOT_LAST "The map content always has to be the last element"
#define RULES_ERROR "The map doesn't contain all required graphical elements"

static int	is_texture(const char *line, int found_map)
{
	size_t	i;
	int		alpha;

	i = 0;
	while (line[i] && ft_strchr(SPACE, line[i]))
		i++;
	if (!line[i])
		return (2);
	alpha = ft_isalpha(line[i]);
	if (found_map && alpha)
		return (-1);
	return (alpha);
}

static void	check_rules(t_texure *texture, t_color *color, t_collector *col)
{
	int			rules;

	rules = 0;
	while (texture)
	{
		if (!ft_strncmp("NO\0", texture->key, 3)
			|| !ft_strncmp("SO\0", texture->key, 3)
			|| !ft_strncmp("WE\0", texture->key, 3)
			|| !ft_strncmp("EA\0", texture->key, 3))
			rules++;
		texture = texture->next;
	}
	while (color)
	{
		if (!ft_strncmp("F\0", color->key, 2)
			|| !ft_strncmp("C\0", color->key, 2))
			rules++;
		color = color->next;
	}
	if (rules != 6)
		cerror(RULES_ERROR, col);
}

void	parse_file(t_map *map, const char *argv, t_collector *collector)
{
	t_list	*file;
	int		found_map;
	int		code;

	file = read_file(argv, collector);
	found_map = 0;
	while (file)
	{
		code = is_texture((const char *)file->content, found_map);
		if (code == -1)
			cerror(MAP_NOT_LAST, collector);
		else if (code == 0 && ++found_map)
			;
		else if (code == 1)
			parse_graphic((char *)file->content, &map->graphic, collector);
		file = file->next;
	}
	check_rules(map->graphic.texture, map->graphic.color, collector);
}
