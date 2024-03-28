/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:04:41 by amanjon-          #+#    #+#             */
/*   Updated: 2024/03/28 15:04:41 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * We update the node by overwriting the content when --> env -i ./minishell
 * @param	t_env **envi, char *str, char *pwd_oldpwd
 * @return	static void
*/
static	void	ft_pwd_without_env(t_env **envi, char *str, char *pwd_oldpwd)
{
	char	*result_join;

	result_join = ft_strjoin(str, pwd_oldpwd);
	(*envi)->content = ft_strdup(result_join);
	free (result_join);
}

/**
 * Replaces the oldpwd of the linked list when --> env -i ./minishell
 * updating the pointers and deleting the node
 * @param	t_env *aux, char *str, char *pwd_oldpwd
 * @return	static void
*/
static	void	ft_oldpwd_without_env(t_env *aux, char *str, char *pwd_oldpwd)
{
	t_env	*node_free;
	t_env	*new_node;
	char	*result_join;

	node_free = NULL;
	result_join = NULL;
	node_free = aux;
	aux = aux->prev;
	result_join = ft_strjoin(str, pwd_oldpwd);
	new_node = ft_lstnew_str_env(result_join);
	free(result_join);
	if (aux->next->next != NULL)
		aux->next->next->prev = new_node;
	new_node->next = aux->next->next;
	aux->next = new_node;
	new_node->prev = aux;
	ft_lstdelone_ms(&node_free, &del_ms);
}

/**
 * Replaces the environment variables that this function receives as arguments
 * @param	t_env **envi, char *str, char *pwd_oldpwd
 * @return	void
*/
void	ft_replace_node_cd(t_env **envi, char *str, char *pwd_oldpwd)
{
	t_env	*aux;
	int		len;

	aux = *envi;
	len = 0;
	while (str[len] != '=')
		len++;
	while (aux)
	{
		if (ft_strncmp(aux->content, str, len + 1) == 0)
		{
			if (aux == *envi)
				ft_pwd_without_env(envi, str, pwd_oldpwd);
			else
				ft_oldpwd_without_env(aux, str, pwd_oldpwd);
			return ;
		}
		aux = aux->next;
	}
}
