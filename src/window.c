/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:12:32 by averin            #+#    #+#             */
/*   Updated: 2024/03/06 10:31:37 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include <stdio.h>

void	delete_window(void *window)
{
	t_window	*w;

	w = (t_window *)window;
	mlx_clear_window(w->mlx, w->ptr);
	mlx_destroy_window(w->mlx, w->ptr);
	mlx_destroy_display(w->mlx);
	free(w->mlx);
	w->mlx = NULL;
	w->ptr = NULL;
}

void	create_window(t_window *window, t_collector *collector)
{
	window->mlx = mlx_init();
	if (!window->mlx)
		cerror("Cannot open window", collector);
	window->ptr = mlx_new_window(window->mlx, WIDTH, HEIGHT, "cub3d");
	if (!window->ptr)
		(mlx_destroy_display(window->mlx), free(window->ptr),
			cerror("Cannot open window", collector));
	add_collector(collector, window, &delete_window);
	give_mlx_priority(collector);
}
