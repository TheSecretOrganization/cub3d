/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:54:10 by abasdere          #+#    #+#             */
/*   Updated: 2024/03/05 17:31:07 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collector.h"
#include <stdio.h>

void	free_collector(t_collector *collector)
{
	t_collector	*next;

	while (collector)
	{
		next = collector->next;
		if (collector->el)
			collector->f(collector->el);
		free(collector);
		collector = next;
	}
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
		(free_collector(collector), error("Malloc failed"));
	next->next->el = el;
	next->next->f = f;
	next->next->next = NULL;
}

void	*ccalloc(size_t nmemb, size_t size, t_collector *collector)
{
	void	*el;

	el = ft_calloc(nmemb, size);
	if (el)
		(free_collector(collector), error("Malloc failed"));
	add_collector(collector, el, &free);
	return (el);
}
