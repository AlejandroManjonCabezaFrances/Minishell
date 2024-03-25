/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 02:33:47 by marvin            #+#    #+#             */
/*   Updated: 2024/03/24 02:33:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Manipulates the pointers of the nodes of the head, tail and middle linked list
 * @param	t_env **envi, t_env *aux, t_env *new_node
 * @return	void
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
 * @param	t_env *envi, char *cmd
 * @return	void
*/
void	ft_replace_node_parsed(t_env **envi, char *cmd)
{
	t_env	*aux;
	t_env	*node_free;
	t_env	*new_node;
	int		len;

	aux = *envi;
	node_free = NULL;
	len = 0;
	while (cmd[len] != '=')
		len++;
	while (aux)
	{
		if (ft_strncmp(aux->content, cmd, len) == 0)
		{
			printf("aux->content = %s\n", aux->content);
			node_free = aux;
			new_node = ft_lstnew_str_env(ft_parser_arguments_2(cmd));
			new_node->next = aux->next;
			if (aux->next != NULL)
				aux->next->prev = new_node;


			new_node->prev = aux->prev;
			ft_handle_head_tail(envi, &aux, &new_node);
			ft_lstdelone_ms(&node_free, &del_ms);
			break ;
		}
		aux = aux->next;
	}
}

/**
 * This function searches to see if the variable you want to export exists.
 * @param	char **cmd, t_env *envi
 * @return	(TRUE) --> env var exists
*/
int	ft_check_env_var_exists(char **cmd, t_env **envi, int i)
{
	t_env	*aux;
	int		len;

	aux = *envi;
	// printf("***************************\n\n");
	// ft_print_lst_2(aux);
	// printf("***************************\n\n");
	while (aux)
	{
		len = 0;
		while (aux->content[len] != '=' && aux->content[len])
			len++;
		if (ft_strncmp(cmd[i], aux->content, len) == 0)
		{
			return (TRUE);
		}
		aux = aux->next;
	}
	return (FALSE);
}

/**
 * Look for a "=" in the received string
 * @param	char *str
 * @return	TRUE, FALSE
*/
int	ft_is_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (TRUE);
		i++;
	}
	return (FALSE);
}