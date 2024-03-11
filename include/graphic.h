/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:15:07 by abasdere          #+#    #+#             */
/*   Updated: 2024/03/11 11:02:15 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHIC_H
# define GRAPHIC_H

# include "libft.h"
# include "collector.h"

typedef struct s_color
{
	const char		*key;
	int				red;
	int				green;
	int				blue;
	struct s_color	*next;
}	t_color;

typedef struct s_texture
{
	const char			*key;
	const char			*value;
	struct s_texture	*next;
}	t_texure;

typedef struct s_graphic
{
	t_color		*color;
	t_texure	*texture;
}	t_graphic;

void	parse_graphic(char *line, t_graphic *graphic, t_collector *collector);
void	remove_space(char *line);
size_t	check_commas(const char *value);

#endif
