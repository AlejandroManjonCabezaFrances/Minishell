/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:33:42 by amanjon-          #+#    #+#             */
/*   Updated: 2024/03/25 10:38:27 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*ft_lstlast_ms(t_env *lst)
{
	while (lst != NULL)
	{
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
	return (lst);
}

void	ft_convert_list_2(t_env *temp, char **env_array, int *count)
{
	int	i;

	while (temp)
	{
		env_array[*count] = ft_strdup(temp->content);
		if (env_array[*count] == NULL)
		{
			i = 0;
			while (i < (*count))
			{
				free(env_array[i]);
				i++;
			}
			free(*env_array);
			break ;
		}
		temp = temp->next;
		(*count)++;
	}
}

char	**ft_convert_list_to_double_pointer(t_env **envi)
{
	t_env	*temp;
	char	**env_array;
	int		count;

	temp = *envi;
	count = 0;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	env_array = malloc(sizeof(char *) * (count + 1));
	if (env_array == NULL)
		return (NULL);
	temp = *envi;
	count = 0;
	ft_convert_list_2(temp, env_array, &count);
	env_array[count] = NULL;
	return (env_array);
}

/**
 * Replaces the existing environment variable node
 * @param	t_env *aux, t_env *aux2, t_env *node_free, t_env *new_node
 * @return	void
*/
void	ft_trim(t_env *aux, t_env *aux2, t_env *node_free, t_env *new_node)
{
	aux->next = new_node;
	new_node->prev = aux;
	if (aux2)
	{
		aux2->prev = new_node;
		new_node->next = aux2;
	}
	else
		new_node->next = NULL;
	ft_lstdelone_ms(&node_free, &del_ms);
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
	len = 0;
	while (str[len] != '=')
		len++;
	while (aux)
	{
		if (ft_strncmp(aux->content, str, len) == 0)
		{
			node_free = aux;
			aux2 = aux->next;
			aux = aux->prev;
			new_node = ft_lstnew_str_env(ft_strjoin(str, pwd_oldpwd));
			ft_trim(aux, aux2, node_free, new_node);
			break ;
		}
		aux = aux->next;
	}
}