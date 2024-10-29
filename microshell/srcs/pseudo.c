int	g_status;

int	main(int argc, char **argv, char **envp) {
	signal();
	create_env_list(envp);
	readline();
	lexer(line); // t_token
	expander(t_env, t_token);

	execve(t_env, t_token);
	clean();
)
