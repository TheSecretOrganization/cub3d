/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:03:32 by averin            #+#    #+#             */
/*   Updated: 2024/03/06 16:14:35 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

#define MALLOC_ERROR "Malloc failed"
#define OPEN_ERROR "Cannot open file"
#define SUFFIX_ERROR "Invalid suffix, use a <map.cub>"

void	clear_file(void *v)
{
	ft_lstclear((t_list **) &v, &free);
}

static void	check_suffix(const char *f, const char *s, t_collector *col)
{
	size_t	len;

	len = ft_strlen(f);
	if (len < 4
		|| f[len - 4] != s[0]
		|| f[len - 3] != s[1]
		|| f[len - 2] != s[2]
		|| f[len - 1] != s[3])
		cerror(SUFFIX_ERROR, col);
}

t_list	*read_file(const char *file, t_collector *collector)
{
	t_list	*lst;
	t_list	*new_element;
	char	*line;
	char	*trimmed;
	int		fd;

	lst = NULL;
	(check_suffix(file, ".cub", collector), fd = open(file, O_RDONLY));
	if (fd == -1)
		cerror(OPEN_ERROR, collector);
	while (oget_next_line(fd, &line))
	{
		trimmed = ft_strtrim(line, "\n");
		free(line);
		if (!trimmed)
			(ft_lstclear(&lst, &free), close(fd),
				cerror(MALLOC_ERROR, collector));
		new_element = ft_lstnew(trimmed);
		if (!new_element)
			(ft_lstclear(&lst, &free), free(trimmed), close(fd),
				cerror(MALLOC_ERROR, collector));
		ft_lstadd_back(&lst, new_element);
	}
	(close(fd), add_collector(collector, lst, &clear_file));
	return (lst);
}
