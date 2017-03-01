/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 22:47:10 by ekelen            #+#    #+#             */
/*   Updated: 2017/02/28 09:12:10 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 10

# include <stdlib.h>
# include <fcntl.h>
# include "./libft/libft.h"
# include "./fdf.h"

int	get_next_line(const int fd, char **line);

#endif
