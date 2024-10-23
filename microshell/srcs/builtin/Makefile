all:
	$(MAKE) -C ../libft
	cc -Wall -Wextra -Werror -g -lreadline main.c env_lst.c env.c export.c unset.c echo.c \
	cd.c pwd.c exit.c ../libft/libft.a -o builtin-shell
com-export:
	cc -g env_lst.c export.c ../libft/libft.a -o export
clean:
	$(MAKE) -C ../libft fclean
	rm -f builtin-shell
	rm -f export