/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:14:09 by abasdere          #+#    #+#             */
/*   Updated: 2024/03/22 16:49:39 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include "mlx.h"

# define WIDTH 800
# define HEIGHT 600

typedef struct t_img
{
	void	*ptr;
	char	*content;
	int		bpp;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_window
{
	void	*mlx;
	void	*ptr;
}	t_window;

#endif
