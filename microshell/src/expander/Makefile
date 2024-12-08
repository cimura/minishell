all:
	$(MAKE) -C ../libft
	$(MAKE) bonus -C ../libft
	cc -Wall -Wextra -Werror -g -I../../inc -I../libft/include expander_utils.c expand_dollar.c expand_dollar_utils.c \
		expand_quotes.c ../parser/parser.c ../parser/parser_utils.c ../parser/create_command_list.c \
			../utils.c ../utils2.c ../syntax/syntax_utils.c \
			 ../env/create_env_lst.c ../env/env_lst_utils.c ../libft/libft.a -o expander
clean:
	$(MAKE) -C ../libft fclean
	rm expander
