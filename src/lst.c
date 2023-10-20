/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 11:48:57 by amanjon-          #+#    #+#             */
/*   Updated: 2023/10/20 17:03:14 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_print_lst(t_process *temp)
{
	while (temp)
	{
		printf("temp = %s\n", temp->content);
		temp = temp->next;
	}
}

t_process	*ft_lstnew_mshell(void)
{
	t_process	*k;

	k = NULL;
	k = malloc(sizeof(t_process));
	if (k == NULL)
		return (NULL);
	k->content = NULL;
	k->next = NULL;
	k->type_tokens = INIT_INT;
	return (k);
}

void	ft_lstadd_back_mshell(t_process **lst, t_process *new)
{
	t_process	*aux;
	
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

void	ft_lstclear_mshell(t_process **lst)
{
	t_process	*aux;

	while (*lst)
	{
		aux = (*lst)->next;
		free(*lst);
		(*lst) = aux;
	}
	*lst = NULL;
}
