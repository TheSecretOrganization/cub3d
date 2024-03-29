/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:59:20 by abasdere          #+#    #+#             */
/*   Updated: 2024/03/29 08:52:16 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cerror(const char *message, const char *el, t_collector *collector)
{
	ft_dprintf(2, "Error\n%s", message);
	if (el)
		ft_dprintf(2, ": %s", el);
	ft_putchar_fd('\n', 2);
	if (collector)
		free_collector(collector);
	exit(1);
}

void	error(const char *message, const char *el)
{
	cerror(message, el, NULL);
}

float	rad(float deg)
{
	return (deg * M_PI / 180);
}
