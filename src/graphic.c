/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:35:32 by abasdere          #+#    #+#             */
/*   Updated: 2024/03/06 16:09:35 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphic.h"
#include "parsing.h"
#include "utils.h"

#define MALLOC_ERROR "Malloc failed"
#define NB_PATH_ERROR "There must be one path by texture"
#define KEY_ERROR "Element key is invalid, \
it must be a one or two char long alphabetical string"

static void	add_texture(t_texure **tex, char *k, char *v, t_collector *col)
{
	t_texure	*new;
	t_texure	*last;

	new = ccalloc(1, sizeof(t_texure), col);
	new->key = k;
	new->value = v;
	new->next = NULL;
	if (!*tex)
		*tex = new;
	else
	{
		last = *tex;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

static void	check_texture(const char *key, const char *value, t_collector *col)
{
	if (key[1] && !ft_isalpha(key[1]))
		cerror(KEY_ERROR, col);
	check_suffix(value, ".xpm", col);
}

void	parse_texture(char *line, t_graphic **graphic, t_collector *collector)
{
	size_t	i;
	char	**split;
	char	*key;
	char	*value;

	i = -1;
	while (line[++i])
		if (line[i] == '\t')
			line[i] = ' ';
	split = ft_split(line, ' ');
	if (!split)
		cerror(MALLOC_ERROR, collector);
	i = -1;
	while (split[++i])
		;
	if (i != 2)
		(ft_fsplit(split), cerror(NB_PATH_ERROR, collector));
	(add_collector(collector, split[0], &free), key = split[0]);
	(add_collector(collector, split[1], &free), value = split[1]);
	(free(split[2]), free(split));
	check_texture(key, value, collector);
	add_texture(graphic, key, value, collector);
}
