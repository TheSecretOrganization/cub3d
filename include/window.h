/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:14:09 by abasdere          #+#    #+#             */
/*   Updated: 2024/03/14 14:32:45 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include "mlx.h"
# include "collector.h"
# include "utils.h"

# define WIDTH 800
# define HEIGHT 600

typedef struct t_img
{
	void	*ptr;
	char	*content;
	int		bpp;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_window
{
	void	*mlx;
	void	*ptr;
	t_img	img;
}	t_window;

void	create_window(t_window *window, t_collector *col);
void	img_pixel_put(t_img *img, int x, int y, int color);

#endif
