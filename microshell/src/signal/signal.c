/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:16:02 by ttakino           #+#    #+#             */
/*   Updated: 2024/11/17 15:05:16 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_handler.h"

void	sigint_handler_child(int signum)
{
	printf("sigchild_handler\n");
	//fflush(stdout);
	(void)signum;
}

void	sigquit_handler_child(int signum)
{
	printf("Quit\n");
	(void)signum;
}

void	sigint_handler(int signum)
{
	printf("sigint_handler\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void)signum;
}

void	ft_signal(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

//int main(int argc, char **argv, char **envp)
//{
//	(void)argv;
//	(void)argc;
//	(void)envp;
//	char *line = NULL;

//	ft_signal();

//	while (1)
//	{
//		line = readline("minishell> ");

//		if (line == NULL)
//		{
//		  printf("exit\n");
//		  break;
//		}
//		if (ft_strlen(line) == 0)
//		{
//		  free(line);
//		  continue;
//		}
//		else
//		{
//			printf("input: %s\n", line);
//		}
//		if (ft_strlen(line) > 0)
//			add_history(line);
//		free(line); // Free memory allocated by readline
//	}
//	return (0);
//}
