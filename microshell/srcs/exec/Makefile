all:
	$(MAKE) -C ../libft
	cc -Wall -Wextra -Werror -g ../lexer/lexer.c ../lexer/lexer_utils.c exec.c ../libft/libft.a -o exec
array:
	$(MAKE) -C ../libft
	cc -Wall -Wextra -Werror -g env_lst_to_array.c ../env/env_lst.c ../libft/libft.a -o env_array
clean:
	$(MAKE) -C ../libft fclean
	rm -f exec
	rm -f env_array
