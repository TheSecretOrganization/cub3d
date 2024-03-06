/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:52:38 by averin            #+#    #+#             */
/*   Updated: 2024/03/06 11:06:54 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "collector.h"
#include "window.h"

#define USAGE_ERROR "Usage: ./cub3d <file.cub>"

int	main(int argc, char const *argv[])
{
	t_window	window;
	t_collector	*collector;

	(void)argv;
	if (argc != 2)
		error(USAGE_ERROR);
	collector = init_collector();
	create_window(&window, collector);
	return (free_collector(collector), 0);
}
