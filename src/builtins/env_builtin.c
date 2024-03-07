/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:13:38 by amanjon-          #+#    #+#             */
/*   Updated: 2024/03/06 11:01:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// gcc -Wall -Werror -Wextra ../../libft/Libft/src/ft_putstr_fd.c ../utils.c unset.c ../sandbox2.c ../../libft/Libft/src/ft_strtrim.c ../../libft/Libft/src/ft_strjoin.c builtins.c env.c echo.c exit.c pwd.c export.c cd.c -o env && ./env

// ################ env -i ./minishell ######################
// gcc -Wall -Werror -Wextra ../../libft/Libft/src/ft_putstr_fd.c ../utils.c unset.c ../sandbox2.c ../../libft/Libft/src/ft_strtrim.c ../../libft/Libft/src/ft_strjoin.c builtins.c env.c echo.c exit.c pwd.c export.c cd.c -o env && env -i ./env
// ################ env -i ./minishell ######################

/**
 * Replicate the env command printing the environment list
 * @param	t_env *envi
 * @return	void
*/
void	ft_env(t_env *envi, char **cmd)
{
	if (cmd[1] != NULL)
	{
		printf("env: %s: No such file or directory\n", cmd[1]);
		// g_signal_code = 127;
	}
	else
		ft_print_lst_2(envi);
}

// int main(int argc, char **argv, char **env)
// {
// 	t_env	*envi;
// 	(void) 	argc;
//     (void) 	argv;
	
// 	envi = NULL;
// 	if (*env == NULL)
// 	{
// 		ft_simulate_env_i_minishell(&envi);
// 	}
// 	// ################ env -i ./minishell ######################
// 	else
// 	{
// 		ft_linked_list_env(&envi, env);
// 	}
// 	char *cmd[2];
// 	cmd[0] = "env";
// 	cmd[1] = NULL;

// 	// char *cmd[3];
// 	// cmd[0] = "env";
// 	// cmd[1] = "lsakdjdskf";
// 	// cmd[2] = NULL;
	
// 	ft_builtins(cmd, &envi, env);
// 	return (0);
// }