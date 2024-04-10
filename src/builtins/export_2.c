/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:05:29 by amanjon-          #+#    #+#             */
/*   Updated: 2024/03/28 15:05:29 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Manipulates the pointers of the nodes of the head, tail and middle linked list
 * @param	t_env **envi, t_env **aux, t_env **new_node
 * @return	static void
*/
static	void	ft_handle_head_tail(t_env **envi, t_env **aux, t_env **new_node)
{
	if (ft_strcmp((*aux)->content, (*envi)->content) == 0)
	{
		*envi = *new_node;
		*aux = *envi;
	}
	else
	{
		*aux = (*aux)->prev;
		(*aux)->next = *new_node;
	}
}

/**
 * The non-existing variable to be exported will be parsed.
 * @param	char *cmd
 * @return	 var_parsed. Parsed mallocated string
*/
static	char	*ft_parser_arguments_2(char *cmd)
{
	int		i;
	int		len;
	int		start;
	char	*var_parsed;

	i = 0;
	len = 0;
	while (cmd[i] && cmd[i] != '=')
		i++;
	while (cmd[i] != ' ' && i >= 0)
		i--;
	i++;
	start = i;
	while (cmd[i] && cmd[i] != ' ')
	{
		len++;
		i++;
	}
	var_parsed = ft_substr(cmd, start, len);
	return (var_parsed);
}

/**
 * Replaces the existing environment variable node parsed for builtin export
 * @param	t_env **envi, t_env *aux, char *cmd
 * @return	void
*/
void	ft_trim_replace_node_parsed(t_env **envi, t_env *aux, char *cmd)
{
	t_env	*node_free;
	t_env	*new_node;
	char	*var_parsed;

	node_free = NULL;
	node_free = aux;
	var_parsed = ft_parser_arguments_2(cmd);
	new_node = ft_lstnew_str_env(var_parsed);
	free (var_parsed);
	new_node->next = aux->next;
	if (aux->next != NULL)
		aux->next->prev = new_node;
	new_node->prev = aux->prev;
	ft_handle_head_tail(envi, &aux, &new_node);
	ft_lstdelone_ms(&node_free, &del_ms);
}

/**
 * Replaces the existing environment variable node parsed for builtin export
 * @param	t_env **envi, char *cmd
 * @return	void
*/
void	ft_replace_node_parsed(t_env **envi, char *cmd)
{
	t_env	*aux;
	int		len;

	aux = *envi;
	len = 0;
	while (cmd[len] != '=')
		len++;
	while (aux)
	{
		if (ft_strncmp(aux->content, cmd, len) == 0)
		{
			ft_trim_replace_node_parsed(envi, aux, cmd);
			break ;
		}
		aux = aux->next;
	}
}

/**
 * This function searches to see if the variable you want to export exists.
 * @param	char **cmd, t_env **envi, int i
 * @return	(TRUE) --> env var exists or (FALSE)
*/
int	ft_env_var_exists(char **cmd, t_env **envi, int i)
{
	t_env	*aux;
	int		len;

	aux = *envi;
	while (aux)
	{
		len = 0;
		while (aux->content[len] != '=' && aux->content[len])
			len++;
		if (ft_strncmp(cmd[i], aux->content, len) == 0)
			return (TRUE);
		aux = aux->next;
	}
	return (FALSE);
}
