/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:16:02 by ttakino           #+#    #+#             */
/*   Updated: 2024/11/19 19:59:02 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_handler.h"

void	sigint_handler_child(int signum)
{
	ft_putstr_fd("\n", STDOUT_FILENO);
	//fflush(stdout);
	(void)signum;
}

void	sigquit_handler_child(int signum)
{
	ft_putstr_fd("Quit\n", STDOUT_FILENO);
	(void)signum;
}

void	sigint_handler(int signum)
{
	rl_on_new_line();
	ft_putstr_fd("\n", STDOUT_FILENO);
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
//		  ft_putstr_fd("exit\n");
//		  break;
//		}
//		if (ft_strlen(line) == 0)
//		{
//		  free(line);
//		  continue;
//		}
//		else
//		{
//			ft_putstr_fd("input: %s\n", line);
//		}
//		if (ft_strlen(line) > 0)
//			add_history(line);
//		free(line); // Free memory allocated by readline
//	}
//	return (0);
//}
