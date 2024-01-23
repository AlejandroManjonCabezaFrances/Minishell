/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:13:14 by amanjon-          #+#    #+#             */
/*   Updated: 2024/01/23 15:40:07 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// gcc -Wall -Werror -Wextra ../../libft/Libft/src/ft_putstr_fd.c ../utils.c ../sandbox2.c builtins.c echo.c pwd.c export.c -o export && ./export
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

void	ft_export_with_flag(char *cmd, char **env_cpy)
{
    t_env *envi;
	
	envi = NULL;
    ft_linked_list_env(&envi, env_cpy);
    // ft_print_lst_2(envi);
	ft_lstadd_penultimate_str_env(&envi, ft_lstnew_penultimate_str_env(cmd));
	ft_print_lst_2(envi);
}

void	ft_export_without_argv(char **env_cpy)
{
		
	
}

void    ft_export(char **cmd, char **env_cpy)
{
	int		j;
	int		fail;
	int		k;
	char	*aux; 

	j = 1;
	fail = 0;
	aux = NULL;
	aux = malloc(sizeof(char) * (ft_strlen(cmd[1]) + 1));
	if (aux == NULL)
		return ;
	if (cmd[1] == NULL)
		ft_export_without_argv(env_cpy);
	while (cmd[1][j])
	{
		if ((cmd[1][j] == '=' && ft_isalpha(cmd[1][j - 1])))
		{
			fail = 1;
			break;
		}
		j++;
	}
	while (cmd[1][j] != ' ' && j >= 0)
		j--;
	j++;
	k = 0;
	while (cmd[1][j] != ' ' && cmd[1][j])
	{
		aux[k] = cmd[1][j];
		k++;	
		j++;
	}
	aux[k] = '\0';
	if (fail == 0)
		printf("arguments not founds");
	else
		ft_export_with_flag(aux, env_cpy);
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
	cmd[1] = "LEX= alex";
	// cmd[1] = "ALEX=alex";
	// cmd[1] = NULL;
	cmd[2] = NULL;
	ft_builtins(cmd, env_cpy);

	// habria que probar que ft_export devuelva un doble puntero
	// y guardar la lista --> env_cpy = char **ft_export(). 
	// antes de esto, hacer free a env_cpy por los leaks.
    return (0);
}