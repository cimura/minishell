all:
	$(MAKE) -C ../libft
	$(MAKE) bonus -C ../libft
	cc -Wall -Wextra -Werror -g lexer.c lexer_helper.c lexer_util.c ../libft/libft.a -o lexer
clean:
	$(MAKE) -C ../libft fclean
	rm lexer
