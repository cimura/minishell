all:
	$(MAKE) -C ../libft
	cc -Wall -Wextra -Werror -g expander.c expander_helper.c expander_util.c ../env/env_lst.c ../libft/libft.a -o expander
clean:
	$(MAKE) -C ../libft fclean
	rm expander
