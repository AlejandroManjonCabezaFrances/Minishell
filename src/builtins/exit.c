/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:13:20 by amanjon-          #+#    #+#             */
/*   Updated: 2024/03/21 11:02:53 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// gcc -Wall -Werror -Wextra ../../libft/Libft/src/ft_putstr_fd.c ../utils.c unset.c ../sandbox2.c ../../libft/Libft/src/ft_strtrim.c ../../libft/Libft/src/ft_strjoin.c builtins.c env.c echo.c exit.c pwd.c export.c cd.c -o exit && ./exit

// ################ env -i ./minishell ######################
// gcc -Wall -Werror -Wextra ../../libft/Libft/src/ft_putstr_fd.c ../utils.c unset.c ../sandbox2.c ../../libft/Libft/src/ft_strtrim.c ../../libft/Libft/src/ft_strjoin.c builtins.c env.c echo.c exit.c pwd.c export.c cd.c -o exit && env -i ./exit
// ################ env -i ./minishell ######################

/**
 * Lower the shlvl by -1, checking that shlvl > 1
 * @param	t_env *envi
 * @return	void
*/
static	void	ft_lower_shlvl(t_env *envi)
{
	t_env   *aux;
	char	*n_shlvl;

	aux = envi;
	n_shlvl = NULL;
	while (aux)
	{
		if (ft_strncmp(aux->content, "SHLVL=", 6) == 0)
		{
			if (ft_atoi((ft_strrchr(aux->content, '=')) + 1) > 1)
			{
				n_shlvl = ft_itoa((ft_atoi(aux->content + 6) - 1));
				ft_replace_node(envi, "SHLVL=", n_shlvl);
				free(n_shlvl);
			}
		}
		aux = aux->next;
	}
	// ft_print_lst_2(envi);	// para check
}

/**
 * Manages the numeric arguments of "exit"
 * @param	char **cmd
 * @return	int
*/
static	int	ft_manage_numerics(char **cmd)
{
	int	n_argc;
	int	check_num;

	n_argc = 1;
	check_num = 0;
	while (cmd[n_argc])
	{
		if (ft_isdigit(ft_atoi(cmd[n_argc])))
		{
			check_num++;
			if (check_num > 1)
			{
				ft_putendl_fd("exit", STDOUT_FILENO);
				ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO); 
				break;
			}
		}
		n_argc++;
	}
	return (check_num);
}

/**
 * Replicates the "exit" builtin. Check if the argument is NULL/digit or not digit
 * @param	char **cmd, t_env *envi
 * @return	void
*/
void	ft_exit(char **cmd, t_env *envi)
{
	int	check_two_num;

	check_two_num = ft_manage_numerics(cmd);
	if (check_two_num <= 1)
	{
		if (cmd[1] == NULL || ft_isdigit(*cmd[1]) == 1)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			ft_lower_shlvl(envi);
		}
		else
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			ft_putendl_fd("minishell: exit: numeric argument required", STDERR_FILENO);
			ft_lower_shlvl(envi);
			exit (255);
		}
	}
}
