/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:45:31 by averin            #+#    #+#             */
/*   Updated: 2024/03/23 14:01:10 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <X11/keysym.h>
#include <X11/X.h>
#include <math.h>

static int	handle_loop(t_data *data)
{
	(void) data;
	// print_image(data);
	return (0);
}

static int	handle_destroy(t_data *data)
{
	mlx_loop_end(data->window.mlx);
	return (0);
}

void	move(t_vector v, t_player *player)
{
	player->pos.x += player->direction.x * v.x;
	player->pos.y += player->direction.y * v.y;
}

void	rotate(float v, t_player *player)
{
	float olddx = player->direction.x;
	player->direction.x = olddx * cos(v) - player->direction.y * sin(v);
	player->direction.y = olddx * sin(v) + player->direction.y * cos(v);
	float oldpx = player->plane.x;
	player->plane.x = oldpx * cos(v) - player->plane.y * sin(v);
	player->plane.y = oldpx * sin(v) + player->plane.y * cos(v);
}

static int	handle_key(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		handle_destroy(data);
	if (keycode == XK_Left)
		rotate(0.2f, &data->map.player);
	if (keycode == XK_Right)
		rotate(-0.2f, &data->map.player);
	if (keycode == XK_a)
		move((t_vector){0, -0.2f}, &data->map.player);
	if (keycode == XK_d)
		move((t_vector){0, 0.2f}, &data->map.player);
	if (keycode == XK_w)
		move((t_vector){0.2f, 0}, &data->map.player);
	if (keycode == XK_s)
		move((t_vector){-0.2f, 0}, &data->map.player);
	printf("%f %f\n", data->map.player.pos.x, data->map.player.pos.y);
	print_image(data);
	return (0);
}

void	init_hook(t_data *data)
{
	mlx_hook(data->window.ptr, DestroyNotify, 0, &handle_destroy, data);
	mlx_hook(data->window.ptr, KeyPress, KeyPressMask, &handle_key, data);
	mlx_loop_hook(data->window.mlx, &handle_loop, data);
}
