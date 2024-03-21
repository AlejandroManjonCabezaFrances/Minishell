/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 08:03:09 by amanjon-          #+#    #+#             */
/*   Updated: 2024/03/21 15:26:23 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	del(void *content)
{
	free(content);
}

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*next;

	if (lst != NULL && del != NULL)
	{
		while (*lst != NULL)
		{
			next = (*lst)->next;
			(*del)((*lst)->content);
			free(*lst);
			*lst = (*lst)->next;
		}
	}
}

/* int	main(void)
{
	t_list	*node1;
	t_list	*node2;
	int		*content1;
	int		*content2;

	content1 = 0;
	content2 = 0;
	node1 = ft_lstnew(content1);
	node2 = ft_lstnew(content2);
	node1 = ft_lstnew("hola");
	node2 = ft_lstnew("adios");

	node1->next = node2;
	ft_lstclear(&node1, &del);
	while(node1)
	{
		printf("%s\n", node1->content);
		node1 = node1->next;
	}

	if(node1 == NULL)
		printf("the list is empty.\n");
	else
		printf("the list is not empty\n");
	return(0);
} */

/* Descripción Itera la lista ’lst’ y aplica la función ’f’
en el contenido de cada nodo.
Parámetros lst: un puntero al primer nodo.f: un puntero
 a la función que utilizará cada nodo.
Libera la memoria de todos los nodos de una lista y los
 borra."la lista estará vacía"  */
