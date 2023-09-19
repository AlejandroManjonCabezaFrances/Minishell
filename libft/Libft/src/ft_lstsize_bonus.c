/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:09:51 by amanjon-          #+#    #+#             */
/*   Updated: 2023/05/23 11:02:40 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_lstsize(t_list *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}

/* int	main(void)
{
	t_list *node1;
	t_list *node2;

	node1 = ft_lstnew("holaaaa");
	node2 = ft_lstnew("adiooss");
	node1->next = node2;

	printf("%d", ft_lstsize(node1));
	return (0);
} */

/* Cuenta el número de nodos de una lista. */
/* Valor devuelto La longitud de la lista. */