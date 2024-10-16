all:
	$(MAKE) -C ../libft
	cc -Wall -Wextra -Werror -g lexer.c lexer_utils.c ../libft/libft.a -o lexer
clean:
	$(MAKE) -C ../libft fclean
	rm lexer
