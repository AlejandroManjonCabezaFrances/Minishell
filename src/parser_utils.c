/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipalaci <vipalaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:30:55 by vipalaci          #+#    #+#             */
/*   Updated: 2024/02/14 12:53:58 by vipalaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	create_node(t_token *token, t_token **wordlist)
{
	t_token	*word;

	word = ms_lstnew();
	word->type = token->type;
	word->content = token->content;
	ms_lstadd_back(wordlist, word);
}

t_token	*create_scmd(t_token *token, t_scmd **scmds_list)
{
	t_scmd	*simple_cmd;

	simple_cmd = ms_cmdnew();
	while (token && token->type != PIPE)
	{
		create_node(token, &simple_cmd->wordlist);
		token = token->next;
	}
	ms_cmdadd_back(scmds_list, simple_cmd);
	return (token);
}

int	is_redir(int type)
{
	if (type == IN_REDIR || type == OUT_REDIR
		|| type == HEREDOC || type == APPEND)
		return (1);
	return (0);
}

int	check_pipe(t_token *token)
{
	if (!token)
		return (0);
	if (token->type == PIPE)
		return (0);
	return (1);
}

int	check_redir(t_token *token)
{
	if (!token)
		return (0);
	if (is_redir(token->type))
		return (0);
	return (1);
}
