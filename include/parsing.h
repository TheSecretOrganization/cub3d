/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:04:30 by averin            #+#    #+#             */
/*   Updated: 2024/03/07 11:37:10 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include "cub3d.h"
# include "collector.h"

# include <fcntl.h>
# include <sys/stat.h>

typedef struct s_pmap
{
	t_list	*map;
	size_t	size;
}	t_pmap;

t_list	*read_file(const char *file, t_collector *collector);
void	parse_file(t_map *map, const char *argv, t_collector *collector);

#endif
