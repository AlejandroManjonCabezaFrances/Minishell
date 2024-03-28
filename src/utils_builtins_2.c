/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:32:51 by amanjon-          #+#    #+#             */
/*   Updated: 2024/03/28 09:38:16 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Receives a string that will be allocated to create a node from our list
 * @param	char *str_env
 * @return	t_env
*/
t_env	*ft_lstnew_str_env(char *str_env)
{
	t_env	*node;

	node = NULL;
	node = malloc(sizeof(t_env));
	if (node == NULL)
		return (NULL);
	node->content = ft_strdup(str_env);
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

/**
 * Modified libft function. Adds the new node it receives to the last
 * position in the list
 * @param	t_env **envi, t_env *node
 * @return	void
*/
void	ft_lstadd_back_str_env(t_env **envi, t_env *node)
{
	t_env	*aux;

	aux = *envi;
	if (*envi == NULL)
	{
		*envi = node;
		return ;
	}
	else
	{
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = node;
		node->prev = aux;
	}
}

/**
 * Free to the content that receives the function
 * @param	void *content
 * @return	void
*/
void	del_ms(void *content)
{
	free(content);
}

/**
 * Free to the pointer that points to the node and free to the content
 * @param	t_env **lst, void (*del_ms)(void *)
 * @return	void
*/
void	ft_lstdelone_ms(t_env **lst, void (*del_ms)(void *))
{
	if (lst != NULL && *lst != NULL && del_ms != NULL)
	{
		(*del_ms)((*lst)->content);
		free(*lst);
		*lst = NULL;
	}
}

/**
 * Free al the pointers and contents of the entire list
 * @param	t_env **lst, void (*del)(void*)
 * @return	void
*/
void	ft_lstclear_ms(t_env **lst, void (*del)(void*))
{
	if (lst != NULL && del != NULL)
	{
		while (*lst != NULL)
		{
			(*del)((*lst)->content);
			free(*lst);
			*lst = (*lst)->next;
		}
	}
}
