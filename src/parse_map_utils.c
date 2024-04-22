/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:56:13 by averin            #+#    #+#             */
/*   Updated: 2024/04/18 14:57:23 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_rectangle(t_list *line, t_map *map, t_collector *collector)
{
	char	*tmp;
	size_t	i;
	size_t	len;

	i = 0;
	map->content = ccalloc(map->height + 1, sizeof(char *), collector);
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
		replace_char(((char *)line->content), ' ', '1');
		map->content[i++] = line->content;
		line = line->next;
	}
}
