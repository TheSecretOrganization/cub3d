/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:14:09 by abasdere          #+#    #+#             */
/*   Updated: 2024/03/12 11:46:10 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include "mlx.h"
# include "collector.h"
# include "utils.h"

# define WIDTH 800
# define HEIGHT 600

typedef struct s_window
{
	void	*mlx;
	void	*ptr;
}	t_window;

void	create_window(t_window *window, t_collector *col);

#endif
