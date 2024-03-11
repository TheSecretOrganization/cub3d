/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:52:38 by averin            #+#    #+#             */
/*   Updated: 2024/03/11 10:53:30 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "collector.h"
#include "window.h"
#include "math.h"
#include <X11/keysym.h>
#include <X11/X.h>

int map[10][10] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};
int	width = 10;
int	height = 10;

void	create_img(t_window *window)
{
	t_img	img;

	img.addr = mlx_new_image(window->mlx, WIDTH, HEIGHT);
	if (!img.addr)
		return ;
	img.content = mlx_get_data_addr(img.addr, &img.bpp, &img.size_line,
			&img.endian);
	window->image = img;
}

void	img_pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	pixel = img->content + (y * img->size_line + x * (img->bpp / 8));
	*(int *)pixel = color;
}

void	draw_cube(t_img *image, int size, int x, int y, int color)
{
	int	i;
	int	j;

	i = x;
	while (i < x + size)
	{
		j = y;
		while (j < y + size)
		{
			img_pixel_put(image, i, j, color);
			j++;
		}
		i++;
	}
}

void	draw_wall(t_img *image, int start, int end, int x)
{
	int	i;

	i = start - 1;
	while (++i < end)
		img_pixel_put(image, x, i, 0xFFFFFF);
}


void	draw_minimap(t_img *img, float *player)
{
	int	x;
	int	y;

	x = -1;
	while (++x < width)
	{
		draw_line((t_vec2) {x * 30, 0}, (t_vec2) {x * 30, height * 30}, 0x555555, img);
		y = -1;
		while (++y < height)
		{
			if (map[x][y] == 1)
				draw_cube(img, 30, y * 30, x * 30, 0xFFFFFF);
		}
	}
	y = -1;
	while (++y < height)
	{
		draw_line((t_vec2) {0, y * 30}, (t_vec2) {width * 30, y * 30}, 0x555555, img);
	}
	draw_cube(img, 10, (30 * player[0]) - 5, (30 * player[1]) - 5, 0xFFFF00);
}

int	key_hook(int keycode, float *pos)
{
	if (keycode == XK_a)
		pos[0] += 0.2;
	else if (keycode == XK_s)
		pos[0] -= 0.2;
	else if (keycode == XK_z)
		pos[1] += 0.2;
	else if (keycode == XK_x)
		pos[1] -= 0.2;
	printf("%f - %f\n", pos[0], pos[1]);
	return (0);
}

int	loop_hook(t_data *param)
{
	draw_minimap(&param->window->image, param->pos);
	raycast(&param->window->image, (t_vec2) {param->pos[0], param->pos[1]});
	mlx_put_image_to_window(param->window->mlx, param->window->ptr, param->window->image.addr, 0, 0);
	return (0);
}

int	main(int argc, char const *argv[])
{
	t_window	window;
	t_collector	*collector;
	t_data		data;

	float player[2] = {7.5f, 6.5f};
	(void)argc;
	(void)argv;
	collector = init_collector();
	create_window(&window, collector);
	create_img(&window);
	// draw_cube(&window.image, 50, 100, 200);
	// draw_line((t_vec2) {100, 200}, (t_vec2) {300, 500}, 0xFFFF00, &window.image);
	// loop_hook(&window);
	data.window = &window;
	data.pos = player;
	// mlx_key_hook(window.ptr, &loop_hook, player);
	mlx_loop_hook(window.mlx, &loop_hook, &data);
	mlx_hook(window.ptr, KeyPress, KeyPressMask, key_hook, player);
	mlx_loop(window.mlx);
	return (free_collector(collector), 0);
}
