/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:32:18 by ttakino           #+#    #+#             */
/*   Updated: 2024/12/10 18:02:34 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_handler.h"

extern int	g_global;

void	sigint_handler_in_heredoc(int signum)
{
	int	pipefd[2];

	(void)signum;
	g_global = 1;
	if (pipe(pipefd) < 0)
		perror("pipe: ");
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		perror("dup2");
	write(pipefd[1], "", 1);
	close(pipefd[0]);
	close(pipefd[1]);
}

void	sigint_handler_non_nl(int signum)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void)signum;
}
