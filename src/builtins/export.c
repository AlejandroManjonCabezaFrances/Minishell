/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:13:14 by amanjon-          #+#    #+#             */
/*   Updated: 2024/01/22 17:02:34 by marvin           ###   ########.fr       */
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

void	ft_export_with_flag(char **cmd, char **env)
{
    t_env *envi;
    ft_linked_list_env(&envi, env);
    // ft_print_lst_2(envi);
	ft_lstadd_penultimate_str_env(&envi, ft_lstnew_penultimate_str_env(cmd[1]));
	ft_print_lst_2(envi);
}

void    ft_export(char **cmd, char **env)
{
	int j;
	int fail;

	j = 1;
	fail = 0;
	while (cmd[1][j])
	{
		if ((cmd[1][j] == '=' && ((cmd[1][j - 1] >= 'a' && cmd[1][j - 1] <= 'z')  // 1=alex , no es correcto numeros
				|| (cmd[1][j - 1] >= 'A' && cmd[1][j - 1] <= 'Z'))))
		{
			if (ft_strchr(cmd))// intentar encontrar el = + 1, y star and end ara ver largo del string sin ' ' o primer caracter del string ' ' ok
				ft_export_with_flag(cmd, env);
				fail = 1;
		}
		j++;
	}
	if (fail == 0)
		printf("arguments not found");
}

int main(int argc, char **argv, char **env) 
{
	char *cmd[3];
    (void) argc;
    (void) argv;
    
	cmd[0] = "export";
	cmd[1] = "ALEX=alex";
	cmd[2] = NULL;
	ft_builtins(cmd, env);

    return (0);
}