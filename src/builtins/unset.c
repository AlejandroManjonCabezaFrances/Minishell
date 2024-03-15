/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:13:17 by amanjon-          #+#    #+#             */
/*   Updated: 2024/03/15 09:38:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// gcc -Wall -Werror -Wextra ../../libft/Libft/src/ft_putstr_fd.c ../utils.c unset.c ../sandbox2.c ../../libft/Libft/src/ft_strtrim.c ../../libft/Libft/src/ft_strjoin.c builtins.c env.c echo.c exit.c pwd.c export.c cd.c -o unset && ./unset

// ################ env -i ./minishell ######################
// gcc -Wall -Werror -Wextra ../../libft/Libft/src/ft_putstr_fd.c ../utils.c unset.c ../sandbox2.c ../../libft/Libft/src/ft_strtrim.c ../../libft/Libft/src/ft_strjoin.c builtins.c env.c echo.c exit.c pwd.c export.c cd.c -o unset && env -i ./unset
// ################ env -i ./minishell ######################

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
	// t_env	*node_free;
	int		len;

	aux = *envi;
	// node_free = NULL;
	while (aux)
	{
		len = 0;
		while (aux->content[len] != '=')
			len++;
		if (ft_strncmp(cmd, aux->content, len) == 0)
		{
			// node_free = aux;
			ft_handle_list_header_and_tail(envi, &aux);
			// ft_lstdelone_ms(node_free, &del_ms);
		}
		aux = aux->next;
	}
	// printf("\n\n");
	// ft_print_lst_2(*envi);
	// printf("\n\n");
}

void	ft_unset(char **cmd, t_env **envi)
{
	int i;

	i = 1;
	if (*cmd == NULL || cmd == NULL)
		return ;
	while (cmd[i])
	{
		ft_delete_node(envi, cmd[i]);
		i++;
	}
	// ft_print_lst_2(*envi);		// para checkear
}
