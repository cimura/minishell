/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 00:01:32 by cimy              #+#    #+#             */
/*   Updated: 2024/11/22 16:50:23 by cimy             ###   ########.fr       */
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

static int	white_space(char check_chr)
{
	if (check_chr == ' ' || check_chr == '\t' || check_chr == '\n' || \
		check_chr == '\v' || check_chr == '\f' || check_chr == '\r')
		return (1);
	else
		return (0);
}

int check_quotation(char *line)
{
  int i;
  int s_flag;
  int d_flag;

  i = 0;
  s_flag = 0;
  d_flag = 0;
  while (line[i] != '\0')
  {
    if (s_flag == 0 && d_flag == 0 && line[i] == '\'')
      s_flag = 1;
    else if (s_flag == 0 && d_flag == 0 && line[i] == '\"')
      d_flag = 1;
    else if (s_flag == 1 && line[i] == '\'')
      s_flag = 0;
    else if (d_flag == 1 && line[i] == '\"')
      d_flag = 0;
    i++;
  }
  if (s_flag == 1 || d_flag == 1)
  {
    return (1);
  }
  return (0);
}

int check_syntax_before_lexer(char *line)
{
  // int   i;
  // pipe単体 ex) "|"
  if (line[0] == '|' && (line[1] == '\0' || white_space(line[1])))
  {
    ft_putendl_fd("syntax error", STDERR_FILENO);
    return (1);
  }
  if (check_quotation(line) == 1)
  {
    ft_putendl_fd("syntax error", STDERR_FILENO);
    return (1);
  }
  // i = 0;
  // while (line[i] != '\0')
  // {
    // トークンの中身がカラ
    // ex) "echo | | "
    // if (line[i] == '|')
    // {
    //   while(white_space(line[i]))
    //     i++;
    //   if (line[i] == '|')
    //   {
    //      ft_putendl_fd("syntax error", STDERR_FILENO);
    //     return (1);
    //   }
  //   i++;
  // }
  return (0);
}

// TODO
// case1: " echo hi |   |  "
// case2: " echo hi |  "|" " の区別
int check_syntax(t_env *env_lst, t_token *token)
{
  int i;
  (void)env_lst;

  while (token != NULL)
  {
    i = 0;
    
    // case1 の対応
    if (token->command_line[0] == NULL)
    {
      ft_putendl_fd("syntax error", STDERR_FILENO);
      return (1);
    }
    while (token->command_line[i] != NULL)
    {
      // リダイレクト先がない　ex)" echo > "
      if (is_redirection(token->command_line[i]) && token->command_line[i + 1] == NULL)
      {
        ft_putendl_fd("syntax error", STDERR_FILENO);
        return (1);
      }
      // 変なやつ　ex) " echo >>> out "
      // <<<　みたいなのはあるっぽいから入れてない
      if (ft_strncmp(token->command_line[i], ">>>", 3) == 0)
      {
        ft_putendl_fd("syntax error", STDERR_FILENO);
        return (1);
      }
      if (ft_strncmp(token->command_line[i], ">|", 2) == 0
          || ft_strncmp(token->command_line[i], "<|", 2) == 0
          || ft_strncmp(token->command_line[i], "|<", 2) == 0
          || ft_strncmp(token->command_line[i], "|>", 2) == 0)
      {
        ft_putendl_fd("syntax error", STDERR_FILENO);
        return (1);
      }
      i++;
    }
    token = token->next;
    // if (token->command_line[0] == NULL && token != NULL)
    //   return (1);
  }
  return (0);
}
