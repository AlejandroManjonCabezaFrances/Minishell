/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vini <vini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 11:58:28 by vipalaci          #+#    #+#             */
/*   Updated: 2024/03/06 20:16:20 by vini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_dsign(char c)
{
	if (c == '$')
		return (TRUE);
	return (FALSE);
}

int	is_space(char c)
{
	if (c == ' ')
		return (TRUE);
	return (FALSE);
}

int	is_qte(char c)
{
	if (c == '\'')
		return (SINGLE_QUOTE);
	if (c == '"')
		return (DOUBLE_QUOTE);
	return (FALSE);
}

int	is_operator(char c)
{
	if (c == '|')
		return (PIPE);
	if (c == '<')
		return (IN_REDIR);
	if (c == '>')
		return (OUT_REDIR);
	return (FALSE);
}

int	operator_type(char *input, int i)
{
	if (input[i] == '>' && input[i + 1] == '>')
		return (APPEND);
	else if (input[i] == '<' && input[i + 1] == '<')
		return (HEREDOC);
	else if (input[i] == '>')
		return (OUT_REDIR);
	else if (input[i] == '<')
		return (IN_REDIR);
	else if (input[i] == '|')
		return (PIPE);
	return (FALSE);
}
