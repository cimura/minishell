all:
	$(MAKE) -C ../libft
	cc -Wall -Wextra -Werror -g -lreadline main.c env.c export.c unset.c echo.c \
	cd.c pwd.c exit.c ../env/env_lst.c ../libft/libft.a -o builtin-shell
com-export:
	$(MAKE) -C ../libft
	cc -g export.c ../env/env_lst.c ../libft/libft.a -o export
clean:
	$(MAKE) -C ../libft fclean
	rm -f builtin-shell
	rm -f export