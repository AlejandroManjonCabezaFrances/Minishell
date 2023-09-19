/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:53:18 by amanjon-          #+#    #+#             */
/*   Updated: 2023/06/22 12:00:18 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	while (lst != NULL)
	{
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
	return (lst);
}

/* int	main(void)
{
	t_list *first_node;
	t_list *second_node;
	t_list *third_node;
	t_list *last_node;
	int i;

	first_node = ft_lstnew("hola");
	second_node = ft_lstnew("mundo");
	third_node = ft_lstnew("bonito");
	i = 1;
	ft_lstadd_back(&first_node, second_node);	// Enlazar lista	
	ft_lstadd_back(&first_node, third_node);
	last_node = ft_lstlast(first_node);				
	printf("%p\n", last_node);			//direccion del puntero al último nodo
	printf("%s\n", last_node->content);		//contenido del último nodo
	while(first_node)
	{
		printf("%d %s\n", i, first_node->content);
		first_node = first_node->next;
		i++;
	}		
	return(0);
}  */

/* Descripción Devuelve el último nodo de la lista.*/
