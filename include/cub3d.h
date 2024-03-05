/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:15:26 by averin            #+#    #+#             */
/*   Updated: 2024/03/05 14:24:15 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"

# define WIDTH 600
# define HEIGHT 800

typedef struct s_window
{
	void	*mlx;
	void	*ptr;
}	t_window;

int		create_window(t_window *window);
void	delete_window(t_window *window);

#endif
