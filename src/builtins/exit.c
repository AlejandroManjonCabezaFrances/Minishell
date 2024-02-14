/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:13:20 by amanjon-          #+#    #+#             */
/*   Updated: 2024/02/14 10:45:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// gcc -Wall -Werror -Wextra ../../libft/Libft/src/ft_putstr_fd.c ../utils.c unset.c ../sandbox2.c ../../libft/Libft/src/ft_strtrim.c ../../libft/Libft/src/ft_strjoin.c builtins.c env.c echo.c pwd.c export.c cd.c -o cd && ./cd

int main(int argc, char **argv, char **env)
{
    t_env   *envi;
    char    cmd[1]
    (void) 	argc;
    (void) 	argv;

    envi = NULL;
    ft_linked_list_env(&envi, env);
    ft_builtins(cmd, envi);
    
    return (0);
}