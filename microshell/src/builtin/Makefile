all:
	$(MAKE) -C ../libft
	cc -Wall -Wextra -Werror -g -lreadline main.c ../env/env_lst.c env.c export.c unset.c echo.c \
	cd.c pwd.c exit.c ../libft/libft.a -o builtin-shell
com-cd:
	$(MAKE) -C ../libft
	cc -Wall -Wextra -Werror -g cd.c pwd.c ../env/env_lst.c ../libft/libft.a -o cd
com-export:
	$(MAKE) -C ../libft
	cc -Wall -Wextra -Werror -g export.c ../env/env_lst.c ../libft/libft.a -o export
com-unset:
	$(MAKE) -C ../libft
	cc -Wall -Wextra -Werror -g unset.c ../env/env_lst.c ../libft/libft.a -o unset
clean:
	$(MAKE) -C ../libft fclean
	rm -f builtin-shell
	rm -f export
	rm -f unset
	rm -f cd
