/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 13:59:47 by mcarter           #+#    #+#             */
/*   Updated: 2019/06/13 15:54:12 by mcarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	get_new_buffer(const int fd, char *buf, int *cur_pos)
{
	int	ret;

	*cur_pos = 0;
	ret = read(fd, buf, BUFF_SIZE);
	buf[ret] = '\0';
	if (errno)
		return (-1);
	if (ret == 0)
		return (0);
	return (1);
}

static void	set_line(char **tmp, char *buf, int *cur_pos, char ***line)
{
	int	len;

	len = ft_strclen(buf + *cur_pos, '\n');
	if (*tmp)
	{
		*tmp = ft_strnew(ft_strlen(**line) + len);
		ft_strcpy(*tmp, **line);
		free(**line);
		ft_strncat(*tmp, buf + *cur_pos, len);
	}
	else
	{
		*tmp = ft_strnew(len);
		ft_strncpy(*tmp, buf + *cur_pos, len);
		(*tmp)[len] = '\0';
	}
	**line = *tmp;
	*cur_pos = *cur_pos + len;
}

int			get_next_line(const int fd, char **line)
{
	int			ret;
	char		*tmp;
	static char	buf[BUFF_SIZE + 1];
	static int	cur_pos = 0;

	tmp = NULL;
	while (buf[cur_pos] != '\n')
	{
		if (buf[cur_pos] == '\0')
		{
			if ((ret = get_new_buffer(fd, buf, &cur_pos)) != 1)
				return (ret);
		}
		else
			tmp = NULL;
		set_line(&tmp, buf, &cur_pos, &line);
	}
	if (buf[cur_pos] == '\n')
	{
		cur_pos++;
		if (tmp == NULL)
			*line = ft_strnew(1);
	}
	return (1);
}
