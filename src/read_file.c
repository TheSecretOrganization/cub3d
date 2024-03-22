/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:03:32 by averin            #+#    #+#             */
/*   Updated: 2024/03/22 10:37:44 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_file(void *v)
{
	ft_lstclear((t_list **) &v, &free);
}

static int	check_suffix(const char *f)
{
	size_t	len;

	len = ft_strlen(f);
	return (len < 4
		|| f[len - 4] != '.'
		|| f[len - 3] != 'c'
		|| f[len - 2] != 'u'
		|| f[len - 1] != 'b');
}

t_list	*read_file(const char *file, t_collector *collector)
{
	t_list	*lst;
	t_list	*new_element;
	char	*line;
	int		fd;

	lst = NULL;
	if (check_suffix(file))
		cerror(SUFFIX_ERROR, collector);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		cerror(OPEN_ERROR, collector);
	while (oget_next_line(fd, &line))
	{
		line = ft_fstrtrim(line, "\n");
		if (!line)
			(ft_lstclear(&lst, &free), close(fd),
				cerror(MALLOC_ERROR, collector));
		new_element = ft_lstnew(line);
		if (!new_element)
			(ft_lstclear(&lst, &free), free(line), close(fd),
				cerror(MALLOC_ERROR, collector));
		ft_lstadd_back(&lst, new_element);
	}
	(close(fd), add_collector(collector, lst, &clear_file));
	return (lst);
}
