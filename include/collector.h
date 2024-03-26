/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:48:40 by abasdere          #+#    #+#             */
/*   Updated: 2024/03/22 10:33:00 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLECTOR_H
# define COLLECTOR_H

typedef struct s_collector
{
	void				*el;
	void				(*f)(void *);
	int					mlx;
	struct s_collector	*next;
}	t_collector;

#endif
