/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:31:29 by amanjon-          #+#    #+#             */
/*   Updated: 2023/05/22 10:08:54 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst != NULL && del != NULL)
	{
		(*del)(lst->content);
		free(lst);
	}
}

void	del(void *content)
{
	free(content);
}

/* int	main(void)
{
	t_list	*lst;
	
	lst = ft_lstnew("hola");
	while(lst)
	{
		printf("%s\n", lst->content);
		lst = lst->next;
	}
	ft_lstdelone(lst, &del);
	
	while(lst)
	{
		printf("%s\n", lst->content);
		lst = lst->next;
	}
	return(0);
} */

/* Descripción Toma como parámetro un nodo ’lst’ y libera la memoria
del contenido utilizando la función ’del’dada como parámetro, además
de liberar el nodo.?¿? La memoria de ’next’ no debe liberarse. ?¿?¿?*/

/* Parámetros lst: el nodo a liberar. del: un puntero a la función 
utilizada para liberar el contenido del nodo. */