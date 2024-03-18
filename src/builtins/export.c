/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 13:13:01 by marvin            #+#    #+#             */
/*   Updated: 2024/03/18 11:15:18 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// gcc -Wall -Werror -Wextra ../../libft/Libft/src/ft_putstr_fd.c ../utils.c unset.c ../sandbox2.c ../../libft/Libft/src/ft_strtrim.c ../../libft/Libft/src/ft_strjoin.c builtins.c env.c echo.c exit.c pwd.c export.c cd.c -o export && ./export

// ################ env -i ./minishell ######################
// gcc -Wall -Werror -Wextra ../../libft/Libft/src/ft_putstr_fd.c ../utils.c unset.c ../sandbox2.c ../../libft/Libft/src/ft_strtrim.c ../../libft/Libft/src/ft_strjoin.c builtins.c env.c echo.c exit.c pwd.c export.c cd.c -o export && env -i ./export
// ################ env -i ./minishell ######################

/**
 * Print the linked list with the flag declare -x
 * @param	t_env *temp
 * @return	void
*/
static	void	ft_print_lst_2_declare(t_env *temp)
{
	while (temp)
	{
			printf("declare -x %s\n", temp->content);
			temp = temp->next;
	}
}

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
		aux->next->prev = node;		// new fusion minishell
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
static	void	ft_export_parsed_variable(char *cmd, t_env **envi, t_env **declare)
{
	(void ) *declare;
	ft_lstadd_penultimate_str_env(envi, ft_lstnew_str_env(cmd));
	// ft_lstadd_penultimate_str_env(declare, ft_lstnew_str_env(cmd));
}

