/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:15:07 by abasdere          #+#    #+#             */
/*   Updated: 2024/04/09 16:26:44 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHIC_H
# define GRAPHIC_H

# include "window.h"

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
	t_sprite	*sprite;
	float		zbuffer[WIDTH];
}	t_graphic;

#endif
