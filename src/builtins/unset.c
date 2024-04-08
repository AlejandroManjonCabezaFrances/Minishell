/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:13:17 by amanjon-          #+#    #+#             */
/*   Updated: 2024/04/08 07:27:50 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * We manipulate the pointers correctly by paying attention to the first/last
 * node in the list
 * @param	t_env **envi, t_env **aux
 * @return	static void
*/
static	void	ft_handle_list_header_and_tail(t_env **envi, t_env **aux)
{
	t_env	*temp;
	t_env	*last_node;

	temp = *envi;
	last_node = ft_lstlast_ms(temp);
	if (*aux != last_node)
	{
		if (*aux != *envi)
		{
			*aux = (*aux)->prev;
			if ((*aux)->next != last_node)
			{
				(*aux)->next = (*aux)->next->next;
				(*aux)->next->prev = *aux;
			}
		}
		else
		{
			*envi = (*envi)->next;
			*aux = *envi;
		}
	}
}

/**
 * We look for the node we want to delete
 * @param	t_env **envi, char *cmd
 * @return	static void
*/
static	void	ft_delete_node(t_env **envi, char *cmd)
{
	t_env	*aux;
	t_env	*node_free;
	int		len;

	aux = *envi;
	node_free = NULL;
	while (aux)
	{
		len = 0;
		while (aux->content[len] != '=')
			len++;
		if (ft_strncmp(cmd, aux->content, len) == 0)
		{
			node_free = aux;
			ft_handle_list_header_and_tail(envi, &aux);
			ft_lstdelone_ms(&node_free, &del_ms);		// NEW *********************
		}
		aux = aux->next;
	}
}

/**
 * Replicates the "unset" builtin like bash.
 * @param	char **cmd, t_env **envi
 * @return	void
*/
void	ft_unset(char **cmd, t_env **envi)
{
	int	i;

	i = 1;
	if (*cmd == NULL || cmd == NULL)
		return ;
	while (cmd[i])
	{
		ft_delete_node(envi, cmd[i]);
		i++;
	}
}
