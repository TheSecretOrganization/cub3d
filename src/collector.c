/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:54:10 by abasdere          #+#    #+#             */
/*   Updated: 2024/03/06 10:46:29 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collector.h"
#include "utils.h"
#include <stdio.h>

void	free_collector(t_collector *collector)
{
	t_collector	*next;
	t_collector	*mlx;

	mlx = NULL;
	while (collector)
	{
		next = collector->next;
		if (collector->mlx)
		{
			mlx = collector;
			collector = next;
			continue ;
		}
		if (collector->el)
			collector->f(collector->el);
		free(collector);
		collector = next;
	}
	if (mlx)
		(mlx->f(mlx->el), free(mlx));
}

t_collector	*init_collector(void)
{
	t_collector	*collector;

	collector = ft_calloc(1, sizeof(t_collector));
	if (!collector)
		error("Malloc failed");
	return (collector);
}

void	add_collector(t_collector *collector, void *el, void (*f)(void *))
{
	t_collector	*next;

	next = collector;
	while (next->next)
		next = next->next;
	next->next = ft_calloc(1, sizeof(t_collector));
	if (!next->next)
		cerror("Malloc failed", collector);
	next->next->el = el;
	next->next->f = f;
	next->next->next = NULL;
	next->next->mlx = 0;
}

void	give_mlx_priority(t_collector *collector)
{
	while (collector->next)
		collector = collector->next;
	collector->mlx = 1;
}

void	*ccalloc(size_t nmemb, size_t size, t_collector *collector)
{
	void	*el;

	el = ft_calloc(nmemb, size);
	if (el)
		cerror("Malloc failed", collector);
	add_collector(collector, el, &free);
	return (el);
}
