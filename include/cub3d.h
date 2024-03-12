/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:15:26 by averin            #+#    #+#             */
/*   Updated: 2024/03/11 12:56:02 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include "utils.h"
# include "graphic.h"
# include "window.h"

# include <stdio.h>

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
	char		**map;
	t_player	player;
	t_graphic	graphic;
	size_t		heigh;
	size_t		width;
}	t_map;

typedef struct s_data
{
	t_map		map;
	t_collector	*collector;
	t_window	window;
}	t_data;

void	init_hook(t_data *data);

#endif
