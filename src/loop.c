/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:45:31 by averin            #+#    #+#             */
/*   Updated: 2024/03/12 11:48:04 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <X11/keysym.h>
#include <X11/X.h>

static int	handle_loop(t_data *data)
{
	(void) data;
	return (0);
}

static int	handle_key(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		handle_destroy(data);
	if (keycode == XK_Left)
		data->map.player.view.x += 0.2;
	if (keycode == XK_Right)
		data->map.player.view.x -= 0.2;
	if (keycode == XK_a)
		data->map.player.pos.y -= 0.2;
	if (keycode == XK_d)
		data->map.player.pos.y += 0.2;
	if (keycode == XK_w)
		data->map.player.pos.x += 0.2;
	if (keycode == XK_s)
		data->map.player.pos.x -= 0.2;
	return (0);
}

static int	handle_destroy(t_data *data)
{
	mlx_loop_end(data->window.mlx);
	free_collector(data->collector);
	return (0);
}

void	init_hook(t_data *data)
{
	mlx_hook(data->window.ptr, DestroyNotify, 0, handle_destroy, data);
	mlx_hook(data->window.ptr, KeyPress, KeyPressMask, handle_key, data);
	mlx_loop_hook(data->window.mlx, handle_loop, data);
}
