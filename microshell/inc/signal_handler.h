/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakino <ttakino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:22:41 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/12 15:47:07 by ttakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLER_H

# define SIGNAL_HANDLER_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "libft.h"

# define SIGINT_RECEIVED	-1
# define BREAK				3

void	ft_signal(void);
void	ft_child_signal(void);
void	sigint_handler_in_heredoc(int signum);
void	sigint_handler_non_nl(int signum);

#endif
