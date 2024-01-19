/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:13:14 by amanjon-          #+#    #+#             */
/*   Updated: 2024/01/19 11:46:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// gcc -Wall -Werror -Wextra ../../libft/Libft/src/ft_putstr_fd.c ../utils.c sandbox2.c builtins.c echo.c pwd.c export.c -o export && ./export

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
        printf("linked_list_1\n");
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

void    ft_export(char **cmd, char **env)
{
    t_env *envi;
    
    *cmd = NULL;
    printf("check_1\n");
    ft_linked_list_env(&envi, env);
    printf("check_2\n");
    ft_print_lst_2(envi);
    printf("check_3\n");
}

int main(int argc, char **argv, char **env) 
{
	char *cmd[3];
    (void) argc;
    (void) argv;
    
	cmd[0] = "export";
	cmd[1] = "ALEX=holaaaaaaaaaaaaa";
	cmd[2] = NULL;
	ft_builtins(cmd, env);

    return (0);
}