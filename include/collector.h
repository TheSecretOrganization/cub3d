/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:48:40 by abasdere          #+#    #+#             */
/*   Updated: 2024/03/05 22:47:50 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLECTOR_H
# define COLLECTOR_H

# include "utils.h"

typedef struct s_collector
{
	void				*el;
	void				(*f)(void *);
	int					mlx;
	struct s_collector	*next;
}	t_collector;

t_collector	*init_collector(void);
void		free_collector(t_collector *col);
void		add_collector(t_collector *col, void *el, void (*f)(void *));
void		give_mlx_priority(t_collector *collector);
void		*ccalloc(size_t nmemb, size_t size, t_collector *col);

#endif
