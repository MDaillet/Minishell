/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 12:00:35 by mdaillet          #+#    #+#             */
/*   Updated: 2021/11/08 18:25:06 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	storejoin(char **store, char *buf, int readsize)
{
	char		*temp;

	buf[readsize] = 0;
	if (*store == NULL)
		temp = ft_strdup2(buf, readsize);
	else
	{
		temp = ft_strjoin(*store, buf);
		free(*store);
	}
	*store = temp;
	if (ft_strchr1(*store, '\n'))
		return (1);
	return (0);
}

static int	make_line(char **store, char **line)
{
	char		*ptr;
	char		*temp;

	ptr = ft_strchr1(*store, '\n');
	if (ptr)
	{
		*line = ft_strdup2(*store, ptr - *store);
		temp = ft_strdup2(ptr + 1, ft_strlen(ptr + 1));
		free(*store);
		*store = temp;
		return (1);
	}
	else
	{
		*line = *store;
		*store = 0;
		return (0);
	}
}

int	get_next_line(int fd, char **line)
{
	char		*buf;
	static char	*store[OPEN_MAX];
	int			readsize;

	readsize = 0;
	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0 || !line)
		return (-1);
	if (!(ft_malloc(&buf, sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while (readsize >= 0)
	{
		readsize = read(fd, buf, BUFFER_SIZE);
		if (storejoin(&store[fd], buf, readsize) || readsize <= 0)
			break ;
	}
	free(buf);
	if (readsize < 0)
		return (-1);
	return (make_line(&store[fd], line));
}
