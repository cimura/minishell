/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 00:01:32 by cimy              #+#    #+#             */
/*   Updated: 2024/11/21 00:30:24 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

static bool is_redirection(char *arg)
{
  if (ft_strncmp(arg, ">", 2) == 0
		|| ft_strncmp(arg, ">>", 3) == 0
		|| ft_strncmp(arg, "<", 2) == 0
    || ft_strncmp(arg, "<<", 3) == 0)
    return (true);
  else
    return (false);
}

int check_syntax(t_env *env_lst, t_token *token)
{
  int i;
  (void)env_lst;

  while (token != NULL)
  {
    i = 0;
    while (token->command_line[i] != NULL)
    {
      if (is_redirection(token->command_line[i]) && token->command_line[i + 1] == NULL)
      {
        ft_putendl_fd("syntax error", STDERR_FILENO);
        return (1);
      }
      i++;
    }
    token = token->next;
  }
  return (0);
}