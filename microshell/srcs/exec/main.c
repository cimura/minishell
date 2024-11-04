#include "../env/env_lst.h"
#include "../expander/expander.h"
#include "../lexer/lexer.h"

#include <stdbool.h>
#include <fcntl.h>

#define RESET   "\033[0m"   // リセット
#define RED     "\033[31m"  // 赤
#define GREEN   "\033[32m"  // 緑
#define YELLOW  "\033[33m"  // 黄
#define BLUE    "\033[34m"  // 青

typedef struct s_fd
{
  int tmp_fd[2];
  int in_fd;
  int out_fd;
} t_fd;

typedef struct s_cmd_data
{
  char  *path;
  char  **cmd;
} t_cmd_data;



// static void	print_commands(char **commands)
// {
// 	int	i;

// 	i = 0;
// 	while (commands[i])
// 	{
// 		printf("%s\n", commands[i++]);
// 	}
// }

// static void	Print(t_token *token)
// {
// 	while (token != NULL)
// 	{
// 		print_commands(token->command_line);
// 		token = token->next;
// 		if (token != NULL)
// 			printf("\tnext...\n");
// 	}
// }

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

// void	test_main(t_env *env_lst)
// {
// 	t_token	*token;
// 	char	*input;

// 	input = "echo hello$USER >cat out| ls  <<INFILE";
// 	token = lexer(input);
// 	assert(strcmp())
// }

// bool  is_builtin(t_token *token)
// {
//   return (ft_strncmp(token->command_line[0], "cd", 3) ||
//           ft_strncmp(token->command_line[0], "echo", 5) ||
//           ft_strncmp(token->command_line[0], "env", 4) ||
//           ft_strncmp(token->command_line[0], "exit", 5));
// }

// void	builtin_command(t_token *token)
// {
// 	if (ft_strncmp(token->command_line[0], "cd", 3))
// 		cd(&token->command_line[1]);
// 	else if (ft_strncmp(token->command_line[0], "echo", 5))
// 		echo(&token->command_line[1]);
// 	else if (ft_strncmp(token->command_line[0], "env", 4))
// 		env(&token->command_line[1]);
// 	else if (ft_strncmp(token->command_line[0], "exit", 5))
// 		exit(&token->command_line[1]);
// 	else if (ft_strncmp(token->command_line[0], "export", 7))
// 		export(&token->command_line[1]);
// 	else if (ft_strncmp(token->command_line[0], "pwd", 4))
// 		pwd(&token->command_line[1]);
// 	else if (ft_strncmp(token->command_line[0], "unset", 6))
// 		unset(&token->command_line[1]);
// }


// /bin/cat Makefile| /usr/bin/grep all
// TODO: /bin/cat Makefile| /usr/bin/grep all > out

t_cmd_data  *redirect(t_token *token)
{
  t_cmd_data  set;
  int fd;
  int i = 0;
  
  // $PATHからpathを得て代入
  // set.path = get_path(token->command_line[0]);
  // set.cmd = get_cmd(&token->command_line[i], i);

  while (token->command_line[i] != NULL)
  {
    if (ft_strncmp(token->command_line[i], ">", 2))
    {
      fd = open(token->command_line[i + 1], O_CREAT | O_WRONLY, 0644);
      dup2(fd, STDOUT_FILENO);
      close(fd);
    }
    else if (ft_strncmp(token->command_line[i], ">>", 3))
    {
      fd = open(token->command_line[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
      dup2(fd, STDOUT_FILENO);
      close(fd);
    }
    else if (ft_strncmp(token->command_line[i], "<", 2))
    {
      fd = open(token->command_line[i - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
      dup2(STDIN_FILENO, fd);
      close(fd);
    }
    else if (ft_strncmp(token->command_line[i], "<<", 3))
    {
      //heredoc();
    }
    i++;
  }
}

void	command(t_token *token, char **envp)
{
  t_cmd_data  *cmd;
	pid_t	pid;
  t_fd t;

  t.in_fd = STDIN_FILENO;
  t.out_fd = STDOUT_FILENO;
  if (pipe(t.tmp_fd) == -1)
    perror("pipe");
	pid = fork();
  if (pid == -1)
    perror("fork");
  
  cmd = redirect(token);
	if (pid == 0)
	{
    close(t.tmp_fd[0]);
    dup2(t.tmp_fd[1], STDOUT_FILENO);
    close(t.tmp_fd[1]);
    ft_putendl_fd(token->command_line[0], 2);
		if (execve(token->command_line[0], token->command_line, envp) == -1)
      perror("execve failed");
    exit(EXIT_FAILURE);
	}
	else
	{
    close(t.tmp_fd[1]);
		dup2(t.tmp_fd[0], STDIN_FILENO);
		close(t.tmp_fd[0]);
		wait(NULL);
	}
}

void  last_command(t_token *token, char **envp)
{
 	pid_t	pid;
  t_fd t;

  if (pipe(t.tmp_fd) == -1)
    perror("pipe");
	pid = fork();
  if (pid == -1)
    perror("fork");
	if (pid == 0)
	{
    close(t.tmp_fd[0]);
    dup2(STDOUT_FILENO, t.out_fd);
    close(t.tmp_fd[1]);
    ft_putendl_fd(token->command_line[0], 2);
		if (execve(token->command_line[0], token->command_line, envp) == -1)
      perror("execve failed");
    exit(EXIT_FAILURE);
	}
	else
	{
    close(t.tmp_fd[1]);
		dup2(t.tmp_fd[0], t.in_fd);
		close(t.tmp_fd[0]);
		wait(NULL);
    exit(EXIT_SUCCESS);
	} 
}

// 標準出力や標準入力はdup2によって書き換わるため，構造体でその値を保存しておく
// -> 最後とそれ以外で分ければいい
void	execute_command_line(t_token *token, char **envp)
{
	while (token != NULL)
	{
		// もしbuiltinコマンドの場合はforkは必要ない
    // if (is_builtin(token))
    //   builtin_command(token);
    // else
    if (token->next == NULL)
    {
      break ;
    }
    command(token, envp);
		token = token->next;
	}
    last_command(token, envp);
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
