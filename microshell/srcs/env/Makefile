all:
	$(MAKE) -C ../libft
	cc -Wall -Wextra -Werror -g -lreadline env_lst.c env.c export.c unset.c main.c ../libft/libft.a -o builtin-shell
clean:
	$(MAKE) -C ../libft fclean
	rm builtin=shell
