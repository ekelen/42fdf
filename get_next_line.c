/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 19:14:24 by ekelen            #+#    #+#             */
/*   Updated: 2017/01/17 15:51:04 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void			add_nl(char **last_line)
{
	char		*added_nl;
	size_t		i;

	added_nl = NULL;
	i = 0;
	while (i < ft_strlen(*last_line))
	{
		if (*(*last_line + i) == '\n')
			return ;
		i++;
	}
	added_nl = *last_line;
	*last_line = ft_strjoin(*last_line, "\n");
	if (*added_nl)
		ft_strdel(&added_nl);
	return ;
}

static char			*get_overflow(char **leftover_buf)
{
	char			*str;
	static char		*line_to_return = "";

	if (*leftover_buf && **leftover_buf)
		add_nl(leftover_buf);
	if ((str = ft_strchr(*leftover_buf, '\n')) != NULL)
	{
		*str = '\0';
		line_to_return = ft_strdup(*leftover_buf);
		ft_memmove(*leftover_buf, str + 1, ft_strlen(str + 1) + 1);
		return (line_to_return);
	}
	ft_bzero(*leftover_buf, ft_strlen(*leftover_buf));
	return (NULL);
}

static char			*read_file(int fd, int bytes_read)
{
	static char *joined = "";
	char		*str;
	char		*other_str;
	char		*line_to_return;
	char		buf[BUFF_SIZE + 1];

	other_str = NULL;
	ft_memset(buf, 0, BUFF_SIZE + 1);
	while ((bytes_read = read(fd, buf, BUFF_SIZE)))
	{
		buf[bytes_read] = '\0';
		other_str = joined;
		joined = ft_strjoin(joined, buf);
		if (*other_str)
			ft_strdel(&other_str);
		if ((str = ft_strchr(joined, '\n')) != NULL)
		{
			*str = '\0';
			line_to_return = ft_strdup(joined);
			ft_memmove(joined, str + 1, ft_strlen(str + 1) + 1);
			return (line_to_return);
		}
	}
	return (get_overflow(&joined));
}

int					get_next_line(const int fd, char **line)
{
	if (!line || fd < 0 || read(fd, *line, 0) == -1)
		return (-1);
	if ((*line = read_file(fd, 0)) != NULL)
		return (1);
	*line = NULL;
	return (0);
}
