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

// gcc -Wall -Werror -Wextra ../../libft/Libft/src/ft_putstr_fd.c ../utils.c unset.c ../sandbox2.c ../../libft/Libft/src/ft_strtrim.c ../../libft/Libft/src/ft_strjoin.c builtins.c env.c echo.c exit.c pwd.c export.c cd.c -o pwd && ./pwd

// ################ env -i ./minishell ######################
// gcc -Wall -Werror -Wextra ../../libft/Libft/src/ft_putstr_fd.c ../utils.c unset.c ../sandbox2.c ../../libft/Libft/src/ft_strtrim.c ../../libft/Libft/src/ft_strjoin.c builtins.c env.c echo.c exit.c pwd.c export.c cd.c -o pwd && env -i ./pwd
// ################ env -i ./minishell ######################

// bash pwd < builtins.c

/**
 * Replicate the pwd command
 * @param	char **cmd
 * @return	void
*/
void    ft_pwd(char **cmd)
{	
    char cwd[PATH_MAX];

	// cwd = NULL;
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
