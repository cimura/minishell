all:
	$(MAKE) -C ../libft
	$(MAKE) bonus -C ../libft
	cc -Wall -Wextra -Werror -g -I../libft/include -I../../inc ../env/env_lst.c \
	../parser/parser.c ../parser/parser_helper.c ../parser/parser_util.c \
	../expander/expander_util.c ../expander/expander_helper.c ../expander/expander.c \
	../builtin/cd.c ../builtin/echo.c ../builtin/env.c ../builtin/exit.c ../builtin/export.c ../builtin/pwd.c ../builtin/unset.c \
	../utils.c \
	../signal/signal.c \
	command_executor.c helper.c util.c env_lst_to_array.c \
	../libft/libft.a  -lreadline -o test
clean:
	$(MAKE) -C ../libft fclean
	rm test
