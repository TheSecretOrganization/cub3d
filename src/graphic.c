/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:35:32 by abasdere          #+#    #+#             */
/*   Updated: 2024/03/11 11:04:37 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphic.h"
#include "parsing.h"
#include "utils.h"

#define MALLOC_ERROR "Malloc failed"
#define NB_ERROR "There must be one key value couple by element"
#define KEY_ERROR "Element key is invalid: \
It must be a one to two char long alphabetical string"
#define UNIQUE_KEY_ERROR "Element key is invalid: each key must be unique"
#define EL_ERROR "Element value is invalid: \
It must be either a path to <texture.xpm> or a <R,G,B> color"
#define COLOR_ERROR "Color's must be compose by three integer, \
there value must be between 0 and 255"
#define TEXTURE_ERROR "Texture couldn't be loaded"

static void	add_text(t_texure **t, const char *k, const char *v, t_collector *c)
{
	t_texure	*new;
	t_texure	*last;
	int			fd;

	fd = open(v, O_RDONLY);
	if (fd == -1)
		cerror(TEXTURE_ERROR, c);
	close(fd);
	new = ccalloc(1, sizeof(t_texure), c);
	new->key = k;
	new->value = v;
	new->next = NULL;
	if (!*t)
		*t = new;
	else
	{
		last = *t;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

static void	split_atoi(char **split, t_color *new, t_collector *collector)
{
	char	*tmp;
	size_t	i;
	int		number;

	i = -1;
	while (split[++i])
	{
		if (i > 2)
			(ft_fsplit(split), cerror(EL_ERROR, collector));
		number = ft_atoi(split[i]);
		tmp = ft_itoa(number);
		if (!tmp)
			(ft_fsplit(split), cerror(MALLOC_ERROR, collector));
		if (ft_strncmp(tmp, split[i], ft_strlen(tmp)))
			(free(tmp), ft_fsplit(split), cerror(COLOR_ERROR, collector));
		free(tmp);
		if (number < 0 || number > 255)
			(ft_fsplit(split), cerror(COLOR_ERROR, collector));
		if (i == 0)
			new->red = number;
		else if (i == 1)
			new->blue = number;
		else
			new->green = number;
	}
}

static void	add_color(t_color **x, const char *k, const char *v, t_collector *c)
{
	t_color	*new;
	t_color	*last;
	char	**split;

	if (check_commas(v) != 2)
		cerror(EL_ERROR, c);
	new = ccalloc(1, sizeof(t_color), c);
	new->key = k;
	new->next = NULL;
	split = ft_split(v, ',');
	if (!split)
		cerror(MALLOC_ERROR, c);
	(split_atoi(split, new, c), ft_fsplit(split));
	if (!*x)
		*x = new;
	else
	{
		last = *x;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

static void	dispatch(t_graphic *g, const char *k, const char *v, t_collector *c)
{
	size_t		len;
	t_graphic	cpy;

	if (k[1] && !ft_isalpha(k[1]))
		cerror(KEY_ERROR, c);
	cpy = (t_graphic){g->color, g->texture};
	while (cpy.color || cpy.texture)
	{
		if ((cpy.color && !ft_strncmp(cpy.color->key, k, ft_strlen(k)))
			|| (cpy.texture && !ft_strncmp(cpy.texture->key, k, ft_strlen(k))))
			cerror(UNIQUE_KEY_ERROR, c);
		if (cpy.color)
			cpy.color = cpy.color->next;
		if (cpy.texture)
			cpy.texture = cpy.texture->next;
	}
	len = ft_strlen(v);
	if (len >= 4 && v[len - 4] == '.' && v[len - 3] == 'x' && v[len - 2] == 'p'
		&& v[len - 1] == 'm')
		add_text(&g->texture, k, v, c);
	else
		add_color(&g->color, k, v, c);
}

void	parse_graphic(char *line, t_graphic *graphic, t_collector *collector)
{
	size_t		i;
	char		**split;
	const char	*key;
	const char	*value;

	i = -1;
	while (line[++i])
		if (line[i] == '\t')
			line[i] = ' ';
	if (!ft_strnstr(line, ".xpm", ft_strlen(line)))
		remove_space(line);
	split = ft_split(line, ' ');
	if (!split)
		cerror(MALLOC_ERROR, collector);
	i = -1;
	while (split[++i])
		;
	if (i != 2)
		(ft_fsplit(split), cerror(NB_ERROR, collector));
	(add_collector(collector, split[0], &free), key = split[0]);
	(add_collector(collector, split[1], &free), value = split[1]);
	(free(split[2]), free(split));
	dispatch(graphic, key, value, collector);
}
