/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:26:05 by marvin            #+#    #+#             */
/*   Updated: 2024/01/17 14:26:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// gcc -Wall -Werror -Wextra ../../libft/Libft/src/ft_putstr_fd.c ../utils.c unset.c ../sandbox2.c ../../libft/Libft/src/ft_strtrim.c ../../libft/Libft/src/ft_strjoin.c builtins.c echo.c env.c pwd.c export.c -o pwd && ./pwd
// bash pwd < builtins.c

/**
 * Replicate the pwd command
 * @param	char **cmd
 * @return	void
*/
void    ft_pwd(char **cmd)
{	
    char cwd[PATH_MAX];

	cwd = NULL;
    if (cmd[1] != NULL && cmd[1][0] != '<' && cmd[1][0] != '>')
	{
		ft_putstr_fd("pwd without arguments according to subject\n", 2);
		return ;
	}
	else 
	{
		getcwd(cwd, sizeof(cwd));
        printf("%s\n", cwd); 
    }
    return ;
}

// int main(int argc, char **argv, char **env) 
// {
// 	t_env	*envi;
// 	(void) 	argc;
//  	(void) 	argv;
	
// 	envi = NULL;
// 	ft_linked_list_env(&envi, env);

// 	// char *cmd[2];
// 	// cmd[0] = "pwd";
// 	// cmd[1] = NULL;

// 	char *cmd[3];
// 	cmd[0] = "pwd";
// 	cmd[1] = "!";
// 	cmd[2] = NULL;
// 	ft_builtins(cmd, envi);

//     return (0);
// }