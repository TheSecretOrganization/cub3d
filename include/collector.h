/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:48:40 by abasdere          #+#    #+#             */
/*   Updated: 2024/03/06 12:23:27 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLECTOR_H
# define COLLECTOR_H

# include <sys/types.h>

typedef struct s_collector
{
	void				*el;
	void				(*f)(void *);
	int					mlx;
	struct s_collector	*next;
}	t_collector;

t_collector	*init_collector(void);
void		free_collector(t_collector *col);
void		*add_collector(t_collector *col, void *el, void (*f)(void *));
void		give_mlx_priority(t_collector *collector);
void		*ccalloc(size_t nmemb, size_t size, t_collector *col);

#endif
