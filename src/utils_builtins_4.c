/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins_4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 06:39:18 by amanjon-          #+#    #+#             */
/*   Updated: 2024/04/10 17:24:44 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Replaces the existing environment variable node
 * @param	t_env *node_free, t_env *aux, t_env *aux2
 * @return	void
*/
static void	ft_trim_1(t_env **node_free, t_env **aux, t_env **aux2)
{
	*node_free = *aux;
	*aux2 = (*aux)->next;
	*aux = (*aux)->prev;
}

/**
 * Replaces the existing environment variable node
 * @param	char *str, char *pwd_oldpwd, t_env *new_node
 * @return	void
*/
static void	ft_trim_2(char *str, char *pwd_oldpwd, t_env **new_node)
{
	char	*var_join;

	var_join = NULL;
	var_join = ft_strjoin(str, pwd_oldpwd);
	*new_node = ft_lstnew_str_env(var_join);
	free (pwd_oldpwd);
	free (var_join);
}

/**
 * Replaces the existing environment variable node
 * @param	t_env *aux, t_env *aux2, t_env *node_free, t_env *new_node
 * @return	void
*/
static void	ft_trim_3(t_env **aux, t_env **aux2, t_env **n_free, t_env **new_n)
{
	(*aux)->next = *new_n;
	(*new_n)->prev = *aux;
	if (*aux2)
	{
		(*aux2)->prev = *new_n;
		(*new_n)->next = *aux2;
	}
	else
		(*new_n)->next = NULL;
	ft_lstdelone_ms(n_free, &del_ms);
}

/**
 * Replaces the existing environment variable node
 * @param	t_env *envi, char *str, char *pwd_oldpwd
 * @return	void
*/
void	ft_replace_node(t_env *envi, char *str, char *pwd_oldpwd)
{
	t_env	*aux;
	t_env	*aux2;
	t_env	*node_free;
	t_env	*new_node;
	int		len;

	aux = envi;
	aux2 = NULL;
	node_free = NULL;
	new_node = NULL;
	len = 0;
	while (str[len] != '=')
		len++;
	while (aux)
	{
		if (ft_strncmp(aux->content, str, len) == 0)
		{
			ft_trim_1(&node_free, &aux, &aux2);
			ft_trim_2(str, pwd_oldpwd, &new_node);
			ft_trim_3(&aux, &aux2, &node_free, &new_node);
			break ;
		}
		aux = aux->next;
	}
}
