/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 13:13:01 by marvin            #+#    #+#             */
/*   Updated: 2024/03/08 11:32:07 by marvin           ###   ########.fr       */
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
static	void	ft_print_lst_2_declare_x(t_env *temp)
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
static	void	ft_export_without_argv_sort(t_env **envi)
{
	t_env	*temp;
	t_env	*head;
	char	*aux;

	head = *envi;
	temp = *envi;
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
	// printf("\n\n");
	// printf("***********************************\n");
	// ft_print_lst_2_declare_x(envi);
	// printf("***********************************\n");
	// printf("\n\n");
}

/**
 * Alphabetically sorts the minilist after the first sorted list
 * @param	t_env *envi, t_env *finish_list
 * @return	 void
*/
static	void	ft_sort_minilist(t_env **envi, t_env *finish_list)
{
	(void)	envi;
	t_env	*temp;
	t_env	*head;
	char	*aux;

	temp = finish_list->next;
	head = finish_list->next;
	aux = NULL;
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
	printf("\n\n");
	printf("***********************************\n");
	ft_print_lst_2_declare_x(*envi);
	printf("***********************************\n");
	printf("\n\n");
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

/**
 * Splits arguments without '=', not numbers and creates two alphabetically
 * ordered lists
 * @param	t_env *envi, char *cmd
 * @return	 void
*/
static	void	ft_export_but_not_in_env(t_env **envi, char *cmd)
{
	int i;
	char	**argum;
	t_env	*finish_list;

	i = -1;
	finish_list = *envi;
	while (cmd[++i])
		if (!ft_isalpha(cmd[0]) /* && ft_is_equal(cmd) */ /* && cmd[i] != ' ' */)		// if (!ft_isalpha(cmd[i]) && cmd[i] != ' ')
		{
			ft_putstr_fd("minishell: export: '", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			// g_signal_code = 1;
			return ;
		}
	
	argum = ft_split(cmd, ' ');
	ft_export_without_argv_sort(envi);
	while (finish_list->next)
		finish_list = finish_list->next;
	ft_linked_list_env(envi, argum);	// hago lista linkeada con el nodo spliteado. que lo uso luego para hacer sort de minilista
	ft_sort_minilist(envi, finish_list);	// y noo quiero guardar esa lista envi con ese nodo, solo para la ordenacion ejemplo con cmd[1] = "Z"; o cmd[1] = "a2";
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
	int len;

	aux = *envi;
	while (aux)
	{
		len = 0;
		while (aux->content[len] != '=')
			len++;
		if (aux->next == NULL)
			return (FALSE);
		if (ft_strncmp(cmd[i], aux->content, len) == 0)
			return (TRUE);
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
		printf("\nhola\n");
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
			ft_handle_head_tail_replace_node(envi, &aux, &new_node);
			ft_lstdelone_ms(node_free, &del_ms);
			break;
		}
		aux = aux->next;
	}
	printf("\n\n");
	ft_print_lst_2(*envi); // solo para check
	printf("\n\n");
}

/**
 * Replicate the export command
 * @param	char **cmd, t_env *envi
 * @return	void
*/
void    ft_export(char **cmd, t_env **envi)
{
	char	*aux;
	int		i;

	aux = NULL;
	i = 0;
	printf("cmd[0] = %s\n", cmd[0]);
	printf("cmd[1] = %s\n", cmd[1]);
	while (cmd[++i])
	{
		if (cmd[1] == NULL)
		{
			printf("ft_export_1\n");
			ft_export_without_argv_sort(envi);
			ft_print_lst_2_declare_x(*envi);
		}
		else if (ft_check_env_var_exists(cmd, envi, i) == TRUE)
		{
			printf("ft_export_2\n");
			ft_replace_node_parsed(envi, cmd[i]);
		}
		else
		{
			if (ft_is_equal(cmd[1]) && ft_isalpha(cmd[1][0]))
			{
				printf("ft_export_3\n");
				aux = ft_parser_arguments(cmd[i]);
				ft_export_parsed_variable(aux, envi);
				// printf("*****************************\n");
				// ft_print_lst_2(*envi);
				// printf("\n******************+\n");
			}
			else
			{
				printf("ft_export_4\n");
				ft_export_but_not_in_env(envi, cmd[i]);
			}
		}
	}
}

// int main(int argc, char **argv, char **env) 
// {
// 	t_env	*envi;
// 	// char 	*cmd[3];
// 	char 	*cmd[4];
//     (void) 	argc;
//     (void) 	argv;

// 	envi = NULL;

// 		// ################ env -i ./minishell ######################
// 	if (*env == NULL)
// 	{
// 		ft_simulate_env_i_minishell(&envi);
// 	}
// 	else
// 	{
// 		ft_linked_list_env(&envi, env);
// 	}
// 	// ft_linked_list_env(&envi ,env);
// 	cmd[0] = "export";
// 	// cmd[1] = NULL;
	
// 	// cmd[1] = "SECURITYSESSIONID=alex";
// 	// cmd[2] = "USER=alvaro";
// 	// cmd[3] = NULL;

// 	// cmd[1] = "USER=alvaro";
// 	// cmd[2] = "MallocNanoZone=alex";
// 	// cmd[3] = NULL;
	
// 	// cmd[1] = "ALEX=alex";
// 	// cmd[2] = "ALVARO=alvaro";
// 	// cmd[3] = NULL;
	
// 	// cmd[1] = "LEX= alex";
// 	// cmd[1] = "ALEX=alex";
// 	// cmd[1] = "ALEX=alex espacio";
// 	// cmd[1] = "a alex=hola que";
	
// 	// cmd[1] = "2";		// no exportar	-ok-
// 	// cmd[1] = "2a";		// no exportar	-ok-
// 	// cmd[1] = "2a=";		// no exportar			-ok-
// 	// cmd[1] = "a2";		// no exportar, solo al declare "yo lo hago al declare pero tambien la exporto"
	
// 	// cmd[1] = "a2=";		// si exportar
// 	// cmd[1] = "a2a=";		// si exportar
// 	// cmd[1] = "PWD=primer_nodo_sin_env_i";
// 	// cmd[1] = "SECURITYSESSIONID=sustituir_contenido_de_esta_variable"; 	// primer nodo
// 	// cmd[1] = "USER=PAPIII_ESTA_HECHOOOOOOOOOOOOO";					  	// medio nodo
// 	// cmd[1] = "USER=PAPIII_ESTA HECHOOOOOOOOOOOOO";
// 	// cmd[1] = "_=te_cambio_el_contenido";									// ultimo nodo, no exportar nunca
	
// 	// cmd[1] = "Z";				// no exportar, solo al declare "yo lo hago al declare pero tambien la exporto"
// 	// cmd[1] = "1";
// 	// cmd[1] = "1 2 3";			// ok
// 	// cmd[1] = "PRUEBA";			// no exportar, solo al declare "yo lo hago al declare pero tambien la exporto"
// 	// cmd[2] = NULL;					// sin el env, hace lo mismo que con, no exporta, pero si en el declare alfabeticamente	
// 	ft_builtins(cmd, &envi, env);
// 	printf("\n\n");
// 	printf("***********************************\n");
// 	ft_print_lst_2(envi);
// 	printf("***********************************\n");
// 	printf("\n\n");
//     return (0);
// }

// ** FALLO con cmd[1] = "Z"; y  cmd[1] = "PRUEBA"; **
//** tambien tengo que guarar la lista **
