all:
	$(MAKE) -C ../libft
#	cc -Wall -Wextra -Werror -g lexer.c lexer_util.c ../libft/libft.a -o lexer
	cc -Wall -Wextra -Werror -g lexer.c expander.c expander_util.c expander_helper.c lexer_util.c \
								../env/env_lst.c ../libft/libft.a -o expand
clean:
	$(MAKE) -C ../libft fclean
#	rm lexer
	rm expand
