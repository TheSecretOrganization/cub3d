/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:15:07 by abasdere          #+#    #+#             */
/*   Updated: 2024/04/19 15:55:47 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHIC_H
# define GRAPHIC_H

# include "window.h"

# define OPEN 1
# define CLOSE 0

typedef struct s_vector
{
	float	x;
	float	y;
}	t_vector;

typedef struct s_color
{
	const char		*key;
	int				red;
	int				green;
	int				blue;
	struct s_color	*next;
}	t_color;

typedef struct s_texture
{
	const char			*key;
	t_img				img;
	void				*mlx;
	struct s_texture	*next;
}	t_texture;

typedef struct s_ws
{
	t_vector	position;
	int			state;
	struct s_ws	*next;
}	t_ws;

typedef struct s_sprite
{
	const char		*key;
	t_vector		pos;
	float			distance;
	t_img			img;
	void			*mlx;
	struct s_sprite	*next;
}	t_sprite;

typedef struct s_graphic
{
	t_color		*color;
	t_texture	*texture;
	t_ws		*wall_state;
	t_sprite	*sprite;
	float		zbuffer[WIDTH + 1];
}	t_graphic;

#endif
