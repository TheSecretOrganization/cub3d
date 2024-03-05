/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:12:32 by averin            #+#    #+#             */
/*   Updated: 2024/03/05 14:23:53 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_window(t_window *window)
{
	window->mlx = mlx_init();
	if (!window->mlx)
		return (-1);
	window->ptr = mlx_new_window(window->mlx, WIDTH, HEIGHT, "cub3d");
	if (!window->ptr)
		return (free(window->ptr), -1);
	return (0);
}

void	delete_window(t_window *window)
{
	mlx_clear_window(window->mlx, window->ptr);
	mlx_destroy_window(window->mlx, window->ptr);
	mlx_destroy_display(window->mlx);
	free(window->mlx);
	window->mlx = NULL;
	window->ptr = NULL;
}
