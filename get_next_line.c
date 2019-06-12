/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 13:59:47 by mcarter           #+#    #+#             */
/*   Updated: 2019/06/12 14:03:18 by mcarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../libft/libft.h"

int		get_next_line(const int fd, char **line)
{
	int			ret;
	char		*tmp;
	static char	buf[BUF_SIZE + 1];
	static int	cur_pos = 0;
	int			len;

	while (buf[cur_pos] != '\n') // || buf[cur_pos] == '\0')
	{
		if (buf[cur_pos] == '\0')
		{
			cur_pos = 0;
			ret = read(fd, buf, BUF_SIZE);
			buf[ret] = '\0';
			if (errno)
				return (-1);
			if (ret == 0)
				return (0);
		}
		else
			tmp = NULL;
		len = ft_strclen(buf + cur_pos, '\n');
		if (tmp)
		{
			tmp = ft_strnew(ft_strlen(*line) + len);
			ft_strcpy(tmp, *line);
			free(*line);
			ft_strncat(tmp, buf + cur_pos, len);
		}
		else
		{
			tmp = ft_strnew(len);
			ft_strncpy(tmp, buf + cur_pos, len);
			tmp[len] = '\0';
		}
		*line = tmp;
		cur_pos = cur_pos + len;
	}

	if (buf[cur_pos] == '\n')
		cur_pos++;
	return (1);
}
