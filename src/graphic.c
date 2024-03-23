/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:35:32 by abasdere          #+#    #+#             */
/*   Updated: 2024/03/22 13:56:53 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	add_text(t_texure **t, const char *k, const char *v, t_collector *c)
{
	t_texure	*new;
	t_texure	*last;
	int			fd;

	fd = open(v, O_RDONLY);
	if (fd == -1)
		cerror(TEXTURE_ERROR, v, c);
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

static void	split_atoi(char **s, t_color *new, t_collector *col, const char *v)
{
	char	*tmp;
	size_t	i;
	int		number;

	i = -1;
	while (s[++i])
	{
		if (i > 2)
			(ft_fsplit(s), cerror(EL_ERROR, v, col));
		number = ft_atoi(s[i]);
		tmp = ft_itoa(number);
		if (!tmp)
			(ft_fsplit(s), cerror(MALLOC_ERROR, "split_atoi", col));
		if (ft_strncmp(tmp, s[i], ft_strlen(tmp)))
			(free(tmp), ft_fsplit(s), cerror(COLOR_ERROR, v, col));
		free(tmp);
		if (number < 0 || number > 255)
			(ft_fsplit(s), cerror(COLOR_ERROR, v, col));
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
		cerror(EL_ERROR, v, c);
	new = ccalloc(1, sizeof(t_color), c);
	new->key = k;
	new->next = NULL;
	split = ft_split(v, ',');
	if (!split)
		cerror(MALLOC_ERROR, "add_color", c);
	(split_atoi(split, new, c, v), ft_fsplit(split));
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
		cerror(KEY_ERROR, k, c);
	cpy = (t_graphic){g->color, g->texture};
	while (cpy.color || cpy.texture)
	{
		if ((cpy.color && !ft_strncmp(cpy.color->key, k, ft_strlen(k)))
			|| (cpy.texture && !ft_strncmp(cpy.texture->key, k, ft_strlen(k))))
			cerror(UNIQUE_KEY_ERROR, k, c);
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
		cerror(MALLOC_ERROR, "parse_graphic", collector);
	i = -1;
	while (split[++i])
		;
	if (i != 2)
		(ft_fsplit(split), cerror(NB_ERROR, line, collector));
	(add_collector(collector, split[0], &free), key = split[0]);
	(add_collector(collector, split[1], &free), value = split[1]);
	(free(split[2]), free(split));
	dispatch(graphic, key, value, collector);
}
