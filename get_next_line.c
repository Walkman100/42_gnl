/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 13:59:47 by mcarter           #+#    #+#             */
/*   Updated: 2019/06/11 16:36:18 by mcarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		get_next_line(const int fd, char **line)
{
	int			ret;
	static char	buf[BUF_SIZE];
	//static int	cur_pos;

	if ((ret = read(fd, buf, BUF_SIZE)))
	{
		buf[ret] = '\0';
		*line = buf;
		return (1);
	}
	if (errno)
		return (-1);
	else
		return (0);
}
