#!/bin/bash

cd "$(dirname "$0")"

echo gcc -Wall -Wextra -Werror -c ../get_next_line.c
gcc -Wall -Wextra -Werror -c ../get_next_line.c

if [ "$?" == "0" ]; then
	echo gcc -Wall -Wextra -Werror main.c -L ../../libft -lft -o test
	gcc -Wall -Wextra -Werror main.c get_next_line.o -L ../../libft -lft -o test
fi
