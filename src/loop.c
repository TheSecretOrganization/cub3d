/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:45:31 by averin            #+#    #+#             */
/*   Updated: 2024/03/26 18:13:43 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
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

void	move(t_vector v, t_player *player, t_map map)
{
	size_t	x;
	size_t	y;

	x = (size_t)(player->pos.x + v.x * player->direction.x);
	y = (size_t)(player->pos.y + v.x * player->direction.y);
	if (x < 0 || x > map.width || y < 0 || y > map.heigh)
		return ;
	if (!ft_strchr("1\0", map.content[(size_t)player->pos.y][x]))
		player->pos.x += v.x * player->direction.x;
	if (!ft_strchr("1\0", map.content[y][(size_t)player->pos.x]))
		player->pos.y += v.x * player->direction.y;
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
		rotate(0.2f, &data->player);
	if (keycode == XK_Right)
		rotate(-0.2f, &data->player);
	if (keycode == XK_a)
		move((t_vector){0, -0.2f}, &data->player, data->map);
	if (keycode == XK_d)
		move((t_vector){0, 0.2f}, &data->player, data->map);
	if (keycode == XK_w)
		move((t_vector){0.2f, 0}, &data->player, data->map);
	if (keycode == XK_s)
		move((t_vector){-0.2f, 0}, &data->player, data->map);
	printf("%f %f\n", data->player.pos.x, data->player.pos.y);
	print_image(data);
	return (0);
}

void	init_hook(t_data *data)
{
	mlx_hook(data->window.ptr, DestroyNotify, 0, &handle_destroy, data);
	mlx_hook(data->window.ptr, KeyPress, KeyPressMask, &handle_key, data);
	mlx_loop_hook(data->window.mlx, &handle_loop, data);
}
