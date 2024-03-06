/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:04:30 by averin            #+#    #+#             */
/*   Updated: 2024/03/06 10:25:26 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include "collector.h"

# include <fcntl.h>
# include <sys/stat.h>

t_list	*read_file(char *file, t_collector *collector);

#endif
