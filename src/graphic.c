/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:35:32 by abasdere          #+#    #+#             */
/*   Updated: 2024/04/09 18:58:10 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static void	add_color(t_data *data, const char *k, const char *v)
{
	t_color	*new;
	t_color	*last;
	char	**split;

	if (check_commas(v) != 2)
		cerror(EL_ERROR, v, data->collector);
	new = ccalloc(1, sizeof(t_color), data->collector);
	new->key = k;
	new->next = NULL;
	split = ft_split(v, ',');
	if (!split)
		cerror(MALLOC_ERROR, "add_color", data->collector);
	(split_atoi(split, new, data->collector, v), ft_fsplit(split));
	if (!data->map.graphic.color)
		data->map.graphic.color = new;
	else
	{
		last = data->map.graphic.color;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

static void	check_keys(t_data *data, const char *k)
{
	t_graphic	cpy;

	if (k[1] && !ft_isalpha(k[1]))
		cerror(KEY_ERROR, k, data->collector);
	cpy = (t_graphic){data->map.graphic.color, data->map.graphic.texture,
		data->map.graphic.wall_state, data->map.graphic.sprite, {0}};
	while (cpy.color || cpy.texture || cpy.sprite)
	{
		if ((cpy.color && !ft_strncmp(cpy.color->key, k, ft_strlen(k)))
			|| (cpy.texture && !ft_strncmp(cpy.texture->key, k, ft_strlen(k)))
			|| (cpy.sprite && !ft_strncmp(cpy.sprite->key, k, ft_strlen(k))))
			cerror(UNIQUE_KEY_ERROR, k, data->collector);
		if (cpy.color)
			cpy.color = cpy.color->next;
		if (cpy.texture)
			cpy.texture = cpy.texture->next;
		if (cpy.sprite)
			cpy.sprite = cpy.sprite->next;
	}
}

static void	dispatch(t_data *data, const char **kvsp)
{
	size_t		l;

	(check_keys(data, kvsp[0]), l = ft_strlen(kvsp[1]));
	if (kvsp[2] && l >= 4 && kvsp[1][l - 4] == '.' && kvsp[1][l - 3] == 'x'
		&& kvsp[1][l - 2] == 'p' && kvsp[1][l - 1] == 'm')
		add_sprite(data, kvsp);
	else if (kvsp[2])
		cerror(NB_ERROR, kvsp[0], data->collector);
	else if (l >= 4 && kvsp[1][l - 4] == '.' && kvsp[1][l - 3] == 'x'
		&& kvsp[1][l - 2] == 'p' && kvsp[1][l - 1] == 'm')
		add_text(data, kvsp[0], kvsp[1]);
	else
		add_color(data, kvsp[0], kvsp[1]);
}

void	parse_graphic(t_data *data, char *line)
{
	size_t		i;
	char		**split;
	const char	*kvsp[4];

	(replace_char(line, '\t', ' '), i = -1);
	split = ft_split(line, ' ');
	if (!split)
		cerror(MALLOC_ERROR, "parse_graphic", data->collector);
	while (split[++i])
		;
	if (i != 2 && i != 4)
		(ft_fsplit(split), cerror(NB_ERROR, line, data->collector));
	(add_collector(data->collector, split[0], &free), kvsp[0] = split[0]);
	(add_collector(data->collector, split[1], &free), kvsp[1] = split[1]);
	if (i == 4)
	{
		(add_collector(data->collector, split[2], &free), kvsp[2] = split[2]);
		(add_collector(data->collector, split[3], &free), kvsp[3] = split[3]);
	}
	else
		kvsp[2] = NULL;
	(free(split[i]), free(split), dispatch(data, kvsp));
}
