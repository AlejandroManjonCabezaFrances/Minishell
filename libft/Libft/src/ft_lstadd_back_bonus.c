/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:29:36 by amanjon-          #+#    #+#             */
/*   Updated: 2023/10/26 15:13:19 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*aux;

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

/* int	main(void)
{
	t_list *head;
	t_list *new;

	head = ft_lstnew("hola");
	new = ft_lstnew("adios");
	ft_lstadd_back(&head, new);
	while (head)
	{
		printf("%s\n", head->content);
		head = head->next;
	}
	return (0);
} */

/* Descripción Añade el nodo ’new’ al final de la lista ’lst’. */
