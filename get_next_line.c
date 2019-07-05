/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 13:59:47 by mcarter           #+#    #+#             */
/*   Updated: 2019/07/05 13:37:42 by mcarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		get_new_buffer(t_finfo *finfo)
{
	int	ret;

	errno = 0;
	finfo->pos = 0;
	ret = read(finfo->fd, finfo->buff, BUFF_SIZE);
	finfo->buff[ret] = '\0';
	if (ret == 0)
		return (0);
	else if (errno)
		return (-1);
	return (1);
}

static STR		get_line(t_finfo *finfo, STR old_line)
{
	int	len;
	STR	tmp;

	len = ft_strclen(finfo->buff + finfo->pos, '\n');
	if (!old_line)
	{
		tmp = ft_strnew(len);
		ft_strncpy(tmp, finfo->buff + finfo->pos, len);
		tmp[len] = '\0';
	}
	else
	{
		tmp = ft_strnew(ft_strlen(old_line) + len);
		ft_strcpy(tmp, old_line);
		free(old_line);
		ft_strncat(tmp, finfo->buff + finfo->pos, len);
	}
	finfo->pos += len;
	return (tmp);
}

static t_finfo	*get_finfo_fd(t_list **lst, int fd)
{
	t_finfo	*finfo;
	t_list	*lst_tmp;
	t_list	*lst_prev;

	lst_tmp = *lst;
	while (lst_tmp)
	{
		if (((t_finfo *)(lst_tmp->content))->fd == fd)
			return ((t_finfo *)lst_tmp->content);
		lst_prev = lst_tmp;
		lst_tmp = lst_tmp->next;
	}
	finfo = (t_finfo *)malloc(sizeof(t_finfo));
	finfo->fd = fd;
	finfo->buff = ft_strnew(BUFF_SIZE + 1);
	finfo->pos = 0;
	finfo->eof = 0;
	if (lst_prev)
		lst_prev->next = ft_lstnew(finfo, sizeof(t_finfo));
	else
		*lst = ft_lstnew(finfo, sizeof(t_finfo));
	ft_memdel((void **)&finfo);
	if (lst_prev)
		return ((t_finfo *)lst_prev->next->content);
	else
		return ((t_finfo *)((*lst)->content));
}

static void		lstdelfnc(void *content, size_t size)
{
	ft_memdel((void **)&(((t_finfo *)content)->buff));
	ft_memdel(&content);
	size++;
}

/*
** list.content (t_finfo) -> fd, buff, pos, eof
** int     get_new_buffer(fd, buf) sets buffer and returns exit code
** str     get_line(finfo) gets the line for the given fileinfo
** t_finfo get_finfo_fd(lst_start, fd) gets the fileinfo for the given fd
** lstdelfnc(void *, size_t) function to pass to ft_lstdelone
**
**gnl{ static lst_start; lst_cur }
*/

int			get_next_line(const int fd, STR *line)
{
	static t_list	*lst;
	t_list			*tmp;
	t_list			*tmp_prev;
	t_finfo			*finfo;
	int				ret;

	finfo = get_finfo_fd(&lst, fd);
	*line = NULL;
	while (finfo->buff[finfo->pos] != '\n' && !finfo->eof)
	{
		if (finfo->buff[finfo->pos] == '\0' && (ret = get_new_buffer(finfo)) == 0)
				finfo->eof = 1;
		if (!finfo->eof)
			*line = get_line(finfo, *line);
	}
	finfo->pos++;
	if (finfo->eof && !*line)
	{
		tmp = lst;
		while (((t_finfo *)(tmp->content))->fd != fd)
		{
			tmp_prev = tmp;
			tmp = tmp->next;
		}
		tmp_prev->next = tmp->next;
		ft_lstdelone(&tmp, &lstdelfnc);
		return (0);
	}
	if (!*line)
		*line = ft_strnew(0);
	return (1);
}
