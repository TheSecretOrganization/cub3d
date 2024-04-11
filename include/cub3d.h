/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:15:26 by averin            #+#    #+#             */
/*   Updated: 2024/04/10 11:46:35 by abasdere         ###   ########.fr       */
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
# include <math.h>

# define STEP 0.2f
# define VALID_CHAR "10NSEWD "
# define PLAYER_VIEW "NSEW"
# define R_DOOR 1

typedef struct s_player
{
	t_vector	pos;
	t_vector	plane;
	t_vector	direction;
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

typedef enum e_dir
{
	EA,
	WE,
	NO,
	SO
}	t_dir;

typedef struct s_hit
{
	float		distance;
	t_vector	position;
	t_dir		face;
	char		type;
}	t_hit;

void		init_hook(t_data *data);

void		cerror(const char *message, const char *el, t_collector *collector);
void		error(const char *message, const char *el);
float		rad(float deg);
t_img		*search_texture(const char *name, t_map map);
int			search_color(const char *name, t_map map);

t_collector	*init_collector(void);
void		free_collector(t_collector *col);
void		*add_collector(t_collector *col, void *el, void (*f)(void *));
void		give_mlx_priority(t_collector *collector);
void		*ccalloc(size_t nmemb, size_t size, t_collector *col);

void		create_window(t_window *window, t_collector *col);

void		parse_graphic(t_data *data, char *line);
size_t		check_commas(const char *value);
void		replace_char(char *s, char target, char replace);
void		add_text(t_data *data, const char *k, const char *v);
void		add_sprite(t_data *data, const char **kvsp);
void		check_sprite_free_space(t_data *data);
t_sprite	*check_sprite_pos(t_sprite *sprite, t_vector pos);

t_list		*read_file(const char *file, t_collector *collector);
void		parse_file(t_data *data, const char *argv);
void		parse_map(t_data *data, t_list *line);
void		flood_map(const t_map *map, t_collector *collector);

void		print_image(t_data *data);
int			get_pixel(t_img *tex, int x, int y);
void		img_pixel_put(t_img *img, int x, int y, int color);
void		spritecasting(t_data *data);
void		sort_sprites(t_sprite **sprites, t_vector pos);

void		forward(float step, t_player *player, t_map map);
void		side(int is_left, t_player *player, t_map map);
void		rotate(float v, t_player *player);

void		raycast(t_vector *view, t_map map, t_hit *hit, int option);

t_ws		*get_wall_state(int x, int y, t_map map);
int			is_door_open(int x, int y, t_map map);
void		close_door(t_player player, t_map map);

void		print_image(t_data *data);

void		create_rectangle(t_list *line, t_map *map, t_collector *collector);

#endif
