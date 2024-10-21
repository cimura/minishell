all:
	$(MAKE) -C ../libft
	cc -Wall -Wextra -Werror -g ../lexer/lexer.c ../lexer/lexer_utils.c exec.c ../libft/libft.a -o exec
clean:
	$(MAKE) -C ../libft fclean
	rm exec
