#include "exec.h"

void  set_stdin(const char *tmp_file)
{
  int fd_tmp = open(tmp_file, O_RDONLY);

  unlink(tmp_file);
  dup2(fd_tmp, STDIN_FILENO);
  close(fd_tmp);
}

void	here_doc(char *eof)
{
	char		*line;
	int			fd_tmp;
	const char	*tmp_file = "/tmp/.heredoc_tmp";

	fd_tmp = open(tmp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_tmp == -1)
		perror("tmpfile");

	while (1)
	{
    ft_putstr_fd("heredoc> ", STDIN_FILENO);
		line = readline("");
		if (!line || (ft_strncmp(line, eof, ft_strlen(eof) + 1) == 0))
    			break ;
		write(fd_tmp, line, ft_strlen(line));
    write(fd_tmp, "\n", 1);
		free(line);
	}
	free(line);
	close(fd_tmp);
	set_stdin(tmp_file);
}

int	pass_token_to_expand(t_env *env_lst, t_token *per_pipe)
{
	int	i;
	while (per_pipe != NULL)
	{
		i = 0;
		while (per_pipe->command_line[i] != NULL)
		{
			per_pipe->command_line[i] = expander(env_lst, per_pipe->command_line[i]);
			i++;
		}
		per_pipe = per_pipe->next;
	}
	return (0);
}

// /bin/cat Makefile| /usr/bin/grep all
// TODO: /bin/cat Makefile| /usr/bin/grep all > out

char	*get_path(t_env *env_lst, char *cmd)
{
	char  *path = get_value_from_key(env_lst, "PATH");
  // printf("get_value: %s\n", path);
  char  **comma_sep = ft_split(path, ':');
  char  *check_path;
  
  // this is for last /
  // ex) /bin => /bin/
  char  *tmp;
  
  int   i = 0;
  if (access(cmd, X_OK) == 0)
    return (cmd);
  while (comma_sep[i])
  {
    // printf("[sep]: %s\n", comma_sep[i]);
    tmp = ft_strjoin(comma_sep[i], "/");
    check_path = ft_strjoin(tmp, cmd);
    if (access(check_path, X_OK) == 0)
      return (free(tmp), check_path);
    free(tmp);
    free(check_path);
    i++;
  }
  return (NULL);
}

char  **get_cmd(char **head_cmdline)
{
  int i;
  int size;

  size = count_until_redirection(head_cmdline);
  // printf("size: %d\n", size);
  char  **result = malloc(sizeof(char *) * (size + 1));
  
  i = 0;
  while (i < size)
  {
    result[i] = head_cmdline[i];
    i++;
  }
  result[i] = NULL;
  return (result);
}

// /bin/cat Makefile > out1 > out2
t_cmd_data  *redirect(t_token *token, char **envp)
{
  t_cmd_data  *set = malloc(sizeof(t_cmd_data));
  t_env *env_lst = create_env_lst(envp);
//  int fd = dup(STDOUT_FILENO);
 int	fd; 
  // $PATHからpathを得て代入
  // get_cmd関数はリダイレクトまでの配列を二次元配列にする
  set->path = get_path(env_lst, token->command_line[0]);
  set->cmd = get_cmd(&token->command_line[0]);

  int i = 0;
  while (token->command_line[i] != NULL)
  {
    if (ft_strncmp(token->command_line[i], ">", 2) == 0)
    {
      fd = open(token->command_line[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
      dup2(fd, STDOUT_FILENO);
      close(fd);
    }
    else if (ft_strncmp(token->command_line[i], ">>", 3) == 0)
    {
      fd = open(token->command_line[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
      dup2(fd, STDOUT_FILENO);
      close(fd);
    }
    else if (ft_strncmp(token->command_line[i], "<", 2) == 0)
    {
      fd = open(token->command_line[i + 1], O_RDONLY, 0644);
      dup2(fd, STDIN_FILENO);
      close(fd);
    }
    else if (ft_strncmp(token->command_line[i], "<<", 3) == 0)
    {
      here_doc(token->command_line[i + 1]);
    }
    i++;
  }
//  dup2(fd, stdout_fileno);
//  close(fd);
  return (set);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*head;
	t_env	*env_lst;
	t_token	*token;
	(void)argv;
	(void)argc;

	env_lst = create_env_lst(envp);
	head = env_lst;
	// test_main(env_lst);
	token = lexer(argv[1]);
	if (pass_token_to_expand(env_lst, token) == 1)
		return (1);
	// printf("\t--- Result---\n\n");
	execute_command_line(token, env_lst);
	// Print(token);
	env_lstclear(&head, free_env_node);
}
