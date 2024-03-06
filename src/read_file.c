/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:03:32 by averin            #+#    #+#             */
/*   Updated: 2024/03/06 10:48:07 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

#define MALLOC_ERROR "Malloc failed"
#define OPEN_ERROR "Cannot open file"

void	clear_file(void *v)
{
	ft_lstclear((t_list **) &v, &free);
}

t_list	*read_file(const char *file, t_collector *collector)
{
	t_list	*lst;
	t_list	*new_element;
	char	*line;
	char	*trimmed;
	int		fd;

	lst = NULL;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		cerror(OPEN_ERROR, collector);
	while (oget_next_line(fd, &line))
	{
		trimmed = ft_strtrim(line, "\n");
		free(line);
		if (!trimmed)
			(ft_lstclear(&lst, &free), cerror(MALLOC_ERROR, collector));
		new_element = ft_lstnew(trimmed);
		if (!new_element)
			(ft_lstclear(&lst, &free), free(trimmed),
				cerror(MALLOC_ERROR, collector));
		ft_lstadd_back(&lst, new_element);
	}
	add_collector(collector, lst, &clear_file);
	return (lst);
}
