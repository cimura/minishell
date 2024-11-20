all:
	$(MAKE) bonus -C ../libft
	cc -Wall -Wextra -Werror -g -I ../libft/include -I ../../inc lexer.c lexer_helper.c lexer_util.c ../libft/libft.a -o lexer
clean:
	$(MAKE) -C ../libft fclean
	rm lexer
