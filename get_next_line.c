/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 13:59:47 by mcarter           #+#    #+#             */
/*   Updated: 2019/07/05 16:25:35 by mcarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		get_new_buffer(t_flist *flist)
{
	int	ret;

	errno = 0;
	flist->pos = 0;
	ret = read(flist->fd, flist->buff, BUFF_SIZE);
	flist->buff[ret] = '\0';
	if (ret == 0)
		return (0);
	else if (errno)
		return (-1);
	return (1);
}

static STR		get_line(t_flist *flist, STR old_line)
{
	int	len;
	STR	tmp;

	len = ft_strclen(flist->buff + flist->pos, '\n');
	if (!old_line)
	{
		tmp = ft_strnew(len);
		ft_strncpy(tmp, flist->buff + flist->pos, len);
		tmp[len] = '\0';
	}
	else
	{
		tmp = ft_strnew(ft_strlen(old_line) + len);
		ft_strcpy(tmp, old_line);
		free(old_line);
		ft_strncat(tmp, flist->buff + flist->pos, len);
	}
	flist->pos += len;
	return (tmp);
}

static t_flist	*get_flist_fd(t_flist **lst, int fd)
{
	t_flist	*lst_tmp;
	t_flist	*lst_prev;

	lst_tmp = *lst;
	lst_prev = NULL;
	while (lst_tmp)
	{
		if (lst_tmp->fd == fd)
			return (lst_tmp);
		lst_prev = lst_tmp;
		lst_tmp = lst_tmp->next;
	}
	lst_tmp = (t_flist *)malloc(sizeof(t_flist));
	lst_tmp->fd = fd;
	lst_tmp->buff = ft_strnew(BUFF_SIZE + 1);
	lst_tmp->pos = 0;
	lst_tmp->eof = 0;
	lst_tmp->next = NULL;
	if (lst_prev)
	{
		lst_prev->next = lst_tmp;
		return (lst_prev->next);
	}
	*lst = lst_tmp;
	return (*lst);
}

/*
** list.content (t_flist) -> fd, buff, pos, eof
** int     get_new_buffer(fd, buf) sets buffer and returns exit code
** str     get_line(flist) gets the appropriate characters from the buffer
** t_flist get_flist_fd(lst_start, fd) gets the filelist for the given fd
**
**gnl{ static lst_start; lst_cur }
*/

int			get_next_line(const int fd, STR *line)
{
	static t_flist	*lst;
	t_flist			*tmp;
	t_flist			*tmp_prev;
	t_flist			*flist;
	int				ret;

	if (fd == 1 || fd == 2 || read(fd, NULL, 0) < 0)
		return (-1);
	flist = get_flist_fd(&lst, fd);
	*line = NULL;
	while (flist->buff[flist->pos] != '\n' && !flist->eof)
	{
		if (flist->buff[flist->pos] == '\0' && (ret = get_new_buffer(flist)) == 0)
			flist->eof = 1;
		if (!flist->eof)
			*line = get_line(flist, *line);
	}
	flist->pos++;
	if (flist->eof && !*line)
	{
		tmp = lst;
		while (tmp->fd != fd)
		{
			tmp_prev = tmp;
			tmp = tmp->next;
		}
		tmp_prev->next = tmp->next;
		ft_strdel(&(tmp->buff));
		if (tmp == lst)
			lst = NULL;
		ft_memdel((void **)&tmp);
		return (0);
	}
	if (!*line)
		*line = ft_strnew(0);
	return (1);
}
