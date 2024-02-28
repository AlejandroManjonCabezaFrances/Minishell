/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 13:13:01 by marvin            #+#    #+#             */
/*   Updated: 2024/02/28 17:57:18 by amanjon-         ###   ########.fr       */
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
void	ft_print_lst_2_declare_x(t_env *temp)
{
	while (temp)
	{
		printf("declare -x %s\n", temp->content);
		temp = temp->next;
	}
}

/**
 * Exports the variable already parsed and puts it in the
 * penultimate position as the terminal
 * @param	char *cmd, t_env *envi
 * @return	void
*/
void	ft_export_parsed_variable(char *cmd, t_env *envi)
{
	ft_lstadd_penultimate_str_env(&envi, ft_lstnew_str_env(cmd));
	// ft_print_lst_2(envi);
}

/**
 * When "export" has not argument, this function sorts the environment
 * alphabetically with the "bubble sort".
 * @param	t_env *envi
 * @return	void
*/
void	ft_export_without_argv_sort(t_env *envi)
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
	ft_print_lst_2_declare_x(envi);
}

/**
 * Alphabetically sorts the minilist after the first sorted list
 * @param	t_env *envi, t_env *finish_list
 * @return	 void
*/
void	ft_sort_minilist(t_env *envi, t_env *finish_list)
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
	// ft_print_lst_2_declare_x(envi);
}

/**
 * Splits arguments without '=', not numbers and creates two alphabetically
 * ordered lists
 * @param	t_env *envi, char *cmd
 * @return	 void
*/
void	ft_export_but_not_in_env(t_env *envi, char *cmd)
{
	int i;
	char	**argum;
	t_env	*finish_list;

	i = -1;
	finish_list = envi;
	while (cmd[++i])
		if (!ft_isalpha(cmd[i]) && cmd[i] != ' ')
		{
			printf("minishell: export: '%s' not a valid identifier\n", cmd);
			return ;
		}
	argum = ft_split(cmd, ' ');
	ft_export_without_argv_sort(envi);
	while (finish_list->next)
		finish_list = finish_list->next;
	ft_linked_list_env(&envi, argum);
	ft_sort_minilist(envi, finish_list);
}

/**
 * The non-existing variable to be exported will be parsed.
 * @param	char *cmd
 * @return	 var_parsed. Parsed mallocated string
*/
char	*ft_parser_arguments_2(char *cmd)
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
void	ft_parser_string(char *cmd, int *fail)
{
	int i;

	i = 0;
	while (cmd[i] != '=' && cmd[i] != ' ')	// && != NULL (PRUEBA) argv:
	{
		if (ft_isalpha(cmd[i]) == 0)
		{
			*fail = 0;
			break;
		}
		*fail = 1;
		i++;
	}
}

/**
 * Look for a "=" in the received string
 * @param	char *str
 * @return	TRUE, FALSE
*/
int	ft_is_equal(char *str)
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
 * The non-existing variable to be exported will be parsed.
 * @param	char **cmd, char *aux, int *fail
 * @return	var_parsed. Parsed mallocated string
*/
char	*ft_parser_arguments(char *cmd, int *fail)
{
	int		i;
	int		len;
	int		start;
	char	*var_parsed;

	ft_parser_string(cmd, fail);
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
int	ft_check_env_var_exists(char **cmd, t_env *envi)
{
	t_env	*aux;
	int len;

	aux = envi;
	while (aux)
	{
		len = 0;
		while (aux->content[len] != '=')
			len++;
		if (ft_strncmp(cmd[1], aux->content, len) == 0)
			return (TRUE);
		aux = aux->next;
	}
	return (FALSE);
}

/**
 * Replaces the existing environment variable node parsed for builtin export
 * @param	t_env *envi, char *cmd
 * @return	void
*/
void	ft_replace_node_parsed(t_env *envi, char *cmd)
{
	t_env	*aux;
	t_env	*node_free;
	t_env	*new_node;
	int		len;

	aux = envi;
	node_free = NULL;
	len = 0;
	while (cmd[len] != '=')
		len++;
	while (aux)
	{
		if (ft_strncmp(aux->content, cmd, len + 1) == 0)
		{
			node_free = aux;
			aux = aux->prev;
			new_node = ft_lstnew_str_env(ft_parser_arguments_2(cmd));
			new_node->next = aux->next->next;
			aux->next = new_node;
			ft_lstdelone_ms(node_free, &dele);
			break;
		}
		aux = aux->next;
	}
	// ft_print_lst_2(envi); // solo para check
}

/**
 * Replicate the export command
 * @param	char **cmd, t_env *envi
 * @return	void
*/
void    ft_export(char **cmd, t_env *envi)
{
	char	*aux;
	int		fail;

	aux = NULL;
	fail = 0;
	if (cmd[1] == NULL)
	{
		ft_export_without_argv_sort(envi);
		// ft_print_lst_2_declare_x(envi);
	}
	else if (ft_check_env_var_exists(cmd, envi) == TRUE)
		ft_replace_node_parsed(envi, cmd[1]);
	else
	{
		if (ft_is_equal(cmd[1]))
		{
			aux = ft_parser_arguments(cmd[1], &fail);
			if (fail == 0)
				printf("arguments not founds");
			else
				ft_export_parsed_variable(aux, envi);
		}
		else
			ft_export_but_not_in_env(envi, cmd[1]);
	}
}

int main(int argc, char **argv, char **env) 
{
	t_env	*envi;
	char 	*cmd[3];
    (void) 	argc;
    (void) 	argv;

	envi = NULL;

		// ################ env -i ./minishell ######################
	if (*env == NULL)
		ft_simulate_env_i_minishell(&envi);
	// ################ env -i ./minishell ######################
	else
		ft_linked_list_env(&envi, env);
	
	// ft_linked_list_env(&envi ,env);
	cmd[0] = "export";
	// cmd[1] = "A LEX=alex";
	// cmd[1] = "LEX= alex";
	// cmd[1] = "ALEX=alex";
	// cmd[1] = "ALEX=alex espacio";
	// cmd[1] = "a alex=hola que";
	// cmd[1] = "a2a=";
	// cmd[1] = NULL;					// -*-*-*
	// cmd[1] = "USER=PAPIII_ESTA_HECHOOOOOOOOOOOOO";
	// cmd[1] = "USER=PAPIII_ESTA HECHOOOOOOOOOOOOO";
	
	// cmd[1] = "Z B A E";				// -*-*-*	bash--> no exporta nada . mi minishell lo exporta en sort_second_minilist
	// cmd[1] = "1 2 3";					// ok
	cmd[1] = "PRUEBA";				// -*-*-*	// bash NO tiene que esportarlo con o sin env
	cmd[2] = NULL;
	ft_builtins(cmd, envi, env);
	ft_print_lst_2(envi);

    return (0);
}
