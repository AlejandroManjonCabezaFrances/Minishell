/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 11:48:57 by amanjon-          #+#    #+#             */
/*   Updated: 2024/01/08 11:25:40 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_lst_ms(t_token *token, int type)
{
	while (token)
	{
		if (token->type == type)
			return (printf("requested type found\n"));
		token = token->next;
	}
	return (printf("requested type NOT found\n"));
}

void	print_lst_ms(t_token *token)
{
	while (token)
	{
		printf("token = -%s- type = -%d-\n", token->content, token->type);
		token = token->next;
	}
}

t_token	*lstnew_ms(void)
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

t_scmd	*lstnew_ms_cmd(char *content)
{
	t_scmd	*new;

	new = NULL;
	new = malloc(sizeof(t_scmd));
	if (new == NULL)
		return (NULL);
	new->cmd = ft_strdup(content);
	new->cmd_args = NULL;
	new->arg_count = 0;
	new->next = NULL;
	return (new);
}

void	lstadd_back_ms(t_token **list, t_token *new)
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

void	lstadd_back_ms_smcd(t_scmd **list, t_scmd *new)
{
	t_scmd	*aux;

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

void	lstclear_ms(t_token **list)
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
