/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins_4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 06:39:18 by amanjon-          #+#    #+#             */
/*   Updated: 2024/04/09 10:56:07 by amanjon-         ###   ########.fr       */
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
	// printf("pwd_oldpwd = %s\n", pwd_oldpwd);
	free (pwd_oldpwd);			// NEW
	free (var_join);
}

/**
 * Replaces the existing environment variable node
 * @param	t_env *aux, t_env *aux2, t_env *node_free, t_env *new_node
 * @return	void
*/
static void	ft_trim_3(t_env **aux, t_env **aux2, t_env **node_free, t_env **new_node)
{
	// printf("ft_trim_3________1\n");
	(*aux)->next = *new_node;
	// printf("ft_trim_3________2\n");
	(*new_node)->prev = *aux;
	// printf("ft_trim_3________3\n");
	if (*aux2)
	{
		// printf("ft_trim_3________4\n");
		(*aux2)->prev = *new_node;
		(*new_node)->next = *aux2;
	}
	else
		(*new_node)->next = NULL;
		// printf("ft_trim_3________5\n");
	ft_lstdelone_ms(node_free, &del_ms);
	// printf("ft_trim_3________6\n");
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
			// printf("ft_replace_node_1\n");
			ft_trim_1(&node_free, &aux, &aux2);
			// printf("ft_replace_node_2\n");
			ft_trim_2(str, pwd_oldpwd, &new_node);
			// printf("ft_replace_node_3\n");
			ft_trim_3(&aux, &aux2, &node_free, &new_node);
			// printf("ft_replace_node_4\n");
			break ;
		}
		aux = aux->next;
	}
}
