/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipalaci <vipalaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 11:57:51 by vipalaci          #+#    #+#             */
/*   Updated: 2024/02/27 15:15:37 by vipalaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ms_print_lst(t_token *token)
{
	printf("--token list--\n");
	while (token)
	{
		printf("token = -%s- type = -%d-\n", token->content, token->type);
		token = token->next;
	}
}

t_token	*ms_lstnew(void)
{
	t_token	*new;

	new = NULL;
	new = malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->type = INIT_INT;
	new->content = NULL;
	new->next = NULL;
	return (new);
}

void	ms_lstadd_back(t_token **list, t_token *new)
{
	t_token	*aux;

	aux = *list;
	if (*list == NULL)
	{
		*list = new;
		return ;
	}
	else
	{
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = new;
	}
}

void	ms_lstclear(t_token **list)
{
	t_token	*aux;

	if (list != NULL)
	{
		while (*list)
		{
			aux = (*list)->next;
			free(*list);
			(*list) = aux;
		}
		*list = NULL;
	}
}
