/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 11:17:26 by marvin            #+#    #+#             */
/*   Updated: 2023/12/26 11:17:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parse(t_token *token, t_scmd **scmds_list)
{
	t_scmd	*simple_cmd;
	t_token	*aux;

	simple_cmd = NULL;
	while (token)
	{
		if (token->type == PIPE)
			token = token->next;
		else
		{
			simple_cmd = ms_lstnew_cmd(token->content);
			ms_lstadd_back_smcd(scmds_list, simple_cmd);
			token = token->next;
			aux = token;
			while (aux->type != PIPE || aux->type != IN_REDIR ||
			aux->type != OUT_REDIR || aux->type != HEREDOC ||
			aux->type != APPEND)
			{
				simple_cmd->arg_count++;
				aux = aux->next;
			}
			if (simple_cmd->arg_count != 0)
			{
				simple_cmd->cmd_args = malloc(sizeof(char *) * (simple_cmd->arg_count + 1));
				// if (simple_cmd->cmd_args == NULL)
				// 	return (NULL);
				simple_cmd->cmd_args[simple_cmd->arg_count] = NULL;
				simple_cmd->arg_count--;
				while (simple_cmd->arg_count >= 0)
				{
					simple_cmd->cmd_args[simple_cmd->arg_count] = ft_strdup(token->content);
					simple_cmd->arg_count--;
					token = token->next;
				}
			}
		}
	}
}