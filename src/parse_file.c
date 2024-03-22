/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:56:21 by abasdere          #+#    #+#             */
/*   Updated: 2024/03/22 16:03:11 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define SPACE " \t"

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
		cerror(MAN_TEXTURE_ERROR, NULL, col);
	while (color)
	{
		if (!ft_strncmp("F\0", color->key, 2)
			|| !ft_strncmp("C\0", color->key, 2))
			rules++;
		color = color->next;
	}
	if (rules != 6)
		cerror(MAN_COLOR_ERROR, NULL, col);
}

void	parse_file(t_data *d, const char *argv)
{
	t_list	*file;
	t_list	*line;
	int		found_map;
	int		code;

	file = read_file(argv, d->collector);
	found_map = 0;
	line = NULL;
	while (file)
	{
		code = is_texture((const char *)file->content, found_map);
		if (code == -1)
			cerror(FILE_ERROR, (const char *)file->content, d->collector);
		else if (code == 0 && ++(d->map.heigh))
		{
			found_map = 1;
			if (d->map.heigh == 1)
				line = file;
		}
		else if (code == 1)
			parse_graphic(d, (char *)file->content);
		file = file->next;
	}
	parse_map(d, line);
	check_rules(d->map.graphic.texture, d->map.graphic.color, d->collector);
}
