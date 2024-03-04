/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 13:41:59 by averin            #+#    #+#             */
/*   Updated: 2023/12/05 08:56:37 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define BUFFER_SIZE 200
#define TRUE 1
#define FALSE 0

size_t		find_end_line(char *s, size_t len);
char		*ft_strcat(char *s1, char *s2);
void		ft_shift_str(char *s, size_t shift, size_t len);
static int	is_valid(char *line);
static int	read_file(int fd, char **buffer);
static char	*process_buffer(char *buffer);

char	*oget_next_line(int fd, char **line)
{
	*line = get_next_line(fd);
	return (*line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	char		*process;
	char		*line;

	line = NULL;
	process = NULL;
	while (!is_valid(line) && read_file(fd, (char **) &buffer))
	{
		process = process_buffer(buffer);
		if (!process)
			return (free(line), NULL);
		if (line)
		{
			line = ft_strcat(line, process);
			if (!line)
				return (NULL);
		}
		else
			line = process;
	}
	return (line);
}

static int	is_valid(char *line)
{
	if (!line)
		return (FALSE);
	return (line[ft_strlen(line) - 1] == '\n');
}

static int	read_file(int fd, char **buffer)
{
	ssize_t	readed;

	if (!buffer[0])
	{
		readed = read(fd, buffer, BUFFER_SIZE);
		if (readed <= 0)
			return (FALSE);
	}
	return (TRUE);
}

static char	*process_buffer(char *buffer)
{
	char	*line;
	size_t	len;
	size_t	i;

	len = find_end_line(buffer, BUFFER_SIZE);
	line = ft_calloc(len + 1, sizeof(char));
	if (!line)
		return (NULL);
	i = -1;
	while (++i < len)
		line[i] = buffer[i];
	line[i] = '\0';
	ft_shift_str(buffer, len, BUFFER_SIZE);
	return (line);
}
