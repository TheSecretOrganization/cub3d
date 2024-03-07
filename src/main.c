/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:52:38 by averin            #+#    #+#             */
/*   Updated: 2024/03/07 13:02:19 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "collector.h"
#include "parsing.h"
#include "window.h"

#define USAGE_ERROR "Usage: ./cub3d <file.cub>"

int	main(int argc, char const *argv[])
{
	t_window	window;
	t_collector	*collector;
	t_map		map;

	if (argc != 2)
		error(USAGE_ERROR);
	window = (t_window){NULL, NULL};
	map = (t_map){0, {{0, 0}, {0, 0}}, {NULL, NULL}, 0, 0};
	collector = init_collector();
	parse_file(&map, argv[1], collector);
	create_window(&window, collector);
	return (free_collector(collector), 0);
}
