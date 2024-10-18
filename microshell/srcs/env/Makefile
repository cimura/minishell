all:
	$(MAKE) -C ../libft
	cc -g env_list.c env.c ../libft/libft.a -o env
	cc -g env_list.c export.c ../libft/libft.a -o export
clean:
	$(MAKE) -C ../libft fclean
	rm env
env:
	cc env.c ../libft/libft.a