/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:35:57 by mcarter           #+#    #+#             */
/*   Updated: 2019/06/14 17:29:38 by mcarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../get_next_line.h"
#include <fcntl.h>

void	print_file(STR filepath)
{
	int		fd;
	char	*buf_ptr;

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd(filepath, 2);
		ft_putendl_fd(": Error reading file", 2);
	}
	else
	{
		while (get_next_line(fd, &buf_ptr) == 1)
		{
			ft_putstr(buf_ptr);
			ft_putendl(BMAGENTA "$" RESET);
		}
		close(fd);
	}
}

int		main(int argc, STR *argv)
{
	int		i;

	if (argc == 1)
	{
		ft_putendl_fd("File name missing.", 2);
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		print_file(argv[i]);
		i++;
	}
	return (0);
}
