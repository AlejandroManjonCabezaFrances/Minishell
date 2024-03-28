/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:33:42 by amanjon-          #+#    #+#             */
/*   Updated: 2024/03/28 08:54:25 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * We put quotes around the content of the environment variables
 * with the "bubble sort".
 * @param	t_env *copy_lst
 * @return	static	void
*/
static	void	ft_put_quotes_in_declare(t_env *copy_lst)
{
	t_env	*aux;
	int		len;

	aux = copy_lst;
	while (aux)
	{
		ft_putstr_fd("declare -x ", 1);
		len = 0;
		while (aux->content[len])
		{
			if (aux->content[len] != '=')
				ft_putchar(aux->content[len]);
			else
			{
				ft_putchar('=');
				ft_putchar('\"');
			}
			if (aux->content[len + 1] == '\0'
				&& (ft_is_equal(aux->content) == TRUE))
				ft_putchar('\"');
			len++;
		}
		ft_putchar('\n');
		aux = aux->next;
	}
}

/**
 * This function sorts the environment alphabetically with the "bubble sort"
 * @param	t_env *envi
 * @return	static	void
*/
static	void	ft_export_without_argv_sort(t_env *envi)
{
	t_env	*temp;
	t_env	*head;
	char	*aux;

	head = envi;
	temp = envi;
	while (temp->next != NULL)
	{
		if (ft_strcmp(temp->content, temp->next->content) > 0)
		{
			aux = temp->content;
			temp->content = temp->next->content;
			temp->next->content = aux;
			temp = head;
		}
		else
			temp = temp->next;
	}
}

/**
 * We make a copy of the env list
 * @param	t_env *envi
 * @return	static	t_env
*/
static	t_env	*ft_copy_lst_to_declare(t_env *envi)
{
	t_env	*dest;
	t_env	*temp_envi;
	t_env	*temp_dest;

	dest = NULL;
	temp_envi = envi;
	temp_dest = NULL;
	while (temp_envi != NULL)
	{
		if (dest == NULL)
		{
			dest = ft_lstnew_str_env(temp_envi->content);
			temp_dest = dest;
		}
		else
		{
			temp_dest->next = ft_lstnew_str_env(temp_envi->content);
			temp_dest = temp_dest->next;
		}
		temp_envi = temp_envi->next;
	}
	return (dest);
}

/**
 * When there is only "export" in the prompt, we order the env alphabetically
 * and put quotes
 * @param	t_env *envi
 * @return	static	void
*/
static	void	ft_just_export(t_env *envi)
{
	t_env	*copy_lst;

	copy_lst = NULL;
	copy_lst = ft_copy_lst_to_declare(envi);
	ft_export_without_argv_sort(copy_lst);
	ft_put_quotes_in_declare(copy_lst);
	ft_lstclear_ms(&copy_lst, &del_ms);
	copy_lst = NULL;
}

/**
 * Replicate the export command
 * @param	char **cmd, t_env *envi
 * @return	void
*/
void	ft_export(char **cmd, t_env **envi)
{
	char	*aux;
	int		i;

	aux = NULL;
	i = 1;
	while (cmd[i] || (ft_strncmp(cmd[0], "export", 7) == 0 && cmd[1] == NULL))
	{
		if (cmd[1] == NULL || cmd == NULL)
		{
			ft_just_export(*envi);
			break ;
		}
		else if (ft_env_var_exists(cmd, envi, i) == TRUE && ft_is_equal(cmd[1]))
			ft_replace_node_parsed(envi, cmd[i]);
		else
		{
			if (ft_env_var_exists(cmd, envi, i) == TRUE
				&& ft_is_equal(cmd[1]) == FALSE)
				break ;
			aux = ft_parser_arguments(cmd[i]);
			if (aux)
				ft_export_parsed_variable(aux, envi);
		}
		i++;
	}
}
