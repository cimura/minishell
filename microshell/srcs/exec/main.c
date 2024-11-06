#include "exec.h"

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
  int fd;
  
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
      //heredoc();
    }
    i++;
  }
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
	printf("\t--- Result---\n\n");
	execute_command_line(token, envp);
	// Print(token);
	env_lstclear(&head, free_env_node);
}
