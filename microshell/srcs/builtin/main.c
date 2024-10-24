/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 15:05:29 by ttakino           #+#    #+#             */
/*   Updated: 2024/10/23 19:35:03 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "builtin.h"

// int	do_command(char **command, t_env *env_lst)
// {
// 	int	i;

// 	i = 0;
// 	while (command[i] != NULL)
// 	{
// 		if (strcmp(command[i], "env") == 0)
// 		{
// 			env(env_lst);
// 		}
// 		else if (strcmp(command[i], "export") == 0)
// 		{
// 			if (export(command[++i], env_lst) != 0)
// 				return (1);
// 		}
// 		else if (strcmp(command[i], "unset") == 0)
// 			unset(env_lst, command[++i]);
// 		else if (strcmp(command[i], "echo") == 0)
// 		{
// 			echo(&command[++i]);
// 			while (command[i + 1] != NULL)
// 				i++;
// 		}
// 		else if (strcmp(command[i], "cd") == 0)
// 		{
// 			cd(command[1]);
// 			break ;
// 		}
// 		else if (strcmp(command[i], "pwd") == 0)
// 			pwd();
// 		else if (strcmp(command[i], "exit") == 0)
// 			exit(atoi(command[i + 1]));
// 		else
// 			return (printf("%s: command not found\n", command[i]), 1);
// 		i++;
// 	}
// 	return (0);
// }

// void free_command(char **command)
// {
// 	int	i;

// 	i = 0;
// 	while (command[i])
// 		free(command[i++]);
// 	free(command);
// 	command = NULL;
// }

// int main(int argc, char **argv, char **envp)
// {
// 	(void)argv;
// 	(void)argc;
// 	char *line = NULL;
// 	t_env	*env_lst;

// 	env_lst = create_env_lst(envp);
// 	if (env_lst == NULL)
// 		return (printf("System Error: create_env_lst\n"), 1);
// 	while (1)
// 	{
// 		line = readline("\x1b[33mbuiltin-shell>\x1b[0m ");

// 		if (strcmp(line, "exit") == 0)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		if (!line)
// 		{
// 			printf("exit\n");
// 			break ;
// 		}
// 		if (strlen(line) == 0)
// 		{
// 			free(line);
// 			continue ;
// 		}
// 		else
// 		{
// 			char **command = ft_split(line, ' ');

// 			if (command == NULL)
// 			{
// 				env_lstclear(&env_lst, free_env_node);
// 				free(line);
// 				printf("System Error: ft_split\n");
// 				return (1);
// 			}
// 			if (do_command(command, env_lst) != 0)
// 			{
// 				env_lstclear(&env_lst, free_env_node);
// 				free_command(command);
// 				free(line);
// 				return (1);
// 			}
// 			free_command(command);
// 		}
// 		if (strlen(line) > 0)
// 			add_history(line);
// 		free(line); // Free memory allocated by readline
// 	}
// 	env_lstclear(&env_lst, free_env_node);
// 	return 0;
// }
