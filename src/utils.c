/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:59:20 by abasdere          #+#    #+#             */
/*   Updated: 2024/03/06 10:42:24 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	cerror(char *message, t_collector *collector)
{
	ft_dprintf(2, "Error\n%s\n", message);
	if (collector)
		free_collector(collector);
	exit(1);
}

void	error(char *message)
{
	cerror(message, NULL);
}
