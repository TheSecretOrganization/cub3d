/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:45:31 by averin            #+#    #+#             */
/*   Updated: 2024/03/27 16:46:18 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

# define STEP 0.2f

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

void	forward(float step, t_player *player, t_map map)
{
	size_t	x;
	size_t	y;

	x = (size_t)(player->pos.x + step * player->direction.x);
	y = (size_t)(player->pos.y + step * player->direction.y);
	if (x < 0 || x > map.width || y < 0 || y > map.heigh)
		return ;
	if (!ft_strchr("1\0", map.content[(size_t)player->pos.y][x]))
		player->pos.x += step * player->direction.x;
	if (!ft_strchr("1\0", map.content[y][(size_t)player->pos.x]))
		player->pos.y += step * player->direction.y;
}

void	side(int is_left, t_player *player, t_map map)
{
	t_vector perpendicular;
	size_t	x;
	size_t	y;

	if (is_left)
		perpendicular = (t_vector){-player->direction.y, player->direction.x};
	else
		perpendicular = (t_vector){player->direction.y, -player->direction.x};
	x = (size_t)(player->pos.x + STEP * perpendicular.x);
	y = (size_t)(player->pos.y + STEP * perpendicular.y);
	if (!ft_strchr("1\0", map.content[(size_t)player->pos.y][x]))
    	player->pos.x += STEP * perpendicular.x;
	if (!ft_strchr("1\0", map.content[y][(size_t)player->pos.x]))
    	player->pos.y += STEP * perpendicular.y;
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
	print_image(data);
	return (0);
}

void	init_hook(t_data *data)
{
	mlx_hook(data->window.ptr, DestroyNotify, 0, &handle_destroy, data);
	mlx_hook(data->window.ptr, KeyPress, KeyPressMask, &handle_key, data);
	mlx_loop_hook(data->window.mlx, &handle_loop, data);
}