/**
 * When "export" has not argument, this function sorts the environment
 * alphabetically with the "bubble sort".
 * @param	t_env *envi
 * @return	void
*/
static	void	ft_export_without_argv_sort(t_env **declare)
{
	t_env	*temp;
	t_env	*head;
	char	*aux;

	head = *declare;
	temp = *declare;
	// printf("(*declare)->content = %s\n", (*declare)->content);
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
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

// static	void	ft_convert_list_2(t_env *temp, char **env_array, int *count)
// {
// 	int i;

// 	while (temp)
// 	{
// 		env_array[*count] = ft_strdup(temp->content);
// 		if (env_array[*count] == NULL)
// 		{
// 			i = 0;
// 			while (i < (*count))
// 			{
// 				free(env_array[i]);
// 				i++;
// 			}
// 			free(*env_array);
// 			break;	// checkear si es correcto este break
// 		}
// 		temp = temp->next;
// 		(*count)++;
// 	}
// }
// static	char	**ft_convert_list_to_double_pointer(t_env **envi)
// {
// 	t_env	*temp;
// 	char	**env_array;
// 	int		count;
// 	// int 	i;
	
// 	temp = *envi;
// 	count = 0;
// 	while(temp)
// 	{
// 		count++;
// 		temp = temp->next;
// 	}
// 	env_array = malloc(sizeof(char *) * (count + 1));
// 	if (env_array == NULL)
// 		return (NULL);
// 	temp = *envi;
// 	count = 0;
// 	ft_convert_list_2(temp, env_array, &count);
// 	// while (temp)
// 	// {
// 	// 	env_array[count] = ft_strdup(temp->content);
// 	// 	if (env_array[count] == NULL)
// 	// 	{
// 	// 		i = 0;
// 	// 		while (i < count)
// 	// 		{
// 	// 			free(env_array[i]);
// 	// 			i++;
// 	// 		}
// 	// 		free(*env_array);
// 	// 		break;	// checkear si es correcto este break
// 	// 	}
// 	// 	temp = temp->next;
// 	// 	count++;
// 	// }
// 	env_array[count] = NULL;
// 	return (env_array);
// }


/**
 * Splits arguments without '=', not numbers and creates two alphabetically
 * ordered lists
 * @param	t_env *envi, char *cmd
 * @return	 void
*/
static	void	ft_export_but_not_in_env(t_env **declare, t_env **envi, char *cmd, char **cmds)
{
	char	**env_array;
	char	**argum;
	int 	i;
	int j;

	i = -1;
	argum = NULL;
	env_array = NULL;
	envi = NULL;					// probablemente tenga que quitar envi de la funcion
	if (cmd != NULL)
	{
		while (cmd[++i])
		{
			if (!ft_isalpha(cmd[0]) /* && ft_is_equal(cmd) */ /* && cmd[i] != ' ' */)		// if (!ft_isalpha(cmd[i]) && cmd[i] != ' ')
			{
				ft_putstr_fd("minishell: export: '", 2);
				ft_putstr_fd(cmd, 2);
				ft_putstr_fd("': not a valid identifier\n", 2);
				// g_signal_code = 1;
				return ;
			}
		}
	}
	if (cmd != NULL)
		argum = ft_split(cmd, ' ');
	if (cmds[1] == NULL)
	{
		// env_array = ft_convert_list_to_double_pointer(envi);
		// // ft_print_double_pointer(env_array);
		// ft_linked_list_env(declare, env_array);		// new

		ft_export_without_argv_sort(declare);
		ft_print_lst_2_declare(*declare);
		
	}
	else
	{	
		j = 0;
		while (argum[j])
		{
			ft_lstadd_back_str_env(declare, ft_lstnew_str_env(argum[j]));
			j++;
		}
		ft_export_without_argv_sort(declare);
		// ft_print_lst_2_declare(*declare);
		
		// env_array = ft_convert_list_to_double_pointer(envi);
		// ft_linked_list_env(declare, env_array);
		// ft_linked_list_env(declare, argum);
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
 * checks if the received string is alphabetic
 * @param	char *cmd, int *fail
 * @return	 void. By reference a fail flag is returned
*/
// void	ft_parser_string(char *cmd, int *fail)
// {
// 	int i;

// 	i = 0;
// 	while (cmd[i] != '=' && cmd[i] != ' ')	// && != NULL (PRUEBA) argv:
// 	{
// 		printf("cmd[%d] = %s\n", i, cmd);
// 		if (ft_isalpha(cmd[i]) == 0)
// 		{
// 			*fail = 0;
// 			break;
// 		}
// 		*fail = 1;
// 		i++;
// 	}
// }

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

	// ft_parser_string(cmd, fail);
	i = 0;
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

/**
 * This function searches to see if the variable you want to export exists.
 * @param	char **cmd, t_env *envi
 * @return	(TRUE) --> env var exists
*/
static	int	ft_check_env_var_exists(char **cmd, t_env **envi, int i)
{
	t_env	*aux;
	int 	len;

	aux = *envi;
	while (aux)
	{
		len = 0;
		while (aux->content[len] != '=')
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
static	void	ft_handle_head_tail_replace_node(t_env **envi, t_env **aux, t_env **new_node)
{
	if (aux == envi)
	{
		envi = new_node;
		aux = envi;
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
		if (ft_strncmp(aux->content, cmd, len + 1) == 0)
		{
			node_free = aux;
			new_node = ft_lstnew_str_env(ft_parser_arguments_2(cmd));
			new_node->next = aux->next;
			aux->next->prev = new_node;
			new_node->prev = aux->prev;
			ft_handle_head_tail_replace_node(envi, &aux, &new_node);
			ft_lstdelone_ms(node_free, &del_ms);
			break;
		}
		aux = aux->next;
	}
	// printf("\n\n");
	// ft_print_lst_2(*envi); // solo para check
	// printf("\n\n");
}

/**
 * Replicate the export command
 * @param	char **cmd, t_env *envi
 * @return	void
*/
void    ft_export(char **cmd, t_env *envi, t_env **declare)
{
	char	*aux;
	int		i;

	aux = NULL;
	i = 1;
	while (cmd[i] || (ft_strncmp(cmd[0], "export", 7) == 0 && cmd[1] == NULL))
	{
		if (cmd[1] == NULL || cmd == NULL)
		{
			ft_export_but_not_in_env(declare, &envi, cmd[i], cmd);
			break;
		}
		else if (ft_check_env_var_exists(cmd, &envi, i) == TRUE)
			ft_replace_node_parsed(&envi, cmd[i]);
		else
		{
			if (ft_is_equal(cmd[i]) && ft_isalpha(cmd[i][0]))	// cmd[1] antes y no [i]
			{
				aux = ft_parser_arguments(cmd[i]);
				ft_export_parsed_variable(aux, &envi, declare);
			}
			else
				ft_export_but_not_in_env(declare, &envi, cmd[i], cmd);
		}
		i++;
	}
}
