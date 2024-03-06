/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:56:21 by abasdere          #+#    #+#             */
/*   Updated: 2024/03/06 16:10:03 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

#define SPACE " \t"
#define MAP_NOT_LAST "The map content always has to be the last element"

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
		// else if (code == 0 && ++found_map)
			// parse map
		else if (code == 1)
			parse_texture((char *)file->content, &map->graphic, collector);
		printf("%s\n", (char *)file->content);
		file = file->next;
	}
}
