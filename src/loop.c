/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:45:31 by averin            #+#    #+#             */
/*   Updated: 2024/04/04 18:39:38 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	handle_loop(t_data *data)
{
	(void) data;
	return (0);
}

static int	handle_destroy(t_data *data)
{
	mlx_loop_end(data->window.mlx);
	return (0);
}

static int	handle_key(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		handle_destroy(data);
	if (keycode == XK_Left)
		rotate(STEP, &data->player);
	if (keycode == XK_Right)
		rotate(-STEP, &data->player);
	if (keycode == XK_a)
		side(1, &data->player, data->map);
	if (keycode == XK_d)
		side(0, &data->player, data->map);
	if (keycode == XK_w)
		forward(STEP, &data->player, data->map);
	if (keycode == XK_s)
		forward(-STEP, &data->player, data->map);
	if (keycode == XK_e)
		close_door(data->player, data->map);
	print_image(data);
	return (0);
}

void	init_hook(t_data *data)
{
	mlx_hook(data->window.ptr, DestroyNotify, 0, &handle_destroy, data);
	mlx_hook(data->window.ptr, KeyPress, KeyPressMask, &handle_key, data);
	mlx_loop_hook(data->window.mlx, &handle_loop, data);
}
