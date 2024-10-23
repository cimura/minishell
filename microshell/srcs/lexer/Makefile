all:
	$(MAKE) -C ../libft
#cc -Wall -Wextra -Werror -g lexer.c lexer_utils.c ../libft/libft.a -o lexer
	cc -Wall -Wextra -Werror -g lexer.c list_expand.c lexer_utils.c ../libft/libft.a -o expand
clean:
	$(MAKE) -C ../libft fclean
#	rm lexer
	rm expand
