/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:15:26 by averin            #+#    #+#             */
/*   Updated: 2024/03/07 13:32:59 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include "utils.h"
# include "window.h"

# include <stdio.h>

typedef struct s_vec2
{
	float	x;
	float	y;
}	t_vec2;

void	draw_line(t_vec2 a, t_vec2 b, int color, t_img *img);
void	img_pixel_put(t_img *img, int x, int y, int color);

#endif
