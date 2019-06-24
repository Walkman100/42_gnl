/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 13:59:47 by mcarter           #+#    #+#             */
/*   Updated: 2019/06/16 18:51:30 by mcarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	get_new_buffer(const int fd, STR buf)
{
	int	ret;

	errno = 0;
	ret = read(fd, buf, BUFF_SIZE);
	buf[ret] = '\0';
	if (ret == 0)
		return (0);
	else if (errno)
		return (-1);
	return (1);
}

static void	shift_buffer(STR buf, int chars)
{
	int	i;

	if (ft_strchr(buf, '\n'))
	{
		i = 0;
		while (i + chars < BUFF_SIZE)
		{
			buf[i] = buf[i + chars + 1];
			i++;
		}
	}
	else
		buf[0] = '\0';
}

static STR read_line(STR buf)
{
	int		len;
	char	*tmp;

	len = ft_strclen(buf, '\n');
	tmp = ft_strnew(len);
	ft_strncpy(tmp, buf, len);
	tmp[len] = '\0';
	shift_buffer(buf, len);
	return (tmp);
}

static char	*concat_line(STR buf, STR old_line)
{
	int		len;
	char	*tmp;

	len = ft_strclen(buf, '\n');
	tmp = ft_strnew(ft_strlen(old_line) + len);
	ft_strcpy(tmp, old_line);
	free(old_line);
	ft_strncat(tmp, buf, len);
	shift_buffer(buf, len);
	return (tmp);
}

/*
** int get_new_buffer(fd, buf) sets buffer and returns exit code
** shift_buffer(buf, chars) moves the buffer up `chars` amount for next line read
** str read_line(buf) returns malloced string
** str concat_line(buf, old_line) returns malloced string, frees original
** buf[BUFF_SIZE + 1] = flag whether file has finished reading
*/

int			get_next_line(const int fd, STR *line)
{
	int			ret;
	static char	buf[BUFF_SIZE + 2];

	if (buf[BUFF_SIZE + 1] == 1)
		return (0);
	if (*buf == '\0')
		if ((ret = get_new_buffer(fd, buf)) != 1)
			return (ret);
	*line = read_line(buf);
	while (*buf == '\0' && buf[BUFF_SIZE + 1] != 1)
	{
		ret = get_new_buffer(fd, buf);
		if (ret == -1)
			return (ret);
		else if (ret == 0)
			buf[BUFF_SIZE + 1] = 1;
		*line = concat_line(buf, *line);
	}
	return (1);
}
