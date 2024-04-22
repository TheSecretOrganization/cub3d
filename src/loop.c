/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:45:31 by averin            #+#    #+#             */
/*   Updated: 2024/04/22 09:27:16 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define ON_MOUSEMOVE 6

static int	handle_loop(t_data *data)
{
	print_image(data);
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
		rotate(-STEP, &data->player);
	if (keycode == XK_Right)
		rotate(STEP, &data->player);
	if (keycode == XK_a)
		side(0, &data->player, data->map);
	if (keycode == XK_d)
		side(1, &data->player, data->map);
	if (keycode == XK_w)
		forward(STEP, &data->player, data->map);
	if (keycode == XK_s)
		forward(-STEP, &data->player, data->map);
	if (keycode == XK_e)
		close_door(data->player, data->map);
	if (keycode == XK_m)
		data->controls ^= C_MINIMAP;
	return (0);
}

static int	handle_mouse(int x, int new_x, t_data *data)
{
	(void)data;
	if (x > WIDTH / 2 + 20)
		(rotate(-STEP / 4, &data->player), new_x = WIDTH / 2 + 19);
	else if (x < WIDTH / 2 - 20)
		(rotate(STEP / 4, &data->player), new_x = WIDTH / 2 - 19);
	else
		return (0);
	print_image(data);
	if (x > WIDTH / 2 + 10)
		mlx_mouse_move(data->window.mlx, data->window.ptr, new_x, HEIGHT / 2);
	else if (x < WIDTH / 2 - 10)
		mlx_mouse_move(data->window.mlx, data->window.ptr, new_x, HEIGHT / 2);
	return (0);
}

void	init_hook(t_data *data)
{
	mlx_hook(data->window.ptr, DestroyNotify, 0, &handle_destroy, data);
	mlx_hook(data->window.ptr, KeyPress, KeyPressMask, &handle_key, data);
	mlx_hook(data->window.ptr, 6, 1L << 6, &handle_mouse, data);
	mlx_loop_hook(data->window.mlx, &handle_loop, data);
}
