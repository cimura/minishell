int	g_status;

// echo"$PATH < aaa" < infile >>out

// echo" < infile >>out"

echo"usr/.. < aaa"
<
infile
>>outfile

"ls -l | wc -l" <- expander
ls -l | wc -l

int	main(int argc, char **argv, char **envp) {
	signal();
	create_env_list(envp);
	char *line = readline();
	lexer(line); // t_token
	expander(t_env, t_token);

	execve(t_env, t_token);
	clean();
}
