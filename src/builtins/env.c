/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:13:38 by amanjon-          #+#    #+#             */
/*   Updated: 2024/02/05 14:27:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// gcc -Wall -Werror -Wextra ../../libft/Libft/src/ft_putstr_fd.c ../utils.c unset.c ../sandbox2.c ../../libft/Libft/src/ft_strtrim.c ../../libft/Libft/src/ft_strjoin.c builtins.c echo.c env.c pwd.c export.c -o env && ./env

void	ft_env(t_env *envi)
{
	ft_print_lst_2(envi);
}

// int main(int argc, char **argv, char **env)
// {
// 	t_env	*envi;
// 	(void) 	argc;
//     (void) 	argv;
	
// 	envi = NULL;
// 	ft_linked_list_env(&envi, env);
// 		char *cmd[2];
// 	cmd[0] = "env";
// 	cmd[1] = NULL;
	
// 	ft_builtins(cmd, envi);
// 	return (0);
// }