all:
	$(MAKE) -C ../libft
	cc -Wall -Wextra -Werror -g -lreadline main.c env_lst.c env.c export.c unset.c echo.c \
	cd.c pwd.c exit.c ../libft/libft.a -o builtin-shell
clean:
	$(MAKE) -C ../libft fclean
	rm builtin-shell
