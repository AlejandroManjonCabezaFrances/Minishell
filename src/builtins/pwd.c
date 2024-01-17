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

// gcc -Wall -Werror -Wextra ../utils.c builtins.c pwd.c -o pwd && ./pwd

void    ft_pwd(char **cmd)
{

}

int main() 
{
    char *cmd[] = {"pwd", NULL};
    char **cmdPtr = cmd;
	
    ft_builtins(cmdPtr);

	// char *cmd[3];

	// cmd[0] = "pwd";
	// cmd[1] = NULL;

	// ft_builtins(cmd);
    return (0);
}