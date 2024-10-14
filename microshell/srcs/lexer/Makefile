all:
	$(MAKE) -C ../libft
	cc -g pair_lexer.c ../libft/libft.a -o lexer
clean:
	$(MAKE) -C ../libft fclean
	rm lexer