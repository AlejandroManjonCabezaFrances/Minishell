/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:33:42 by amanjon-          #+#    #+#             */
/*   Updated: 2024/03/24 02:01:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Print the linked list with the flag declare -x
 * @param	t_env *temp
 * @return	void
*/
// static	void	ft_print_lst_2_declare(t_env *temp)
// {
// 	while (temp)
// 	{
// 			printf("declare -x %s\n", temp->content);
// 			temp = temp->next;
// 	}
// }

static	void	ft_lstadd_penultimate_str_env(t_env **envi, t_env *node)
{
	t_env	*aux;
	t_env	*last;

	aux = *envi;
	last = ft_lstlast_ms(*envi);
	if (*envi == NULL)
	{
		*envi = node;
		return ;
	}
	else
	{
		while (aux->next->next != NULL)
			aux = aux->next;
		aux->next->prev = node;
		aux->next->prev->prev = aux;
		aux->next = node;
		node->next = last;
	}
}

/**
 * Exports the variable already parsed and puts it in the
 * penultimate position as the terminal
 * @param	char *cmd, t_env *envi
 * @return	void
*/
static	void	ft_export_parsed_variable(char *cmd, t_env **envi)
{
	ft_lstadd_penultimate_str_env(envi, ft_lstnew_str_env(cmd));
}

/**
 * When "export" has not argument, this function sorts the environment
 * alphabetically with the "bubble sort".
 * @param	t_env *envi
 * @return	void
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
 * Look for a "=" in the received string
 * @param	char *str
 * @return	TRUE, FALSE
*/
static	int	ft_is_equal(char *str)
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
 * Splits arguments without '=', not numbers and creates two alphabetically
 * ordered lists
 * @param	t_env *envi, char *cmd
 * @return	 void
*/
static	int	ft_export_error_argv(char *cmd)
{
	int	i;

	i = -1;		
	if (cmd != NULL)
	{
		while (cmd[++i])
		{
			if (!ft_isalpha(cmd[0]))
			{
				ft_putstr_fd("minishell: export: '", 2);
				ft_putstr_fd(cmd, 2);
				ft_putstr_fd("': not a valid identifier\n", 2);
				// g_signal_code = 1;
				return (TRUE);
			}
		}
	}
	return (FALSE);
}

/**
 * The non-existing variable to be exported will be parsed.
 * @param	char **cmd, char *aux, int *fail
 * @return	var_parsed. Parsed mallocated string
*/
static	char	*ft_parser_arguments(char *cmd)
{
	int		i;
	int		len;
	int		start;
	char	*var_parsed;

	i = 0;
	if (ft_export_error_argv(cmd) == FALSE)
	{
		while (cmd[i] && cmd[i] != '=')
			i++;
		while (cmd[i] != ' ' && i >= 0)
			i--;
		i++;
		start = i;
		len = 0;
		while (cmd[i] && cmd[i] != ' ')
		{
			len++;
			i++;
		}
		var_parsed = ft_substr(cmd, start, len);
		return (var_parsed);
	}
	return (NULL);
}

/**
 * This function searches to see if the variable you want to export exists.
 * @param	char **cmd, t_env *envi
 * @return	(TRUE) --> env var exists
*/
static	int	ft_check_env_var_exists(char **cmd, t_env **envi, int i)
{
	t_env	*aux;
	int		len;

	aux = *envi;
	while (aux)
	{
		len = 0;
		while (aux->content[len] != '=' && aux->content[len])
			len++;
		if (aux->next == NULL)
			return (FALSE);
		if (ft_strncmp(cmd[i], aux->content, len) == 0)
		{
			return (TRUE);
		}
		aux = aux->next;
	}
	return (FALSE);
}

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
 * Replaces the existing environment variable node parsed for builtin export
 * @param	t_env *envi, char *cmd
 * @return	void
*/
static	void	ft_replace_node_parsed(t_env **envi, char *cmd)
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
			node_free = aux;
			new_node = ft_lstnew_str_env(ft_parser_arguments_2(cmd));
			new_node->next = aux->next;
			aux->next->prev = new_node;
			new_node->prev = aux->prev;
			ft_handle_head_tail(envi, &aux, &new_node);
			ft_lstdelone_ms(&node_free, &del_ms);
			break ;
		}
		aux = aux->next;
	}
}

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
 * Replicate the export command
 * @param	char **cmd, t_env *envi
 * @return	void
*/
void    ft_export(char **cmd, t_env **envi)
{
	t_env	*copy_lst;
	char	*aux;
	int		i;

	copy_lst = NULL;
	aux = NULL;
	i = 1;
	while (cmd[i] || (ft_strncmp(cmd[0], "export", 7) == 0 && cmd[1] == NULL))
	{
		if (cmd[1] == NULL || cmd == NULL)
		{
			copy_lst = ft_copy_lst_to_declare(*envi);
			ft_export_without_argv_sort(copy_lst);
			ft_put_quotes_in_declare(copy_lst);
			ft_lstclear_ms(&copy_lst, &del_ms);
			copy_lst = NULL;
			break ;
		}
		else if (ft_check_env_var_exists(cmd, envi, i) == TRUE)
			ft_replace_node_parsed(envi, cmd[i]);
		else
		{
			aux = ft_parser_arguments(cmd[i]);
			if (aux)
				ft_export_parsed_variable(aux, envi);
		}
		i++;
	}
}
