/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:12:32 by averin            #+#    #+#             */
/*   Updated: 2024/03/05 22:48:04 by abasdere         ###   ########.fr       */
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
		(free_collector(collector), error("Cannot open window"));
	window->ptr = mlx_new_window(window->mlx, WIDTH, HEIGHT, "cub3d");
	if (!window->ptr)
		(mlx_destroy_display(window->mlx), free(window->ptr),
			free_collector(collector), error("Cannot open window"));
	add_collector(collector, window, &delete_window);
	give_mlx_priority(collector);
}
