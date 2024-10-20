/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 15:05:29 by ttakino           #+#    #+#             */
/*   Updated: 2024/10/20 17:49:12 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	do_command(char **command, t_env *env_lst)
{
	int	i;

	i = 0;
	while (command[i] != NULL)
	{
		if (strcmp(command[i], "env") == 0)
			env(env_lst);
		else if (strcmp(command[i], "export") == 0)
			export(command[++i], env_lst);
		else if (strcmp(command[i], "unset") == 0)
			unset(env_lst, command[++i]);
		else
			return (printf("%s: command not found\n", command[i]), 1);
		i++;
	}
	return (0);
}

void free_command(char **command)
{
    for (int i = 0; command[i] != NULL; i++)
    {
        free(command[i]);
    }
    free(command);  // 最後に配列自体を解放
	command = NULL;
}

int main(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)argc;
	char *line = NULL;
	t_env	*env_lst;

	env_lst = ft_env_lst(envp);
	if (env_lst == NULL)
		return (printf("System Error: ft_env_lst\n"), 1);
	while (1)
	{
		line = readline("\x1b[33mbuiltin-shell>\x1b[0m ");

		if (!line)
		{
			printf("exit\n");
			break;
		}
		if (strlen(line) == 0)
		{
			free(line);
			continue;
		}
			// <command> <redirect> <command>の実行
		// if (include_redirect(line))
		//     redirect(line, envp);
		else
		{
			char **command = ft_split(line, ' ');

			if (command == NULL)
			{
			free(line);
				printf("exit\n");
				break;
			}
			if (do_command(command, env_lst) != 0)
				return (1);
			free_command(command);
		}
		if (strlen(line) > 0)
			add_history(line);
		free(line); // Free memory allocated by readline
	}
	return 0;
}
