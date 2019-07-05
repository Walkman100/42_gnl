# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcarter <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/28 15:49:40 by mcarter           #+#    #+#              #
#    Updated: 2019/07/03 13:47:53 by mcarter          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GCCFLAGS = -Wall -Wextra -Werror
GNL = get_next_line.o
LFT = -L ../libft -lft
LFTA = ../libft/libft.a

test: $(LFTA) $(GNL) main.c
	gcc $(GCCFLAGS) main.c $(GNL) $(LFT) -o test

all: test

clean:
	rm -f $(GNL) test

fclean: clean
	make -C ../libft fclean

re: fclean all

$(GNL): ../get_next_line.c ../get_next_line.h
	gcc $(GCCFLAGS) -c ../get_next_line.c

$(LFTA):
	make -C ../libft
