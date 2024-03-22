/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:15:26 by averin            #+#    #+#             */
/*   Updated: 2024/03/22 10:57:05 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include "collector.h"
# include "error.h"
# include "graphic.h"
# include "window.h"

# include <stdio.h>
# include <sys/types.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <X11/keysym.h>
# include <X11/X.h>

typedef struct s_vector
{
	float	x;
	float	y;
}	t_vector;

typedef struct s_player
{
	t_vector	pos;
	t_vector	view;
}	t_player;

typedef struct s_map
{
	char		**content;
	t_graphic	graphic;
	size_t		heigh;
	size_t		width;
}	t_map;

typedef struct s_data
{
	t_map		map;
	t_player	player;
	t_collector	*collector;
	t_window	window;
}	t_data;

void		init_hook(t_data *data);

void		cerror(char *message, t_collector *collector);
void		error(char *message);

t_collector	*init_collector(void);
void		free_collector(t_collector *col);
void		*add_collector(t_collector *col, void *el, void (*f)(void *));
void		give_mlx_priority(t_collector *collector);
void		*ccalloc(size_t nmemb, size_t size, t_collector *col);

void		create_window(t_window *window, t_collector *col);

void		parse_graphic(char *line, t_graphic *graphic,
				t_collector *collector);
void		remove_space(char *line);
size_t		check_commas(const char *value);

t_list		*read_file(const char *file, t_collector *collector);
void		parse_file(t_data *data, const char *argv);
void		parse_map(t_data *data, t_list *line);
void		flood_map(const t_map *map, t_collector *collector);

#endif
