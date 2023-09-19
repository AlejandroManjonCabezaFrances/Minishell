/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 07:29:51 by amanjon-          #+#    #+#             */
/*   Updated: 2023/05/22 10:10:39 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*k;

	k = malloc(sizeof(t_list));
	if (k == NULL)
		return (NULL);
	k->content = content;
	k->next = NULL;
	return (k);
}

/* int	main(void)
{
	char *content;
	
	content = "Hello world";
	printf("%p\n", ft_lstnew(content));
	printf("%s\n", content);
	return (0);
} */

/* int main(void)
{
    char *content = "hello world";
    t_list *node = ft_lstnew(content);

    if (node == NULL)
    {
        printf("Error: ft_lstnew failed\n");
        return (0);
    }

    printf("Content of node: %s\n", node->content);
    printf("direction node: %p\n", node->content);

    return 0;
} */

/* Descripción Crea un nuevo nodo utilizando malloc(3). La
variable miembro ’content’ se inicializa con el
contenido del parámetro ’content’. La variable
’next’, con NULL. */

/* Valor devuelto El nuevo nodo */