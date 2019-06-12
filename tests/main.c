/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:35:57 by mcarter           #+#    #+#             */
/*   Updated: 2019/06/11 16:49:27 by mcarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../get_next_line.h"
#include <fcntl.h>

int		main(int argc, char **argv)
{
	int		fd;
	int		i;
	char	*buf_ptr;

	if (argc == 1)
	{
		ft_putendl_fd("File name missing.", 2);
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		fd = open(argv[i], O_RDONLY);
		if (fd < 0)
		{
			ft_putstr_fd(argv[i], 2);
			ft_putendl_fd(": Error reading file", 2);
		}
		else
		{
			while (get_next_line(fd, &buf_ptr) == 1)
			{
				ft_putstr(buf_ptr);
			}
			close(fd);
		}
		i++;
	}
	return (0);
}
