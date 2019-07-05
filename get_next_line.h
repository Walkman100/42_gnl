/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 13:59:52 by mcarter           #+#    #+#             */
/*   Updated: 2019/07/05 12:15:48 by mcarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <errno.h>
# include "libft/libft.h"
# define BUFF_SIZE 32

typedef struct	s_finfo
{
	int	fd;
	STR	buff;
	int	pos;
	int	eof;
}				t_finfo;

int		get_next_line(const int fd, STR *line);
#endif
