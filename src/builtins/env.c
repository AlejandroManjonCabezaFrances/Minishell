/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:13:38 by amanjon-          #+#    #+#             */
/*   Updated: 2024/01/15 15:27:29 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_print_lst_2(t_env *temp)
{
	while (temp)
	{
		printf("temp = %s\n", temp->content);
		temp = temp->next;
	}
}

t_env	*ft_lstnew_str_env(char *str_env)
{
	t_env	*node;

	node = NULL;
	node = malloc(sizeof(t_env));
	if (node == NULL)
		return (NULL);
	node->content = ft_strdup(str_env);
	node->next = NULL;
	return (node);
}

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
	}
}

/**
 * Create linked list of environment
 * @param	t_env **t_env, char **env
 * @return	void
*/
void	ft_linked_list_env(t_env **envi, char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		ft_lstadd_back_str_env(envi, ft_lstnew_str_env(env[i]));
		i++;	
	}
}