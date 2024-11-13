all:
	$(MAKE) -C ../libft
	$(MAKE) bonus -C ../libft
	cc -Wall -Wextra -Werror -g -lreadline ../env/env_lst.c \
	../lexer/lexer.c ../lexer/lexer_helper.c ../lexer/lexer_util.c \
	../expander/expander_util.c ../expander/expander_helper.c ../expander/expander.c \
	../builtin/cd.c ../builtin/echo.c ../builtin/env.c ../builtin/exit.c ../builtin/export.c ../builtin/pwd.c ../builtin/unset.c \
	main.c command_executor.c util.c env_lst_to_array.c \
	../libft/libft.a -o test
clean:
	$(MAKE) -C ../libft fclean
	rm test
