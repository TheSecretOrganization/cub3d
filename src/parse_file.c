/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:56:21 by abasdere          #+#    #+#             */
/*   Updated: 2024/03/11 11:10:16 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

#define SPACE " \t"
#define FILE_ERROR "The <file.cub> is invalid"
#define TEXTURE_ERROR "The map doesn't contain all required textures: \
NO, SO, WE and EA"
#define COLOR_ERROR "The map doesn't contain all required colors: F and C"

static int	is_texture(const char *line, int found_map)
{
	size_t	i;
	int		alpha;

	i = 0;
	while (line[i] && ft_strchr(SPACE, line[i]))
		i++;
	if (!line[i] && found_map)
		return (-1);
	if (!line[i])
		return (2);
	alpha = ft_isalpha(line[i]);
	if ((!alpha && !ft_isdigit(line[i])) || (found_map && alpha))
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
	if (rules != 4)
		cerror(TEXTURE_ERROR, col);
	while (color)
	{
		if (!ft_strncmp("F\0", color->key, 2)
			|| !ft_strncmp("C\0", color->key, 2))
			rules++;
		color = color->next;
	}
	if (rules != 6)
		cerror(COLOR_ERROR, col);
}

void	parse_file(t_map *map, const char *argv, t_collector *collector)
{
	t_list	*file;
	t_list	*line;
	int		found_map;
	int		code;

	file = read_file(argv, collector);
	found_map = 0;
	line = NULL;
	while (file)
	{
		code = is_texture((const char *)file->content, found_map);
		if (code == -1)
			cerror(FILE_ERROR, collector);
		else if (code == 0 && ++(map->heigh))
		{
			found_map = 1;
			if (map->heigh == 1)
				line = file;
		}
		else if (code == 1)
			parse_graphic((char *)file->content, &map->graphic, collector);
		file = file->next;
	}
	parse_map(line, map, collector);
	check_rules(map->graphic.texture, map->graphic.color, collector);
}
