/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 13:13:01 by marvin            #+#    #+#             */
/*   Updated: 2024/01/26 13:29:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// gcc -Wall -Werror -Wextra ../../libft/Libft/src/ft_putstr_fd.c ../utils.c ../sandbox2.c ../../libft/Libft/src/ft_strtrim.c ../../libft/Libft/src/ft_strjoin.c builtins.c echo.c pwd.c export.c -o export && ./export
// falta usar una copia del enviroment (yo estoy cogiendo el env del sistema)
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

void ft_print_lst_2(t_env *temp)
{
	while (temp)
	{
		printf("temp = %s\n", temp->content);
		temp = temp->next;
	}
}

void ft_print_lst_2_declare_x(t_env *temp)
{
	while (temp)
	{
		printf("declare -x %s\n", temp->content);
		temp = temp->next;
	}
}

void	ft_export_parsed_variable(char *cmd, char **env_cpy)
{
    t_env *envi;
	
	envi = NULL;
    ft_linked_list_env(&envi, env_cpy);
	ft_lstadd_penultimate_str_env(&envi, ft_lstnew_str_env(cmd));
	ft_print_lst_2(envi);
}

void	ft_export_without_argv_sort(t_env *envi, char **env_cpy)
{
	t_env	*temp;
	t_env	*head;
	char	*aux;

	ft_linked_list_env(&envi, env_cpy);
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

char	*ft_parser_arguments(char **cmd, char *aux, int *fail)
{
	int	j;
	int	k;

	j = 0;
	aux = malloc(sizeof(char) * (ft_strlen(cmd[1]) + 1));
	if (aux == NULL)
		return (NULL);
	while (cmd[1][++j])
	{
		if ((cmd[1][j] == '=' && ft_isalpha(cmd[1][j - 1])))
		{
			(*fail)++;
			break;
		}
	}
	while (cmd[1][j] != ' ' && j >= 0)
		j--;
	j++;
	k = 0;
	while (cmd[1][j] != ' ' && cmd[1][j])
		aux[k++] = cmd[1][j++];	
	aux[k] = '\0';
	return (aux);
}

int	ft_check_env_var_exists(char **cmd, char **env_cpy)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (cmd[1][len] != '=' && cmd[1])
		len++;
	printf("len = %d\n", len);
	while (env_cpy[i])
	{
		if (ft_strncmp(cmd[1], env_cpy[i], len) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	del(void *content)
{
	free(content);
}

void	ft_lstdelone_ms(t_env *lst, void (*del)(void *))
{
	if (lst != NULL && del != NULL)
	{
		(*del)(lst->content);
		free(lst);
	}
}

void	ft_add_new_node_replaced(t_env *envi, char *node,char *left_element, int len)
{
	t_env	*node_free;
	t_env	*aux_start;
	t_env	*aux_end;
	t_env	*node_new;
	t_env	*aux;

	aux = envi;
	while (aux)
	{
		if (ft_strncmp(left_element, aux->content, len) == 0)
		{
			node_new = ft_lstnew_str_env(node);
			break;
			printf("node->result = %s\n", node_new->content);
		}
		aux = aux->next;
	}
	printf("aux->content = %s\n", aux->content);
	node_free = aux;
	printf("*****check_1\n");
	aux = aux->prev;
	printf("*****check_2\n");
	aux_start = aux;
	printf("*****check_3\n");
	aux_end = aux->next->next;
	printf("*****check_4\n");
	ft_lstdelone_ms(node_free, &del);
	printf("*****check_5\n");
	aux_start->next = node_new;
	printf("*****check_6\n");
	node_new->next = aux_end;
	printf("*****check_7\n");
	ft_print_lst_2(envi);
	printf("*****check_8\n");
}

void	ft_replace_var_content(t_env *envi, char *cmd, char **env_cpy)
{
	char	*right_element;
	char	*left_element;
	char	*result;
	int		len;
	t_env	*aux;

	ft_linked_list_env(&envi, env_cpy);
	aux = envi;
	right_element = NULL;
	left_element = NULL;
	len = 0;
	while (cmd[len] != '=' && cmd[len])
		len++;
	while (aux)
	{
		if (ft_strncmp(cmd, aux->content, len) == 0)
		{
			printf("envi->content = %s\n", aux->content);
			right_element = aux->content + len + 1;
			break;
		}
		aux = aux->next;
	}
	left_element = ft_strtrim(aux->content, right_element); //cmd -->  USER=ALEXXXXXXXXXXX
														// envi->content --> USER=amanjon
	printf("right_element = %s\n", right_element);	
	printf("left_element = %s\n", left_element);
	result = ft_strjoin(left_element, cmd + len + 1);
	printf("result = %s\n", result);
	// ft_print_lst_2(envi);
	ft_add_new_node_replaced(envi, result, left_element, len);
}

void    ft_export(char **cmd, char **env_cpy)
{

	t_env	*envi;
	char	*aux;
	int		fail;

	envi = NULL;
	aux = NULL;
	fail = 0;
	if (cmd[1] == NULL)
		ft_export_without_argv_sort(envi, env_cpy);
	else if (ft_check_env_var_exists(cmd, env_cpy) == 1)
	{
		ft_replace_var_content(envi, cmd[1], env_cpy);
	}
	else
	{
		aux = ft_parser_arguments(cmd, aux, &fail);
		if (fail == 0)
			printf("arguments not founds");
		else
			ft_export_parsed_variable(aux, env_cpy);
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
	char *cmd[3];
	char	**env_cpy;
    (void) argc;
    (void) argv;
    
	env_cpy = NULL;
	env_cpy = copy_env(env);
	cmd[0] = "export";
	// cmd[1] = "A LEX=alex";
	// cmd[1] = "LEX= alex";
	// cmd[1] = "ALEX=alex";
	// cmd[1] = NULL;
	cmd[1] = "USER=ALEXXXXXXXXXXX";		// sustituir var existente
	cmd[2] = NULL;
	ft_builtins(cmd, env_cpy);

	// habría que probar que ft_export devuelva un doble puntero
	// y guardar la lista --> env_cpy = char **ft_export(). 
	// antes de esto, hacer free a env_cpy por los leaks.
    return (0);
}