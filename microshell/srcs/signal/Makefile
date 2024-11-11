all:
	$(MAKE) -C ../libft
	$(MAKE) bonus -C ../libft
	cc -Wall -Wextra -Werror -g signal.c ../libft/libft.a -lreadline -o signal
clean:
	$(MAKE) -C ../libft fclean
	rm signal