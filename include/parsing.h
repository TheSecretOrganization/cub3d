/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:04:30 by averin            #+#    #+#             */
/*   Updated: 2024/03/07 13:31:14 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include "cub3d.h"
# include "collector.h"

# include <fcntl.h>
# include <sys/stat.h>

t_list	*read_file(const char *file, t_collector *collector);
void	parse_file(t_map *map, const char *argv, t_collector *collector);
void	parse_map(t_list *line, t_map *map, t_collector *collector);

#endif
