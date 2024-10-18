all:
	$(MAKE) -C ../libft
# cc -g env_lst.c env.c ../libft/libft.a -o env
	cc -g env_lst.c export.c ../libft/libft.a -o export
# cc -g env_lst.c env.c unset.c ../libft/libft.a -o unset
clean:
	$(MAKE) -C ../libft fclean
	rm env
env:
	cc env.c ../libft/libft.a