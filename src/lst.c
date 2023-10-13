/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 11:48:57 by amanjon-          #+#    #+#             */
/*   Updated: 2023/10/13 16:58:36 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_node	*ft_lstnew_mshell(char *content)
{
	t_node	*k;

	k = malloc(sizeof(t_node));
	if (k == NULL)
		return (NULL);
	k->content = content;
	k->next = NULL;
	return (k);
}

void	ft_lstadd_back_mshell(t_node **lst, t_node *new)
{
	t_node	*aux;

	aux = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	else
	{
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = new;
	}
}

void	ft_print_lst(t_node *temp)
{
	while (temp)
	{
		printf("temp = %s\n", temp->content);
		temp = temp->next;
	}
}

void	ft_lstclear_mshell(t_node **lst)
{
	t_node	*aux;

	while (*lst)
	{
		aux = (*lst)->next;
		free(*lst);
		(*lst) = aux;
	}
	*lst = NULL;
}