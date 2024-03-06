/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:15:07 by abasdere          #+#    #+#             */
/*   Updated: 2024/03/06 16:08:17 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHIC_H
# define GRAPHIC_H

# include "libft.h"
# include "collector.h"


typedef enum s_graphic_type
{
	COLOR,
	TEXTURE
}	t_graphic_type;

typedef struct	s_color
{
	int	red;
	int	green;
	int	blue;
}	t_color;

typedef struct	s_texture
{
	char				*key;
	char				*value;
}	t_texure;

typedef	struct s_graphic
{
	void				*el;
	t_graphic_type		type;
	struct s_graphic	*next;
}	t_graphic;


void	parse_texture(char *line, t_texure **texture, t_collector *collector);

#endif
