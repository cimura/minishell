all:
	$(MAKE) bonus -C ../libft
	cc -Wall -Wextra -Werror -g -I ../libft/include -I ../../inc parser.c parser_helper.c parser_util.c ../libft/libft.a -o parser
clean:
	$(MAKE) -C ../libft fclean
	rm parser
