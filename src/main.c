/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:52:38 by averin            #+#    #+#             */
/*   Updated: 2024/04/22 09:27:26 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char const *argv[])
{
	t_data	data;

	if (argc != 2)
		error(USAGE_ERROR, NULL);
	data.window = (t_window){NULL, NULL,
	{NULL, NULL, 0, 0, 0, 0, 0}};
	data.player = (t_player){{0, 0}, {0, 0.66f}, {-1, 0}};
	data.map = (t_map){0, {NULL, NULL, NULL, NULL, {0}}, 0, 0};
	data.collector = init_collector();
	data.controls = 0;
	create_window(&data.window, data.collector);
	parse_file(&data, argv[1]);
	init_hook(&data);
	mlx_mouse_move(data.window.mlx, data.window.ptr, WIDTH / 2, HEIGHT / 2);
	mlx_mouse_hide(data.window.mlx, data.window.ptr);
	mlx_loop(data.window.mlx);
	return (free_collector(data.collector), 0);
}
