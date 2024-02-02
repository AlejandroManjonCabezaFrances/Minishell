/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 13:13:01 by marvin            #+#    #+#             */
/*   Updated: 2024/02/02 13:45:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// gcc -Wall -Werror -Wextra ../../libft/Libft/src/ft_putstr_fd.c ../utils.c unset.c ../sandbox2.c ../../libft/Libft/src/ft_strtrim.c ../../libft/Libft/src/ft_strjoin.c builtins.c echo.c pwd.c export.c -o export && ./export

/**
 * Create linked list of environment
 * @param	t_env **t_env, char **env
 * @return	void
*/
void ft_linked_list_env(t_env **envi, char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		ft_lstadd_back_str_env(envi, ft_lstnew_str_env(env[i]));
		i++;	
	}
}

/**
 * Print the linked list
 * @param	t_env *temp
 * @return	void
*/
void ft_print_lst_2(t_env *temp)
{
	while (temp)
	{
		printf("temp = %s\n", temp->content);
		temp = temp->next;
	}
}

/**
 * Print the linked list with the flag declare -x
 * @param	t_env *temp
 * @return	void
*/
void ft_print_lst_2_declare_x(t_env *temp)
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
	ft_print_lst_2(envi);
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
	while (/* temp != NULL &&  */temp->next != NULL)
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

void	ft_parser_string(char *cmd, int *fail)
{
	int i;

	i = 0;
	while (cmd[i] != '=')
	{
		if (ft_isalpha(cmd[i]) == 1)
		{
			(*fail)++;
			break;
		}
		i++;
	}
	
}

/**
 * Dynamic memory will be reserved, and the non-existing variable to be
 * exported will be parsed.
 * @param	char **cmd, char *aux, int *fail
 * @return	Parsed mallocated string
*/
char	*ft_parser_arguments(char *cmd, char *aux, int *fail)
{
	int	len;
	int start;
	char	*var_parsed;

	aux = malloc(sizeof(char) * (ft_strlen(cmd) + 1));
	if (aux == NULL)
		return (NULL);
	ft_parser_string(cmd, fail);
	len = 0;
	while (cmd[len] && cmd[len]  != '=')
		len++;
	while (cmd[len] != ' ')
		len--;
	start = len + 1;
	while (cmd[len] && cmd[len] != ' ')
		len++;
	var_parsed = ft_substr(cmd, start, len);
	return (var_parsed);
}

/**
 * This function searches to see if the variable you want to export exists.
 * @param	char **cmd, t_env *envi
 * @return	(1) --> env var exists
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
	return (0);
}

/**
 * Replaces the existing environment variable node and prints the list
 * @param	t_env *envi, char *cmd
 * @return	void
*/
void	ft_replace_var_content(t_env *envi, char *cmd)
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
			new_node = ft_lstnew_str_env(cmd);
			new_node->next = aux->next->next;
			aux->next = new_node;
			ft_lstdelone_ms(node_free, &dele);
			break;
		}
		aux = aux->next;
	}
	ft_print_lst_2(envi);
}

void    ft_export(char **cmd, t_env *envi)
{
	char	*aux;
	int		fail;

	aux = NULL;
	fail = 0;
	if (cmd[1] == NULL)
		ft_export_without_argv_sort(envi);
	else if (ft_check_env_var_exists(cmd, envi) == TRUE)
	{
		ft_replace_var_content(envi, cmd[1]);
	}
	else
	{
		aux = ft_parser_arguments(cmd[1], aux, &fail);
		if (fail == 0)
			printf("arguments not founds");
		else
			ft_export_parsed_variable(aux, envi);
	}
}
// copia del env (esta función habrá que quitarla, está en el main)
char	**copy_env(char **env)
{
	char	**env_cpy;
	int		i;

	i = 0;
	while (env[i])
		i++;
	env_cpy = (char **)malloc(sizeof(char *) * (i + 1));
	if (!env_cpy)
		return (NULL);
	i = 0;
	while (env[i])
	{
		env_cpy[i] = ft_strdup(env[i]);
		i++;
	}
	env_cpy[i] = NULL;
	return (env_cpy);
}

int main(int argc, char **argv, char **env) 
{
	t_env	*envi;
	char 	*cmd[3];
    (void) 	argc;
    (void) 	argv;
    
	envi = NULL;
	ft_linked_list_env(&envi, env);
	cmd[0] = "export";
	// cmd[1] = "A LEX=alex";
	// cmd[1] = "LEX= alex";
	// cmd[1] = "ALEX=alex";
	// cmd[1] = "ALEX=alex espacio";
	// cmd[1] = "a alex=hola que"
	cmd[1] = "2a=";
	// cmd[1] = NULL;
	// cmd[1] = "USER=PAPIII_ESTA_HECHOOOOOOOOOOOOO";
	// cmd[1] = "USER=PAPIII_ESTA HECHOOOOOOOOOOOOO";
	cmd[2] = NULL;
	ft_builtins(cmd, envi);

	// habría que probar que ft_export devuelva un doble puntero
	// y guardar la lista --> env_cpy = char **ft_export(). 
	// antes de esto, hacer free a env_cpy por los leaks.
    return (0);
}