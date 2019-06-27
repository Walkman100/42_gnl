/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:35:57 by mcarter           #+#    #+#             */
/*   Updated: 2019/06/21 20:35:37 by mcarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
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
	char	*buf_ptr;

	if (argc == 1)
	{
		while (get_next_line(0, &buf_ptr) == 1)
		{
			ft_putstr(buf_ptr);
			ft_putendl(BMAGENTA "$" RESET);
		}
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		print_file(argv[i]);
		i++;
	}
	return (0);
}
