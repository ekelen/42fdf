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

# include "get_next_line.h"
# include "fdf.h"

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

static char			*get_overflow(char **joined)
{
	char			*str;
	static char		*line_to_return = "";

	if (*joined && **joined)
		add_nl(joined);
	if ((str = ft_strchr(*joined, '\n')) != NULL)
	{
		*str = '\0';
		line_to_return = ft_strdup(*joined);
		ft_memmove(*joined, str + 1, ft_strlen(str + 1) + 1);
		return (line_to_return);
	}
	ft_bzero(*joined, ft_strlen(*joined));
	return (NULL);
}

static char			*read_file(int fd, int bytes_read)
{
	static char *joined = NULL;
	char		*str;
	char		*tmp;
	char		*line_to_return;
	char		buf[BUFF_SIZE + 1];

	if (joined == NULL)
		joined = ft_strnew(0);
	tmp = NULL;
	ft_memset(buf, 0, BUFF_SIZE + 1);
	while ((bytes_read = read(fd, buf, BUFF_SIZE)))
	{
		buf[bytes_read] = '\0';
		tmp = joined;
		joined = ft_strjoin(joined, buf);
		ft_strdel(&tmp);
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