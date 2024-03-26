/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:12:32 by averin            #+#    #+#             */
/*   Updated: 2024/03/26 13:31:26 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	delete_image(void *win)
{
	t_window	*twin;

	twin = (t_window *)win;
	mlx_destroy_image(twin->mlx, twin->img.ptr);
}

static int	create_img(t_window *win)
{
	win->img.ptr = mlx_new_image(win->mlx, WIDTH, HEIGHT);
	if (!win->img.ptr)
		return (1);
	win->img.content = mlx_get_data_addr(win->img.ptr,
		&win->img.bpp, &win->img.size_line,	&win->img.endian);
	if (!win->img.content)
		return (mlx_destroy_image(win->mlx, win->img.ptr), 1);
	return (0);
}

static void	delete_window(void *window)
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
		cerror(WINDOW_ERROR, "mlx_init", collector);
	window->ptr = mlx_new_window(window->mlx, WIDTH, HEIGHT, "cub3d");
	if (!window->ptr)
		(mlx_destroy_display(window->mlx), free(window->ptr),
			cerror(WINDOW_ERROR, "mlx_new_window", collector));
	add_collector(collector, window, &delete_window);
	give_mlx_priority(collector);
	if (create_img(window))
		cerror("IMAGE_ERROR", "create_window", collector);
	add_collector(collector, window, &delete_image);
}

void	img_pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	pixel = img->content + (y * img->size_line + x * (img->bpp / 8));
	*(int *)pixel = color;
}
