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

// gcc -Wall -Werror -Wextra ../../libft/Libft/src/ft_putstr_fd.c ../utils.c builtins.c echo.c pwd.c -o pwd && ./pwd
// bash pwd < builtins.c 

void    ft_pwd(char **cmd)
{	
    char cwd[PATH_MAX];

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

// int main() 
// {

//     char *cmd[] = {"pwd",/*  " <  builtins.c", */ NULL};
//     char **cmdPtr = cmd;
//     ft_builtins(cmdPtr);

// 	char *cmd[3];

// 	cmd[0] = "pwd";
// 	cmd[1] = "!";
// 	cmd[2] = NULL;
// 	ft_builtins(cmd);

//     return (0);
// }