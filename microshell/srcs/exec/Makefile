all:
	$(MAKE) -C ../libft
	$(MAKE) bonus -C ../libft
	cc -Wall -Wextra -Werror -g ../env/env_lst.c \
	../lexer/lexer.c ../lexer/lexer_helper.c ../lexer/lexer_util.c \
	../expander/expander_util.c ../expander/expander_helper.c ../expander/expander.c \
	main.c command_executor.c util.c \
	../libft/libft.a -o test
clean:
	$(MAKE) -C ../libft fclean
	rm test
