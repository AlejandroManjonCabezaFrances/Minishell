/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:13:17 by amanjon-          #+#    #+#             */
/*   Updated: 2024/03/24 02:04:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

static	void	ft_delete_node(t_env **envi, char *cmd)
{
	t_env	*aux;
	int		len;

	aux = *envi;
	while (aux)
	{
		len = 0;
		while (aux->content[len] != '=')
			len++;
		if (ft_strncmp(cmd, aux->content, len) == 0)
			ft_handle_list_header_and_tail(envi, &aux);
		aux = aux->next;
	}
}

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
