/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:36:50 by amanjon-          #+#    #+#             */
/*   Updated: 2023/12/26 11:06:12 by marvin           ###   ########.fr       */
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

int	is_quote(char c)
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
