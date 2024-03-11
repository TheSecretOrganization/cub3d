/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:14:09 by abasdere          #+#    #+#             */
/*   Updated: 2024/03/11 10:46:53 by averin           ###   ########.fr       */
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
	void	*addr;
	char	*content;
	int		bpp;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_window
{
	void	*mlx;
	void	*ptr;
	t_img	image;
}	t_window;

typedef struct s_data
{
	t_window	*window;
	float		*pos;
}	t_data;

void	create_window(t_window *window, t_collector *col);

#endif
