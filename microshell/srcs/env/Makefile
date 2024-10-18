all:
	$(MAKE) -C ../libft
	cc -g env_list.c ../libft/libft.a -o env
clean:
	$(MAKE) -C ../libft fclean
	rm env
env:
	cc env.c ../libft/libft.a