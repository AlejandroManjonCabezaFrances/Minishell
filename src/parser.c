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

// void	parse_cmd(t_token **token_list)
// {
// }

void	parser(t_token **token_list)
{
	t_token	*aux;

	aux = *token_list;
	while (aux->next)
	{
		if (aux->type == PIPE)
		{
			parse_pipe(token_list);
			return ;
		}
		aux = aux->next;
	}
	parse_cmd(token_list);
}