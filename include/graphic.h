/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:15:07 by abasdere          #+#    #+#             */
/*   Updated: 2024/03/06 15:58:48 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHIC_H
# define GRAPHIC_H

# include "libft.h"
# include "collector.h"

typedef struct	s_texture
{
	char				*key;
	char				*value;
	struct s_texture	*next;
}	t_texure;

void	parse_texture(char *line, t_texure **texture, t_collector *collector);

#endif
