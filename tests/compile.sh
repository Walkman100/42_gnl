#!/usr/bin/env bash

die() {
	echo
	echo "$* Failed!"
	exit 1
}

cd "$(dirname "$0")"

if [[ "$1" == "re" ]]; then
    make -C ../libft re || die "Make Libft"
else
    make -C ../libft || die "Make Libft"
fi

echo gcc -Wall -Wextra -Werror -c ../get_next_line.c
gcc -Wall -Wextra -Werror -c ../get_next_line.c || die "Compiling GetNextLine"

echo gcc -Wall -Wextra -Werror main.c get_next_line.o -L ../libft -lft -o test
gcc -Wall -Wextra -Werror main.c get_next_line.o -L ../libft -lft -o test || die "Compiling Test"
