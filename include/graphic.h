/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:15:07 by abasdere          #+#    #+#             */
/*   Updated: 2024/03/22 16:43:48 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHIC_H
# define GRAPHIC_H

# include "window.h"

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

typedef struct s_graphic
{
	t_color		*color;
	t_texture	*texture;
}	t_graphic;

#endif
