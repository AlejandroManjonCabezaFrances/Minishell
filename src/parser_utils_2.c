/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vini <vini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 10:28:24 by vipalaci          #+#    #+#             */
/*   Updated: 2024/04/11 18:03:57 by vini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	open_append(t_scmd *scmd, t_token *token)
{
	if (scmd->outfile != -1)
		close(scmd->outfile);
	scmd->outfile = open(token->content, O_APPEND | O_CREAT | O_RDWR, 0644);
	if (scmd->outfile < 0)
		return (OUTFILE_ERR);
	return (1);
}

int	open_outfile(t_scmd *scmd, t_token *token)
{
	if (scmd->outfile != -1)
		close(scmd->outfile);
	scmd->outfile = open(token->content, O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (scmd->outfile < 0)
		return (OUTFILE_ERR);
	return (1);
}

int	open_infile(t_scmd *scmd, t_token *token)
{
	if (scmd->infile != -1)
		close(scmd->infile);
	scmd->infile = open(token->content, O_RDONLY, 0644);
	if (scmd->infile < 0)
		return (INFILE_ERR);
	return (1);
}

int	check_files(t_scmd *scmd)
{
	t_token	*aux;
	int		err;

	aux = scmd->wordlist;
	err = 1;
	while (aux)
	{
		if (aux->type == IN_REDIR)
			err = open_infile(scmd, aux->next);
		else if (aux->type == OUT_REDIR)
			err = open_outfile(scmd, aux->next);
		else if (aux->type == APPEND)
			err = open_append(scmd, aux->next);
		else if (aux->type == HEREDOC)
		{
			if (scmd->infile != -1)
				close(scmd->infile);
			err = open_heredoc(scmd, aux->next);
		}
		if (err != 1)
			return (err);
		aux = aux->next;
	}
	free(aux);
	return (err);
}
